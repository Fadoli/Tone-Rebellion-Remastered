#include "game_session_layout_internal.h"

#include "iw_construct.h"

#include <stdio.h>

static void set_error(char *error, size_t capacity, const char *message)
{
    if (error == NULL || capacity == 0) return;
    (void)snprintf(error, capacity, "%s", message);
    error[capacity - 1] = '\0';
}

typedef int (*CrtCompare)(const void *context, uint16_t a, uint16_t b);

static void crt_swap(uint16_t *items, unsigned int a, unsigned int b)
{
    uint16_t value = items[a];
    items[a] = items[b];
    items[b] = value;
}

/* FUN_004777a0 is the MSVC CRT qsort: shortsort selection pass at 8 or
   fewer elements, otherwise middle-pivot partitioning with an explicit stack. */
static void crt_shortsort(uint16_t *items, unsigned int lo, unsigned int hi,
                          CrtCompare compare, const void *context)
{
    while (lo < hi) {
        unsigned int max = lo;
        unsigned int p;
        for (p = lo + 1U; p <= hi; ++p) {
            if (compare(context, items[p], items[max]) > 0) max = p;
        }
        crt_swap(items, max, hi);
        --hi;
    }
}

static void crt_qsort(uint16_t *items, unsigned int count,
                      CrtCompare compare, const void *context)
{
    unsigned int lo_stack[30];
    unsigned int hi_stack[30];
    int stack = 0;
    unsigned int lo = 0;
    unsigned int hi;
    if (count < 2) return;
    hi = count - 1U;
    for (;;) {
        unsigned int size = hi - lo + 1U;
        if (size <= 8U) {
            crt_shortsort(items, lo, hi, compare, context);
        } else {
            unsigned int loguy = lo;
            unsigned int higuy = hi + 1U;
            crt_swap(items, lo + size / 2U, lo);
            for (;;) {
                do ++loguy; while (loguy <= hi && compare(context, items[loguy], items[lo]) <= 0);
                do --higuy; while (higuy > lo && compare(context, items[higuy], items[lo]) >= 0);
                if (higuy < loguy) break;
                crt_swap(items, loguy, higuy);
            }
            crt_swap(items, lo, higuy);
            if ((int)(higuy - lo) <= (int)hi - (int)loguy) {
                if (loguy < hi) {
                    lo_stack[stack] = loguy;
                    hi_stack[stack++] = hi;
                }
                if (lo + 1U < higuy) {
                    hi = higuy - 1U;
                    continue;
                }
            } else {
                if (lo + 1U < higuy) {
                    lo_stack[stack] = lo;
                    hi_stack[stack++] = higuy - 1U;
                }
                if (loguy < hi) {
                    lo = loguy;
                    continue;
                }
            }
        }
        if (--stack < 0) return;
        lo = lo_stack[stack];
        hi = hi_stack[stack];
    }
}

/* FUN_004642a3 stores worldpos angles as float radians (* 0.017453277). */
static float world_island_radians(const WorldDefinition *world, uint16_t island)
{
    return (float)((double)world->islands[island].angle_degrees * (double)0.017453277f);
}

static int compare_neighbor_angle(const void *context, uint16_t a, uint16_t b)
{
    const WorldDefinition *world = (const WorldDefinition *)context;
    return (int)((double)world_island_radians(world, a) -
                 (double)world_island_radians(world, b));
}

static int compare_location_x(const void *context, uint16_t a, uint16_t b)
{
    const IslandData *layout = (const IslandData *)context;
    return (int)layout->locations[a].x - (int)layout->locations[b].x;
}

