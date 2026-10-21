#ifndef TONE_REBELLION_GAME_SESSION_WORLD_TYPES_H
#define TONE_REBELLION_GAME_SESSION_WORLD_TYPES_H

#include "game_session_base_types.h"

typedef struct GameRuntimeLocation {
    int32_t record_value_10;
    int32_t owner_id;
    /* Raw site +0x14. FUN_004500c4 initializes it to -1, FUN_004528ca stores
       the placing player, and subtype-9 selection/arrival also use it. */
    int32_t source_value_14;
    /* Source signed short +0x18. FUN_004528ca stores the owning player's
       100-byte source-record index here for item IDs 0x2c..0x32. */
    int16_t source_location_slot_18;
    /* Cached pad.txt maintenance cost; lets active-state transitions refresh
       player budgets without threading the catalog through every tick path. */
    int16_t maintenance_tone_cost;
    /* Source record +0x60 subslot, assigned 0..9 per item by FUN_0045ee26. */
    int16_t source_category_slot_60;
    /* On producer items 0x25/0x26/0x27, FUN_00450a71 stores a pending
       resource code 1/3/2 here when PROD completes; other classes use the
       same runtime field for different purposes. */
    int32_t record_value_24;
    int32_t bridge_neighbor_island;
    uint16_t x;
    uint16_t y;
    /* Runtime +0x1c bitword. Bit 0x400 is changed by FUN_00453bf6;
       FUN_0045eaa7 separately checks bit 0x001 for Hall stock requests. */
    uint32_t source_flags;
    /* FUN_00450847 clears runtime short +0x48 when a non-special site dies. */
    int16_t source_value_48;
    /* FUN_00453958 reads these runtime shorts at +0x44 and +0x58 when
       recomputing active bit 0. Their field meanings are not established. */
    int16_t source_value_44;
    int16_t source_value_58;
    /* FUN_00460460 writes a spawn interval to source +0x5a for selected
       Leviathan marker sites. */
    uint16_t leviathan_spawn_interval;
    /* FUN_0045cbaa clears the three subtype 1..3 links when a site is turned
       off. -1 means the source has no linked task for that subtype. */
    int16_t source_task_slot[GAME_RESOURCE_TYPE_COUNT];
    /* FUN_0041ff2e reads the selected record's word at +0x0a and displays
       its low nibble plus one as LEVEL. */
    uint16_t source_level_flags;
    /* Three stock values observed in the hall runtime record at +0x28/+0x2a/
       +0x2c. Ghidra reads them as short fields; exact signedness/caps remain
       unconfirmed. */
    uint16_t resource_stock[GAME_RESOURCE_TYPE_COUNT];
    /* FUN_0045c797 clears source short +0x30 after a CHARGE debit. */
    uint16_t charge_source_value_30;
    /* FUN_004528ca sets source +0x32 to 1 when it initializes an item. */
    int16_t source_value_32;
    /* FUN_00452fcb clears +0x3a..+0x49 and restores +0x3e to -1. */
    int16_t source_value_3a;
    int16_t source_value_3c;
    int16_t source_value_3e;
    int16_t source_value_40;
    int16_t source_value_42;
    int16_t source_value_46;
    /* FUN_0045c470's eight floater links and +0x24 count. */
    int16_t charge_floater_slots[8];
    uint16_t charge_floater_count;
    int16_t charge_recent_floater;
    /* Source staffing row +0x50 task handle; -1 means no queued staff request. */
    int16_t charge_staff_task_handle;
    /* Class-1 Leviathan markers keep the hidden type-4 floater created at
       PROD start here until the production animation releases it. */
    int16_t leviathan_spawned_floater;
    /* Raw +0x4a short: FUN_0045eaa7 uses it as the Hall stock threshold;
       FUN_0040bf98 also uses it as the BASE frame step. */
    int16_t source_capacity_4a;
    /* FUN_004528ca initializes runtime +0x34 from FUN_00450978; repair task
       rows later read this mutable short from their target location. */
    int16_t source_value_34;
    /* Raw site short +0x08; FUN_00420188 increments it after a positive
       state-7 result. Its gameplay meaning is unresolved. */
    uint16_t source_progress_08;
    /* Raw site short +0x22. The low byte is also read as the visibility mask;
       state 7 decrements the whole short when positive. */
    uint16_t source_value_22;
    /* FUN_00452e4d stores the last floater pickup tick it checked for a
       resource output at runtime +0x36. */
    int16_t resource_retry_tick_36;
    /* FUN_00453b09 writes (floater level + 1) * 1000 at site +0x38;
       FUN_00450a71 consumes it once per island update. */
    uint32_t source_effect_timer_38;
    /* Producer items 0x25..0x27 use source +0x0c to start PROD after the
       running object's cadence reaches 20; separate from BASE +0x4a. */
    uint16_t producer_cadence;
    uint16_t chug_progress;
    uint16_t glyph_progress;
    uint16_t inci_progress;
    uint16_t construction_progress;
    uint16_t production_progress;
    uint16_t animation_rate;
    /* BARG double at +0x50: FUN_0045cd75 mirrors +0x30 / 250 while a staff
       floater trains, then fades it by 0.25 per tick without an active trainee.
       FUN_004528ca leaves this value untouched when a site is reused. */
    double barg_progress;
    /* Construction pads are retained from the island layout so a completed
       CONSTR task can validate placement without a separate layout lookup. */
    uint8_t construction_site_size;
    /* Raw site +0x04: FUN_004500c4 leaves it intact; FUN_00453958 uses it
       to admit class 1, and FUN_004539e9 skips classes 2 and 3. */
    uint8_t renderer_class;
    uint8_t tribe_visibility_mask;
    /* FUN_004669bd sets bit 0 at runtime record +0x1c on both paired
       class-2 bridge objects once the bridge link is established. */
    uint8_t bridge_constructed;
} GameRuntimeLocation;

