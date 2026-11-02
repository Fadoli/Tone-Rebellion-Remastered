#include "game_session.h"
#include "game_session_events.h"

#include <string.h>

/* Deferred building-selection and island events. */

int game_session_queue_audio_event(GameSession *session, uint8_t kind,
                                   int16_t owner_id)
{
    unsigned int tail;
    GameSessionAudioEvent *event;

    if (session == NULL || session->audio_event_count >=
            GAME_SESSION_MAX_AUDIO_EVENTS ||
        (kind != GAME_SESSION_AUDIO_FLOATER_DEATH &&
         kind != GAME_SESSION_AUDIO_BUILD &&
         kind != GAME_SESSION_AUDIO_BRIDGE &&
         kind != GAME_SESSION_AUDIO_FLOATER_BIRTH)) return 0;
    tail = ((unsigned int)session->audio_event_head +
            session->audio_event_count) % GAME_SESSION_MAX_AUDIO_EVENTS;
    event = &session->audio_events[tail];
    event->kind = kind;
    event->owner_id = owner_id;
    event->sound = 0;
    event->island = UINT8_MAX;
    event->x = -1;
    ++session->audio_event_count;
    return 1;
}

/* FUN_004181a6 plays an instance's SOUND on its first tick: queue it with
   the instance island and x when the def names a sound. */
int game_session_queue_effect_sound(GameSession *session, int def_index,
                                    uint8_t island, int32_t x)
{
    unsigned int tail;
    GameSessionAudioEvent *event;

    if (session == NULL || def_index < 0 || def_index >= FLOATER_EFFECT_MAX ||
        session->attack_effect_defs[def_index].sound[0] == '\0' ||
        session->audio_event_count >= GAME_SESSION_MAX_AUDIO_EVENTS) return 0;
    tail = ((unsigned int)session->audio_event_head +
            session->audio_event_count) % GAME_SESSION_MAX_AUDIO_EVENTS;
    event = &session->audio_events[tail];
    event->kind = GAME_SESSION_AUDIO_EFFECT;
    event->owner_id = -1;
    event->sound = (uint8_t)def_index;
    event->island = island;
    event->x = (int16_t)(x < 0 ? -1 : x > INT16_MAX ? INT16_MAX : x);
    ++session->audio_event_count;
    return 1;
}

int game_session_effect_def_index(const GameSession *session,
                                  const char *name)
{
    unsigned int i;
    if (session == NULL || name == NULL) return -1;
    for (i = 0; i < FLOATER_EFFECT_MAX; ++i) {
        const char *a = session->attack_effect_defs[i].name;
        const char *b = name;
        while (*a != '\0' && *b != '\0' &&
               (*a | 0x20) == (*b | 0x20)) { ++a; ++b; }
        if (*a == '\0' && *b == '\0' && session->attack_effect_defs[i].name[0])
            return (int)i;
    }
    return -1;
}

/* FUN_00416342 / FUN_00416ff8 realm IMPACT defs, by attack realm. */
int game_session_impact_def_index(const GameSession *session, unsigned int realm)
{
    static const char *const names[4] = {"PHYIMP", "SUPIMP", "ETHIMP", "NATIMP"};
    return realm < 4U ? game_session_effect_def_index(session, names[realm]) : -1;
}

/* FUN_0045b24d needs the instance x; set it on the event just queued. */
void game_session_set_last_audio_x(GameSession *session, int32_t x)
{
    if (session == NULL || session->audio_event_count == 0) return;
    session->audio_events[((unsigned int)session->audio_event_head +
        session->audio_event_count - 1U) % GAME_SESSION_MAX_AUDIO_EVENTS].x =
        (int16_t)(x < 0 ? -1 : x > INT16_MAX ? INT16_MAX : x);
}

int game_session_queue_audio_event_at(GameSession *session, uint8_t kind,
                                      int16_t owner_id, uint8_t island)
{
    if (!game_session_queue_audio_event(session, kind, owner_id)) return 0;
    session->audio_events[((unsigned int)session->audio_event_head +
        session->audio_event_count - 1U) % GAME_SESSION_MAX_AUDIO_EVENTS]
        .island = island;
    return 1;
}