int game_session_prepare_runtime_layouts(const WorldDefinition *world,
                                   const IslandData *sources,
                                   IslandData *layouts,
                                   int32_t bridge_neighbors[WORLD_MAP_MAX_ISLANDS][ISLAND_DATA_MAX_LOCATIONS],
                                   char *error, size_t error_capacity)
{
    unsigned int island_index;
    for (island_index = 0; island_index < world->island_count; ++island_index) {
        uint16_t class2_locations[ISLAND_DATA_MAX_LOCATIONS];
        unsigned int class2_count = 0;
        unsigned int incident_count = 0;
        unsigned int location_index;
        unsigned int bridge_index;
        uint16_t incident_neighbors[WORLD_MAP_MAX_BRIDGES];
        unsigned int incident_neighbor_count = 0;

        for (location_index = 0; location_index < ISLAND_DATA_MAX_LOCATIONS; ++location_index) {
            bridge_neighbors[island_index][location_index] = -1;
        }

        if (sources[island_index].location_count > ISLAND_DATA_MAX_LOCATIONS) {
            if (error != NULL && error_capacity != 0) {
                (void)snprintf(error, error_capacity,
                               "island %u exceeds the original location capacity", island_index);
                error[error_capacity - 1] = '\0';
            }
            return 0;
        }
        layouts[island_index] = sources[island_index];
        for (location_index = 0; location_index < layouts[island_index].location_count;
             ++location_index) {
            if (layouts[island_index].locations[location_index].renderer_class == 2)
                class2_locations[class2_count++] = (uint16_t)location_index;
        }
        for (bridge_index = 0; bridge_index < world->bridge_count; ++bridge_index) {
            const WorldBridge *bridge = &world->bridges[bridge_index];
            if (bridge->island_a >= world->island_count ||
                bridge->island_b >= world->island_count ||
                bridge->island_a == bridge->island_b) {
                set_error(error, error_capacity, "world bridge has an invalid island endpoint");
                return 0;
            }
            if (bridge->island_a == island_index || bridge->island_b == island_index) {
                incident_neighbors[incident_neighbor_count++] =
                    bridge->island_a == island_index ? bridge->island_b : bridge->island_a;
                ++incident_count;
            }
        }
        /* FUN_00461859 sorts both lists with the CRT qsort (FUN_004777a0):
           neighbors by FUN_00461768 (truncated radian difference, so angles
           less than one radian apart compare equal) and class-2 records by
           FUN_00461831 (X). Element order on ties follows that qsort. */
        crt_qsort(incident_neighbors, incident_neighbor_count, compare_neighbor_angle, world);
        crt_qsort(class2_locations, class2_count, compare_location_x,
                  &layouts[island_index]);
        /* FUN_00461859 always pairs the first sorted record, then demotes
           records while the remaining class-2 count exceeds the incident
           bridge count, pairing the rest in neighbor order. */
        {
            unsigned int demoted = 0;
            unsigned int paired = 0;
            for (location_index = 0; location_index < class2_count; ++location_index) {
                uint16_t record = class2_locations[location_index];
                if ((location_index == 0 || class2_count - demoted <= incident_count) &&
                    paired < incident_neighbor_count) {
                    bridge_neighbors[island_index][record] =
                        (int32_t)incident_neighbors[paired++];
                } else {
                    /* The source asserts curbridge<bridgecount when an island
                       with class-2 records has no incident bridge; demote it. */
                    layouts[island_index].locations[record].renderer_class = 0;
                    ++demoted;
                }
            }
        }
    }
    return 1;
}

#include "game_session_layout_internal.h"

#include "iw_construct.h"

#include <stdio.h>

static int is_construction_location(const IslandLocation *location)
{
    uint8_t site_size;
    return iw_construct_site_size(location, &site_size);
}

static int island_has_typed_construction_sites(const IslandData *source)
{
    unsigned int index;
    for (index = 0; index < source->location_count; ++index) {
        if (source->locations[index].renderer_class == 0 &&
            is_construction_location(&source->locations[index])) return 1;
    }
    return 0;
}

static int choose_empty_class0(const IslandData *source,
                               GameRuntimeIsland *runtime,
                               ToneRng *rng,
                               unsigned int *location_index)
{
    unsigned int available = 0;
    unsigned int choice;
    unsigned int index;
    int prefer_typed_sites = island_has_typed_construction_sites(source);
    int selected;

    for (index = 0; index < source->location_count; ++index) {
        if (source->locations[index].renderer_class == 0 &&
            (!prefer_typed_sites || is_construction_location(&source->locations[index])) &&
            runtime->locations[index].owner_id == -1 &&
            runtime->locations[index].record_value_10 == 0) {
            ++available;
        }
    }
    if (available == 0) return 0;
    selected = tone_rng_bounded(rng, (int32_t)available);
    if (selected < 0 || (unsigned int)selected >= available) return 0;
    choice = (unsigned int)selected;
    for (index = 0; index < source->location_count; ++index) {
        if (source->locations[index].renderer_class != 0 ||
            (prefer_typed_sites && !is_construction_location(&source->locations[index])) ||
            runtime->locations[index].owner_id != -1 ||
            runtime->locations[index].record_value_10 != 0) continue;
        if (choice == 0) {
            *location_index = index;
            return 1;
        }
        --choice;
    }
    return 0;
}