typedef struct GameRuntimeIsland {
    uint16_t location_count;
    /* FUN_004642a3 retains the fourth data\\worldpos.txt value per island;
       FUN_004535e4 uses it to choose replacement markers for class-1 item 5. */
    int16_t leviathan_marker_shape_id;
    /* FUN_00460460's per-island Leviathan planning summary. */
    int16_t leviathan_marker_count;
    int16_t leviathan_remaining_markers;
    int16_t leviathan_site_budget;
    int16_t leviathan_floater_count;
    int16_t leviathan_floater_budget;
    int8_t leviathan_admissible;
    int32_t leviathan_wait_timer;
    int16_t leviathan_periodic_timer;
    /* FUN_00423068 reads horizontal wander limits by player slot and
       island. Zero / 0x9ff retain the source's global fallback on each side;
       the data loader for the original per-player limits is not modeled. */
    int32_t floater_min_x[GAME_FLOATER_CATEGORY_COUNT];
    int32_t floater_max_x[GAME_FLOATER_CATEGORY_COUNT];
    /* FUN_00420991 uses DAT_0061fa2e[island] to decide whether a category-4
       floater seeks a different category or another category-4 floater. The
       loaded image initializes all 15 entries to zero; no direct writer was
       found, though indirect runtime updates remain possible. */
    int16_t source_level;
    /* FUN_00420dbd/FUN_0047117d check player access dwords at island +0x29ac. */
    uint8_t access_mask;
    /* FUN_00465793 message type 3/subtype 0 toggles bit 0 in one raw dword
       per player at island +0x29bc. Its gameplay/display meaning is unknown. */
    uint32_t source_event_state[GAME_START_PLAYER_COUNT];
    /* Pending type-3/subtype-0 events are represented by parity: each source
       event only XORs bit 0, so coalescing preserves the post-drain raw word. */
    uint8_t source_event3_pending_parity[GAME_START_PLAYER_COUNT];
    GameRuntimeLocation locations[ISLAND_DATA_MAX_LOCATIONS];
} GameRuntimeIsland;

#endif