/* FUN_0041660b's cast effect name: kinds 1, 17 FLTARMOR; 2, 14, 21 FASTPROD;
   7, 18 SACRIF; 10 KILLBEAS; 16 DESTSUPP; 22 ASCEND; every other kind uses
   the owner-indexed spell effect (pointer table at 0x49bd68). Each effect's
   SOUND line names the same sound. */
int game_session_cast_sound_id(uint8_t kind, uint8_t owner)
{
    switch (kind) {
    case 1: case 0x11: return 4;
    case 2: case 0x0e: case 0x15: return 5;
    case 7: case 0x12: return 6;
    case 0x0a: return 7;
    case 0x10: return 8;
    case 0x16: return 9;
    default: break;
    }
    return owner < 4U ? (int)owner : -1;
}

int game_session_cast_effect_visual(const GameSession *session,
                                    unsigned int slot, int *visual,
                                    unsigned int *frame)
{
    /* Zero-based last frame of LEVELFRAMES level 1 (effects.txt). */
    static const uint8_t last_frame[10] = {
        16, 15, 16, 23, 14, 7, 16, 16, 3, 41
    };
    const struct GameCastEffectState *effect;
    const GameFloaterStart *caster;
    unsigned int odd_steps = 0;
    int id;
    int first = 0;
    int count = 1;
    int loop = 0;
    int index;

    if (session == NULL || visual == NULL || frame == NULL ||
        slot >= GAME_SESSION_MAX_CAST_EFFECTS) return 0;
    effect = &session->cast_effects[slot];
    if (!effect->active || effect->caster_index >= session->floater_count)
        return 0;
    caster = &session->floaters[effect->caster_index];
    switch (effect->animation_phase) {
    case GAME_CAST_PHASE_START:
        id = game_session_cast_sound_id(effect->step, caster->owner_slot);
        if (id < 0 || id >= 10) return 0;
        count = last_frame[id] + 1;
        break;
    case GAME_CAST_PHASE_TRAVEL:
        loop = 1;
        switch (effect->step) {
        case 1: id = 12; count = 10; break;           /* FREEZELB */
        case 5: id = 13; break;                       /* LOCPROT 1..1 */
        case 6: id = 14; break;                       /* BUILDTON 1..1 */
        case 9: id = 15; count = 7; break;            /* HYPERHEAL 1..7 */
        default: id = 10; count = 6; break;           /* UPGRADE */
        }
        break;
    case GAME_CAST_PHASE_DESTSUPP_TRAVEL:
        id = 8; count = 4; loop = 1;
        break;
    case GAME_CAST_PHASE_FINISH:
        switch (effect->step) {
        case 0: id = 16; count = 17; break;           /* REPAIR */
        case 1: id = 4; count = 15; break;            /* FLTARMOR */
        case 3: id = 17; count = 9; break;            /* STOCKUP */
        case 4: id = 18; count = 18; break;           /* BLDARMOR */
        case 5: id = 13; first = 1; count = 21; break; /* LOCPROT 2..22 */
        case 6: id = 14; first = 1; count = 31; break; /* BUILDTON 2..32 */
        case 9: id = 15; first = 7; count = 16; break; /* HYPERHEAL 8..23 */
        case 0x0b: id = 19; count = 17; break;        /* REVPLOT */
        case 0x0c: id = 20; count = 15; break;        /* FASTFLT */
        case 0x0d: case 0x13: id = 11; count = 17; break; /* FREEZESC */
        case 0x10: id = 8; first = 14; count = 4; break;  /* DESTSUPP 15..18 */
        default: id = 21; count = 17; break;          /* BLASTWB */
        }
        break;
    default:
        return 0;
    }
    /* One frame per odd update (FUN_00415063); animation_ticks counts every
       update since the phase began. */
    odd_steps = effect->animation_ticks / 2U;
    if (loop) index = (int)(odd_steps % (unsigned int)count);
    else index = odd_steps >= (unsigned int)count ? count - 1 : (int)odd_steps;
    /* Spell 0x13 plays FREEZESC backwards from its last frame. */
    if (effect->animation_phase == GAME_CAST_PHASE_FINISH && effect->step == 0x13)
        index = count - 1 - index;
    *visual = id;
    *frame = (unsigned int)(first + index);
    return 1;
}