static int assign_initial_bridge_sites(const WorldDefinition *world,
                                       const IslandData *sources,
                                       GameSession *session,
                                       ToneRng *rng,
                                       char *error, size_t error_capacity)
{
    unsigned int ordinal;
    unsigned int island_count = world->island_count;
    unsigned int wrap_span = island_count - 1U;

    for (ordinal = 0; ordinal < world->bridge_count; ++ordinal) {
        unsigned int target_island = ordinal;
        unsigned int location_index;
        while (target_island >= wrap_span) {
            unsigned int previous = target_island;
            target_island = target_island - wrap_span + 4U;
            if (target_island >= previous) {
                set_error(error, error_capacity, "bridge-site wrap rule does not converge for this world");
                return 0;
            }
        }
        if (!choose_empty_class0(&sources[target_island], &session->islands[target_island],
                                 rng, &location_index)) {
            if (error != NULL && error_capacity != 0) {
                (void)snprintf(error, error_capacity,
                               "island %u has no free class-0 record for bridge setup", target_island);
                error[error_capacity - 1] = '\0';
            }
            return 0;
        }
        session->islands[target_island].locations[location_index].record_value_10 = 1;
        session->islands[target_island].locations[location_index].record_value_24 = 5;
        ++session->class0_assignments;
    }
    return 1;
}

static int assign_class0_links(const WorldDefinition *world,
                               const IslandData *sources,
                               const int32_t shape_ids[WORLD_MAP_MAX_ISLANDS],
                               GameSession *session,
                               ToneRng *rng,
                               char *error, size_t error_capacity)
{
    unsigned int ordinal;
    unsigned int count = ((unsigned int)world->island_count - 1U) * 2U;
    unsigned int total_free = 0;

    if (session->config.randomize_class0_assignment != 0) {
        unsigned int island_index;
        for (island_index = 0; island_index + 1U < world->island_count; ++island_index) {
            unsigned int location_index;
            int prefer_typed_sites = island_has_typed_construction_sites(
                &sources[island_index]);
            for (location_index = 0; location_index < sources[island_index].location_count;
                 ++location_index) {
                if (sources[island_index].locations[location_index].renderer_class == 0 &&
                    (!prefer_typed_sites || is_construction_location(
                        &sources[island_index].locations[location_index])) &&
                    session->islands[island_index].locations[location_index].owner_id == -1 &&
                    session->islands[island_index].locations[location_index].record_value_10 == 0) {
                    ++total_free;
                }
            }
        }
        if (total_free < count) {
            set_error(error, error_capacity, "not enough free class-0 records for randomized link setup");
            return 0;
        }
    }

    for (ordinal = 0; ordinal < count; ++ordinal) {
        unsigned int target_island = ordinal / 2U;
        unsigned int location_index;
        int selected = 0;

        while (!selected) {
            if (session->config.randomize_class0_assignment != 0) {
                int random_island = tone_rng_bounded(rng, (int32_t)world->island_count - 1);
                if (random_island < 0 || random_island >= (int)world->island_count - 1) {
                    set_error(error, error_capacity, "random island index is out of range");
                    return 0;
                }
                target_island = (unsigned int)random_island;
            }
            if (choose_empty_class0(&sources[target_island], &session->islands[target_island],
                                    rng, &location_index)) {
                selected = 1;
            } else if (session->config.randomize_class0_assignment == 0) {
                if (error != NULL && error_capacity != 0) {
                    (void)snprintf(error, error_capacity,
                                   "island %u has no free class-0 record for link setup", target_island);
                    error[error_capacity - 1] = '\0';
                }
                return 0;
            }
        }
        session->islands[target_island].locations[location_index].record_value_10 = 1;
        session->islands[target_island].locations[location_index].record_value_24 =
            6 + shape_ids[ordinal / 2U] * 2 + (int32_t)(ordinal & 1U);
        ++session->class0_assignments;
    }
    return 1;
}


int game_session_assign_initial_sites(const WorldDefinition *world,
                                      const IslandData *sources,
                                      const int32_t shape_ids[WORLD_MAP_MAX_ISLANDS],
                                      GameSession *session,
                                      ToneRng *rng,
                                      char *error, size_t error_capacity)
{
    return assign_initial_bridge_sites(world, sources, session, rng,
                                       error, error_capacity) &&
           assign_class0_links(world, sources, shape_ids, session, rng,
                               error, error_capacity);
}