int game_session_cast_special_sprites(const GameSession *session,
                                      unsigned int slot,
                                      GameCastSprite out[3])
{
    const struct GameCastEffectState *effect;
    const GameFloaterStart *caster;
    int count = 0;

    if (session == NULL || out == NULL ||
        slot >= GAME_SESSION_MAX_CAST_EFFECTS) return -1;
    effect = &session->cast_effects[slot];
    if (!effect->active || effect->caster_index >= session->floater_count)
        return -1;
    caster = &session->floaters[effect->caster_index];
    if (effect->animation_phase == GAME_CAST_PHASE_KILLBEAS) {
        /* Three KILLBEAS sprites 5 apart over target floater [1]: counter c
           <= 63 falls from 320 above it at 5 per tick on frame
           (unsigned c mod 13) + 13 (level 0 bits clear); 64..73 lands on
           frames 26..35. */
        const int32_t counters[3] = {
            (int16_t)effect->effect_x, (int16_t)effect->effect_y,
            (int8_t)effect->odd_updates_remaining
        };
        const GameFloaterStart *target;
        unsigned int k;
        if (effect->phase_odd_updates_remaining == 0 ||
            caster->order_target_floater < 0 ||
            (unsigned int)caster->order_target_floater >= session->floater_count)
            return 0;
        target = &session->floaters[(unsigned int)caster->order_target_floater];
        for (k = 0; k < 3; ++k) {
            int32_t c = counters[k];
            GameCastSprite *sprite = &out[count];
            sprite->visual = 7;
            sprite->x = (int32_t)target->x - 5 + 5 * (int32_t)k;
            sprite->stipple = 8;
            if (c <= 63) {
                sprite->y = (int32_t)target->y - 320 + 5 * c;
                sprite->frame = (uint32_t)c % 13U + 13U;
            } else {
                if (c - 38 >= 36) continue;
                sprite->y = target->y;
                sprite->frame = (unsigned int)(c - 38);
            }
            ++count;
        }
        return count;
    }
    if (effect->animation_phase == GAME_CAST_PHASE_FAROBT) {
        /* FAROBT at the target site: fades in 80 above it, dips to the site,
           grabs, then carries the site's object back up and fades out
           (stipple level 8 is opaque). */
        unsigned int c = effect->odd_updates_remaining;
        int16_t selector = (int16_t)effect->effect_y;
        const GameRuntimeLocation *site;
        int32_t y0;
        int32_t y;
        int level;
        unsigned int frame;
        if (caster->island_index >= session->island_count ||
            effect->target_location_index < 0 ||
            (uint16_t)effect->target_location_index >=
                session->islands[caster->island_index].location_count)
            return 0;
        site = &session->islands[caster->island_index]
                    .locations[(uint16_t)effect->target_location_index];
        y0 = site->y;
        if (c < 24) { frame = 0; y = y0 - 80; level = (int)(c / 3U); }
        else if (c < 54) { frame = 0; y = y0 - 128 + 2 * (int32_t)c; level = 8; }
        else if (c < 68) { frame = 1 + (c - 54) / 2; y = y0 - 20; level = 8; }
        else if (c < 98) { frame = 7; y = y0 + 116 - 2 * (int32_t)c; level = 8; }
        else { frame = 7; y = y0 - 80; level = 8 - (int)((c - 98) / 3U); }
        if (level <= 0) return 0;
        out[count].visual = 22;
        out[count].frame = frame;
        out[count].x = site->x;
        out[count].y = y;
        out[count].stipple = (uint8_t)level;
        ++count;
        /* FUN_0040adb5: selectors 5.. are TRIGGERS frames sel - 5; 1..3
           use fixed shapes that are not resolved, and are skipped. */
        if (selector >= 5) {
            out[count].visual = GAME_CAST_SPRITE_OBJECT;
            out[count].frame = (unsigned int)(selector - 5);
            out[count].x = site->x;
            out[count].y = y + 20;
            out[count].stipple = (uint8_t)level;
            ++count;
        }
        return count;
    }
    return -1;
}

int game_session_queue_cast_audio(GameSession *session, uint8_t island,
                                  uint8_t sound)
{
    unsigned int tail;
    GameSessionAudioEvent *event;

    if (session == NULL || sound >= GAME_CAST_SOUND_COUNT ||
        session->audio_event_count >= GAME_SESSION_MAX_AUDIO_EVENTS) return 0;
    tail = ((unsigned int)session->audio_event_head +
            session->audio_event_count) % GAME_SESSION_MAX_AUDIO_EVENTS;
    event = &session->audio_events[tail];
    event->kind = GAME_SESSION_AUDIO_CAST;
    event->owner_id = island;
    event->sound = sound;
    event->island = island;
    event->x = -1;
    ++session->audio_event_count;
    return 1;
}

/* FUN_004181a6: every SOUND effect plays only on its first tick, when the
   instance island (+0x08) equals the displayed island (DAT_0049f53c) and
   DAT_0062d172 == 3 (the island screen). Bridge events carry no island here
   (FUN_004669bd's instance island is unresolved) and stay ungated. */
int game_session_audio_event_is_audible(const GameSessionAudioEvent *event,
                                        int island_screen,
                                        int viewed_island)
{
    if (event == NULL) return 0;
    if (event->kind == GAME_SESSION_AUDIO_BRIDGE) return 1;
    if (event->kind == GAME_SESSION_AUDIO_CAST)
        return island_screen && event->owner_id == viewed_island;
    return island_screen && event->island != UINT8_MAX &&
        (int)event->island == viewed_island;
}

int game_session_pop_audio_event(GameSession *session,
                                 GameSessionAudioEvent *out)
{
    if (session == NULL || out == NULL || session->audio_event_count == 0)
        return 0;
    *out = session->audio_events[session->audio_event_head];
    session->audio_event_head = (uint8_t)(
        ((unsigned int)session->audio_event_head + 1U) %
        GAME_SESSION_MAX_AUDIO_EVENTS);
    --session->audio_event_count;
    return 1;
}

int game_session_queue_world_event(GameSession *session, uint8_t kind,
                                   uint8_t island_index, int32_t payload)
{
    unsigned int tail;
    GameSessionWorldEvent *event;

    if (session == NULL ||
        (kind != GAME_SESSION_WORLD_EVENT_FLOATER_ADVANCED &&
         kind != GAME_SESSION_WORLD_EVENT_BUILDING_DESTROYED &&
         kind != GAME_SESSION_WORLD_EVENT_LEVIATHAN_BOND &&
         kind != GAME_SESSION_WORLD_EVENT_ISLAND_REACHED) ||
        island_index >= session->island_count ||
        session->world_event_count >= GAME_SESSION_MAX_WORLD_EVENTS) return 0;
    tail = ((unsigned int)session->world_event_head +
            session->world_event_count) % GAME_SESSION_MAX_WORLD_EVENTS;
    event = &session->world_events[tail];
    event->kind = kind;
    event->island_index = island_index;
    event->payload = payload;
    ++session->world_event_count;
    return 1;
}

int game_session_pop_world_event(GameSession *session,
                                 GameSessionWorldEvent *out)
{
    if (session == NULL || out == NULL || session->world_event_count == 0)
        return 0;
    *out = session->world_events[session->world_event_head];
    session->world_event_head = (uint8_t)(
        ((unsigned int)session->world_event_head + 1U) %
        GAME_SESSION_MAX_WORLD_EVENTS);
    --session->world_event_count;
    return 1;
}

int game_session_queue_build_selection(GameSession *session,
                                      uint8_t player_slot,
                                      uint8_t island_index,
                                      uint16_t location_index,
                                      uint16_t item_id)
{
    GameBuildSelectionRequest *request;
    if (session == NULL || player_slot >= GAME_START_PLAYER_COUNT ||
        island_index >= session->island_count ||
        location_index >= session->islands[island_index].location_count ||
        session->build_selection_count >= GAME_SESSION_MAX_BUILD_SELECTIONS) {
        return 0;
    }
    request = &session->build_selections[session->build_selection_count++];
    request->category = 0;
    request->player_slot = player_slot;
    request->action_type = 5;
    request->island_index_a = island_index;
    request->reserved_zero = 0;
    request->island_index_b = island_index;
    request->location_index = location_index;
    request->item_id = item_id;
    return 1;
}

int game_session_pop_build_selection(GameSession *session,
                                     GameBuildSelectionRequest *out)
{
    if (session == NULL || out == NULL || session->build_selection_count == 0) {
        return 0;
    }
    *out = session->build_selections[0];
    --session->build_selection_count;
    if (session->build_selection_count != 0) {
        memmove(&session->build_selections[0], &session->build_selections[1],
                (size_t)session->build_selection_count *
                sizeof(session->build_selections[0]));
    }
    memset(&session->build_selections[session->build_selection_count], 0,
           sizeof(session->build_selections[0]));
    return 1;
}

unsigned int game_session_dispatch_build_selections(GameSession *session)
{
    unsigned int read_index;
    unsigned int write_index = 0;
    unsigned int added = 0;
    unsigned int count;

    if (session == NULL) return 0;
    count = session->build_selection_count;
    for (read_index = 0; read_index < count; ++read_index) {
        GameBuildSelectionRequest request = session->build_selections[read_index];
        int slot;
        unsigned int other;
        int already_pending = 0;

        if (request.category != 0 || request.action_type != 5) continue;

        /* The native task table coalesces matching type-5 records. Treat an
           existing task as a successfully represented selection; otherwise
           preserve the outbox entry if the fixed task table is full. */
        for (other = 0; other < GAME_SESSION_MAX_PENDING_EVENTS; ++other) {
            const GamePendingEvent *candidate = &session->pending_events[other];
            if (candidate->active != 0 && candidate->action_type == 5 &&
                candidate->player_id == (int16_t)request.player_slot &&
                candidate->payload_0a == (int16_t)request.island_index_b &&
                candidate->payload_0c == (int16_t)request.reserved_zero &&
                candidate->payload_0e == (int16_t)request.location_index &&
                candidate->payload_12 == (int16_t)request.item_id) {
                already_pending = 1;
                break;
            }
        }
        if (already_pending) continue;

        /* FUN_004662b7 copies packet byte offsets +2/+4/+8/+10/+12/+14
           into the task record and sets priority 1. A building task belongs
           to one player and one island/site, so those fields participate in
           duplicate detection along with the site and building IDs. */
        slot = game_session_pending_event_add(
            session, (int16_t)request.player_slot,
            (int16_t)request.island_index_b,
            (int16_t)request.action_type,
            (int16_t)request.reserved_zero,
            (int16_t)request.location_index,
            (int16_t)request.item_id);
        if (slot >= 0) {
            ++added;
            continue;
        }

        /* The request remains queued when no pending-event slot is available.
           Keep it and every later request in their original order. */
        for (; read_index < count; ++read_index) {
            session->build_selections[write_index++] =
                session->build_selections[read_index];
        }
        break;
    }
    session->build_selection_count = (uint16_t)write_index;
    memset(&session->build_selections[write_index], 0,
           (size_t)(GAME_SESSION_MAX_BUILD_SELECTIONS - write_index) *
               sizeof(session->build_selections[0]));
    return added;
}

int game_session_queue_island_event3_subtype0(GameSession *session,
                                              uint8_t player_slot,
                                              uint8_t island_index)
{
    if (session == NULL || player_slot >= GAME_START_PLAYER_COUNT ||
        island_index >= session->island_count) return 0;
    session->islands[island_index].source_event3_pending_parity[player_slot] ^= 1U;
    return 1;
}

void game_session_dispatch_island_events(GameSession *session)
{
    unsigned int island_index;
    if (session == NULL) return;
    for (island_index = 0; island_index < session->island_count; ++island_index) {
        GameRuntimeIsland *island = &session->islands[island_index];
        unsigned int player_slot;
        for (player_slot = 0; player_slot < GAME_START_PLAYER_COUNT; ++player_slot) {
            if (island->source_event3_pending_parity[player_slot] != 0) {
                island->source_event_state[player_slot] ^= 1U;
                island->source_event3_pending_parity[player_slot] = 0;
            }
        }
    }
    /* FUN_00453958 is a virtual active-state predicate. Keep the modeled
       active bit current before Hall requests are evaluated this tick. */
    (void)game_session_recalculate_active_locations(session);
}
