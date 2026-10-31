/* Spell (FA_Cast) tests: kind tables, dispatch gating and per-kind impacts. */

static GameFloaterStart *spell_caster(GameSession *session, unsigned int index,
                                      uint8_t owner, uint8_t kind,
                                      uint8_t level)
{
    GameFloaterStart *caster = &session->floaters[index];
    memset(caster, 0, sizeof(*caster));
    caster->is_active = 1;
    caster->owner_slot = owner;
    caster->island_index = 0;
    caster->type_index = 0;
    caster->x = 1000;
    caster->y = 1000;
    caster->current_hit_points = 50;
    caster->max_hit_points = 50;
    caster->cast_spell_kind = kind;
    caster->attack_level_flags = level;
    caster->source_link_0c = -1;
    if (index >= session->floater_count)
        session->floater_count = (uint16_t)(index + 1U);
    return caster;
}

static void test_cast_kind_table_follows_owner_and_action_subtype(void)
{
    static const uint8_t expected[4][8] = {
        {4, 7, 9, 10, 11, 12, 14, 20},
        {0, 1, 8, 15, 13, 14, 18, 21},
        {1, 4, 5, 17, 12, 16, 20, 19},
        {0, 2, 3, 6, 11, 13, 16, 21}
    };
    unsigned int owner;
    unsigned int subtype;

    for (owner = 0; owner < 4; ++owner) {
        for (subtype = 0x15; subtype <= 0x1c; ++subtype) {
            assert(game_session_cast_kind_for_action(
                       (uint8_t)owner, (uint8_t)subtype) ==
                   expected[owner][subtype - 0x15]);
        }
        assert(game_session_cast_kind_for_action((uint8_t)owner, 0x14) == -1);
        assert(game_session_cast_kind_for_action((uint8_t)owner, 0x1d) == -1);
    }
    assert(game_session_cast_kind_for_action(4, 0x15) == -1);
}

static void test_cast_kind_costs_follow_spells_txt(void)
{
    uint16_t magic = 0;
    uint16_t crystal = 0;

    assert(game_session_cast_kind_costs(0, &magic, &crystal) &&
           magic == 9 && crystal == 7);
    assert(game_session_cast_kind_costs(10, &magic, &crystal) &&
           magic == 7 && crystal == 13);
    assert(game_session_cast_kind_costs(21, &magic, &crystal) &&
           magic == 46 && crystal == 22);
    assert(!game_session_cast_kind_costs(-1, &magic, &crystal));
    assert(!game_session_cast_kind_costs(22, &magic, &crystal));
    assert(!game_session_cast_kind_costs(0, NULL, &crystal));
    assert(!game_session_cast_kind_costs(0, &magic, NULL));
}

static void test_cast_sound_ids_match_effect_names(void)
{
    uint8_t owner;

    assert(game_session_cast_sound_id(1, 0) == 4);    /* FLTARMOR */
    assert(game_session_cast_sound_id(0x11, 3) == 4);
    assert(game_session_cast_sound_id(2, 0) == 5);    /* FASTPROD */
    assert(game_session_cast_sound_id(0x0e, 0) == 5);
    assert(game_session_cast_sound_id(0x15, 0) == 5);
    assert(game_session_cast_sound_id(7, 0) == 6);    /* SACRIF */
    assert(game_session_cast_sound_id(0x12, 0) == 6);
    assert(game_session_cast_sound_id(0x0a, 0) == 7); /* KILLBEAS */
    assert(game_session_cast_sound_id(0x10, 0) == 8); /* DESTSUPP */
    assert(game_session_cast_sound_id(0x16, 0) == 9); /* ASCEND */
    for (owner = 0; owner < 4; ++owner)
        assert(game_session_cast_sound_id(0, owner) == owner);
    assert(game_session_cast_sound_id(0, 4) == -1);
}

/* One hall (location 0) and one 0x2f building (location 1) for `owner` with
   a linked caster at floater 0. */
static void setup_cast_dispatch(GameSession *session, uint8_t owner,
                                uint8_t level, uint16_t magic, uint16_t crystal)
{
    GameRuntimeLocation *hall;
    GameRuntimeLocation *building;

    memset(session, 0, sizeof(*session));
    session->island_count = 1;
    session->islands[0].location_count = 2;
    session->economy[owner].hall_island_index = 0;
    session->economy[owner].hall_location_index = 0;
    hall = &session->islands[0].locations[0];
    hall->record_value_10 = 0x2a + owner * 16;
    hall->owner_id = owner;
    hall->resource_stock[GAME_RESOURCE_MAGIC_TONE] = magic;
    hall->resource_stock[GAME_RESOURCE_CRYSTAL_TONE] = crystal;
    building = &session->islands[0].locations[1];
    building->record_value_10 = 0x2f + owner * 16;
    building->owner_id = owner;
    building->source_value_14 = owner;
    building->source_location_slot_18 = 0;
    building->charge_floater_slots[0] = 0;
    (void)spell_caster(session, 0, owner, 0, level);
}

static void test_cast_dispatch_debits_both_tones_only_when_both_suffice(void)
{
    static GameSession session;
    GameRuntimeLocation *hall;

    /* Owner 1 subtype 0x15 is kind 0: 9 Magic + 7 Crystal. */
    setup_cast_dispatch(&session, 1, 0, 8, 7);
    hall = &session.islands[0].locations[0];
    assert(game_session_queue_cast_action(&session, 1, 0, 1, 0x15));
    assert(game_session_dispatch_cast_actions(&session) == 0);
    assert(hall->resource_stock[GAME_RESOURCE_MAGIC_TONE] == 8);
    assert(hall->resource_stock[GAME_RESOURCE_CRYSTAL_TONE] == 7);
    assert(session.cast_action_count == 0);
    assert(session.floaters[0].active_order_action == 0);

    setup_cast_dispatch(&session, 1, 0, 9, 6);
    assert(game_session_queue_cast_action(&session, 1, 0, 1, 0x15));
    assert(game_session_dispatch_cast_actions(&session) == 0);
    assert(session.islands[0].locations[0]
               .resource_stock[GAME_RESOURCE_MAGIC_TONE] == 9);

    setup_cast_dispatch(&session, 1, 0, 10, 8);
    assert(game_session_queue_cast_action(&session, 1, 0, 1, 0x15));
    assert(game_session_dispatch_cast_actions(&session) == 1);
    hall = &session.islands[0].locations[0];
    assert(hall->resource_stock[GAME_RESOURCE_MAGIC_TONE] == 1);
    assert(hall->resource_stock[GAME_RESOURCE_CRYSTAL_TONE] == 1);
    assert(session.floaters[0].active_order_action == 0x13);
    assert(session.floaters[0].cast_spell_kind == 0);
    assert(session.floaters[0].order_target_location == 1);
}

static void test_cast_glyph_eight_discounts_magic_only(void)
{
    static GameSession session;
    GameRuntimeLocation *hall;

    setup_cast_dispatch(&session, 1, 0, 6, 7);
    session.economy[1].glyph_mask = 0x0100U;
    assert(game_session_queue_cast_action(&session, 1, 0, 1, 0x15));
    assert(game_session_dispatch_cast_actions(&session) == 1); /* 9*2/3 = 6 */
    hall = &session.islands[0].locations[0];
    assert(hall->resource_stock[GAME_RESOURCE_MAGIC_TONE] == 0);
    assert(hall->resource_stock[GAME_RESOURCE_CRYSTAL_TONE] == 0);

    setup_cast_dispatch(&session, 1, 0, 100, 6);
    session.economy[1].glyph_mask = 0x0100U; /* crystal is never discounted */
    assert(game_session_queue_cast_action(&session, 1, 0, 1, 0x15));
    assert(game_session_dispatch_cast_actions(&session) == 0);
}

static void test_cast_dispatch_needs_caster_level_and_free_worker(void)
{
    static GameSession session;

    /* Owner 0 subtype 0x19 is kind 11: spells.txt level 2, needs worker L>=1. */
    setup_cast_dispatch(&session, 0, 0, 200, 200);
    assert(game_session_queue_cast_action(&session, 0, 0, 1, 0x19));
    assert(game_session_dispatch_cast_actions(&session) == 0);
    assert(session.islands[0].locations[0]
               .resource_stock[GAME_RESOURCE_MAGIC_TONE] == 200);

    setup_cast_dispatch(&session, 0, 1, 200, 200);
    assert(game_session_queue_cast_action(&session, 0, 0, 1, 0x19));
    assert(game_session_dispatch_cast_actions(&session) == 1);
    assert(session.floaters[0].cast_spell_kind == 11);
    assert(session.islands[0].locations[0]
               .resource_stock[GAME_RESOURCE_MAGIC_TONE] == 200 - 33);

    /* A worker already casting is skipped, so nobody can take the order. */
    setup_cast_dispatch(&session, 0, 1, 200, 200);
    session.floaters[0].active_order_action = 0x13;
    assert(game_session_queue_cast_action(&session, 0, 0, 1, 0x19));
    assert(game_session_dispatch_cast_actions(&session) == 0);
}

static void test_cast_queue_rejects_foreign_or_malformed_requests(void)
{
    static GameSession session;

    setup_cast_dispatch(&session, 1, 0, 50, 50);
    assert(!game_session_queue_cast_action(&session, 0, 0, 1, 0x15)); /* not owner */
    assert(!game_session_queue_cast_action(&session, 1, 0, 0, 0x15)); /* hall */
    assert(!game_session_queue_cast_action(&session, 1, 0, 1, 0x14));
    assert(!game_session_queue_cast_action(&session, 1, 0, 1, 0x1d));
    assert(!game_session_queue_cast_action(&session, 4, 0, 1, 0x15));
    assert(!game_session_queue_cast_action(&session, 1, 1, 1, 0x15));
    assert(!game_session_queue_cast_action(&session, 1, 0, 9, 0x15));
    assert(!game_session_queue_cast_action(NULL, 1, 0, 1, 0x15));
    assert(session.cast_action_count == 0);
}

static void test_kill_beast_cast_requires_a_leviathan_target(void)
{
    static GameSession session;

    /* Owner 0 subtype 0x18 is kind 10 (KILLBEAS): target must be owner 4. */
    setup_cast_dispatch(&session, 0, 0, 200, 200);
    add_test_worker(&session, 1, 0, 1010, 1000, 0);
    assert(game_session_queue_cast_action_target(&session, 0, 0, 1, 0x18, 1));
    assert(game_session_dispatch_cast_actions(&session) == 0);
    assert(session.islands[0].locations[0]
               .resource_stock[GAME_RESOURCE_MAGIC_TONE] == 200);

    session.floaters[1].owner_slot = 4;
    assert(game_session_queue_cast_action_target(&session, 0, 0, 1, 0x18, 1));
    assert(game_session_dispatch_cast_actions(&session) == 1);
    assert(session.floaters[0].cast_spell_kind == 10);
    assert(session.floaters[0].order_target_floater == 1);

    assert(game_session_resolve_cast_effect_step(&session, NULL, 0, 10, -1) == 2); /* 2 = target killed */
    assert(session.floaters[1].current_hit_points == 0);
    assert((session.floaters[1].source_runtime_flags & 0x008U) != 0);
}

static void test_mass_heal_restores_owner_workers_up_to_the_level_cap(void)
{
    static GameSession session;
    unsigned int index;
    unsigned int healed = 0;

    memset(&session, 0, sizeof(session));
    session.island_count = 1;
    (void)spell_caster(&session, 0, 1, 2, 0); /* level 0: cap (0+1)*5 = 5 */
    for (index = 1; index <= 8; ++index) {
        add_test_worker(&session, index, 0, 1000, 1000, 1);
        session.floaters[index].current_hit_points = 10;
    }
    add_test_worker(&session, 9, 0, 1000, 1000, 2); /* other tribe */
    session.floaters[9].current_hit_points = 10;

    assert(game_session_resolve_cast_effect_step(&session, NULL, 0, 2, -1) == 6);
    for (index = 1; index <= 8; ++index)
        if (session.floaters[index].current_hit_points == 200) ++healed;
    assert(healed == 5);
    assert(session.floaters[1].current_hit_points == 200); /* slot order */
    assert(session.floaters[6].current_hit_points == 10);
    assert(session.floaters[9].current_hit_points == 10);
    assert((session.floaters[0].source_runtime_flags & 0x200U) != 0);

    /* The step refuses a caster whose spell kind is not 2. */
    session.floaters[0].cast_spell_kind = 3;
    assert(game_session_resolve_cast_effect_step(&session, NULL, 0, 2, -1) == 0);
}

static void test_speed_cast_sets_owner_timer_by_level(void)
{
    static GameSession session;
    unsigned int level;

    for (level = 0; level < 3; ++level) {
        memset(&session, 0, sizeof(session));
        session.island_count = 1;
        (void)spell_caster(&session, 0, 2, 0x15, (uint8_t)level);
        add_test_worker(&session, 1, 0, 0, 0, 2);
        add_test_worker(&session, 2, 0, 0, 0, 3);
        /* The caster is itself an owner subtype-0 floater: caster + worker + 1. */
        assert(game_session_resolve_cast_effect_step(&session, NULL, 0, 0x15, -1)
               == 3);
        assert(session.economy[2].floater_speed_boost_timer ==
               (int16_t)(level * 1000U + 1000U));
        assert(session.economy[3].floater_speed_boost_timer == 0);
        assert((session.floaters[1].source_runtime_flags & 0x2000U) != 0);
        assert((session.floaters[2].source_runtime_flags & 0x2000U) == 0);
    }
}

static void test_timed_site_spells_store_level_scaled_timers(void)
{
    static GameSession session;
    unsigned int level;
    unsigned int kind;

    for (kind = 4; kind <= 6; ++kind) {
        for (level = 0; level < 3; ++level) {
            GameRuntimeLocation *site;
            memset(&session, 0, sizeof(session));
            session.island_count = 1;
            session.islands[0].location_count = 1;
            site = &session.islands[0].locations[0];
            (void)spell_caster(&session, 0, 0, (uint8_t)kind, (uint8_t)level);
            assert(game_session_resolve_cast_effect_step(
                       &session, NULL, 0, (uint8_t)kind, 0) == 1);
            assert((site->source_flags & 0x200U) != 0);
            assert(site->source_effect_timer_38 == (level + 1U) * 1000U);
            /* Out-of-range target and mismatched kind are refused. */
            assert(game_session_resolve_cast_effect_step(
                       &session, NULL, 0, (uint8_t)kind, 5) == 0);
            assert(game_session_resolve_cast_effect_step(
                       &session, NULL, 0, (uint8_t)(kind == 4 ? 5 : 4), 0) == 0);
        }
    }
}

static void test_blast_cast_damages_by_distance_and_consumes_the_caster(void)
{
    static GameSession session;

    memset(&session, 0, sizeof(session));
    session.island_count = 1;
    (void)spell_caster(&session, 0, 0, 7, 0); /* radius 200, base 17 */
    add_test_worker(&session, 1, 0, 1050, 1000, 1);   /* distance 50 <= 100 */
    add_test_worker(&session, 2, 0, 1150, 1000, 1);   /* 150: falloff */
    add_test_worker(&session, 3, 0, 1200, 1000, 1);   /* 200: strict edge */

    assert(game_session_resolve_cast_effect_step(&session, NULL, 0, 7, -1) == 3);
    assert(session.floaters[1].current_hit_points == 200 - 17);
    /* 17 - ((150*2 - 200) * 7) / 200 = 17 - 3 */
    assert(session.floaters[2].current_hit_points == 200 - 14);
    assert(session.floaters[3].current_hit_points == 200);
    assert(session.floaters[0].current_hit_points == 0);
    assert((session.floaters[0].source_runtime_flags & 0x008U) != 0);
}

static void test_blast_cast_radius_and_damage_grow_with_level(void)
{
    static GameSession session;

    memset(&session, 0, sizeof(session));
    session.island_count = 1;
    (void)spell_caster(&session, 0, 0, 7, 2); /* radius 300, base 27 */
    add_test_worker(&session, 1, 0, 1050, 1000, 1);
    add_test_worker(&session, 2, 0, 1000, 1000 + 299, 1);
    add_test_worker(&session, 3, 1, 1000, 1000, 1); /* other island */
    assert(game_session_resolve_cast_effect_step(&session, NULL, 0, 7, -1) == 3);
    assert(session.floaters[1].current_hit_points == 200 - 27);
    assert(session.floaters[2].current_hit_points < 200);
    assert(session.floaters[3].current_hit_points == 200);
}

static void test_fixed_area_cast_hits_floaters_within_250_without_dying_itself(void)
{
    static GameSession session;

    memset(&session, 0, sizeof(session));
    session.island_count = 1;
    (void)spell_caster(&session, 0, 0, 0x12, 0);
    add_test_worker(&session, 1, 0, 1100, 1000, 1);  /* 100: full 17 */
    add_test_worker(&session, 2, 0, 1200, 1000, 1);  /* 200: 17 - 4 */
    add_test_worker(&session, 3, 0, 1250, 1000, 1);  /* strict edge */
    assert(game_session_resolve_cast_effect_step(&session, NULL, 0, 0x12, -1) == 2);
    assert(session.floaters[1].current_hit_points == 200 - 17);
    assert(session.floaters[2].current_hit_points == 200 - 13);
    assert(session.floaters[3].current_hit_points == 200);
    assert(session.floaters[0].current_hit_points == 50); /* caster survives */
}

static void test_fixed_area_cast_kills_a_weak_floater(void)
{
    static GameSession session;

    memset(&session, 0, sizeof(session));
    session.island_count = 1;
    (void)spell_caster(&session, 0, 0, 0x12, 0);
    add_test_worker(&session, 1, 0, 1010, 1000, 4);
    session.floaters[1].current_hit_points = 5;
    assert(game_session_resolve_cast_effect_step(&session, NULL, 0, 0x12, -1) == 1);
    assert(session.floaters[1].current_hit_points == 0);
    assert((session.floaters[1].source_runtime_flags & 0x008U) != 0);
}

static void test_site_damage_drains_hp_then_destroys_or_clears(void)
{
    static GameSession session;
    GameRuntimeLocation *site;

    memset(&session, 0, sizeof(session));
    session.island_count = 1;
    session.islands[0].location_count = 4;

    site = &session.islands[0].locations[0]; /* ordinary defense item */
    site->record_value_10 = 12;
    site->source_value_34 = 5;
    assert(game_session_apply_cast_site_effect(&session, 0, 0, 3) == 3);
    assert(site->source_value_34 == 2);
    assert((site->source_flags & 0x080U) == 0);
    assert(game_session_apply_cast_site_effect(&session, 0, 0, 3) == 3);
    assert(site->source_value_34 < 1);
    assert((site->source_flags & 0x080U) != 0); /* crumble timer started */
    /* A site already crumbling no longer accepts effects. */
    assert(game_session_apply_cast_site_effect(&session, 0, 0, 3) == 0);

    site = &session.islands[0].locations[1]; /* Leviathan seed is cleared */
    site->record_value_10 = 5;
    site->owner_id = 4;
    site->source_value_14 = 4;
    site->source_value_34 = 2;
    site->record_value_24 = 7; /* pad payload: owner-4 sites keep a pool row */
    assert(game_session_apply_cast_site_effect(&session, 0, 1, 5) == 5);
    assert(site->record_value_10 == 1); /* back to a neutral pool */
    assert(site->owner_id == -1);

    site = &session.islands[0].locations[2]; /* empty site and bridge guards */
    site->record_value_10 = 0;
    assert(game_session_apply_cast_site_effect(&session, 0, 2, 3) == 0);
    site->record_value_10 = 12;
    site->renderer_class = 2;
    assert(game_session_apply_cast_site_effect(&session, 0, 2, 3) == 0);
    assert(game_session_apply_cast_site_effect(&session, 0, 9, 3) == 0);
    assert(game_session_apply_cast_site_effect(&session, 3, 0, 3) == 0);
}

static void test_pool_drain_spell_needs_a_filled_pool_and_clears_when_empty(void)
{
    static GameSession session;
    GameRuntimeLocation *pool;

    memset(&session, 0, sizeof(session));
    session.island_count = 1;
    session.islands[0].location_count = 1;
    pool = &session.islands[0].locations[0];
    pool->record_value_10 = 1;
    pool->record_value_24 = 0;
    pool->resource_stock[GAME_RESOURCE_BUILD_TONE] = 10;
    assert(game_session_apply_cast_site_effect(&session, 0, 0, 2) == 0);
    pool->record_value_24 = 1;
    assert(game_session_apply_cast_site_effect(&session, 0, 0, 2) == 1);
    assert(pool->resource_stock[GAME_RESOURCE_BUILD_TONE] == 6); /* 2 * amount */
    assert(game_session_apply_cast_site_effect(&session, 0, 0, 5) == 1);
    assert(pool->record_value_24 == 0); /* emptied: the pool site is reset */
    assert(pool->resource_stock[GAME_RESOURCE_BUILD_TONE] == 0);
}

static void test_destroy_support_spell_targets_leviathan_spawner_sites(void)
{
    static GameSession session;
    GameRuntimeLocation *spawner;
    GameRuntimeLocation *other;

    memset(&session, 0, sizeof(session));
    session.island_count = 1;
    session.islands[0].location_count = 2;
    spawner = &session.islands[0].locations[0];
    spawner->record_value_10 = 7;
    spawner->owner_id = 4;
    spawner->source_value_14 = 4;
    spawner->source_value_34 = 9;
    other = &session.islands[0].locations[1];
    other->record_value_10 = 12;
    other->source_value_34 = 9;
    (void)spell_caster(&session, 0, 0, 0x10, 0);

    /* Kind 0x10 forwards the spawner's own HP, so it always destroys it. */
    assert(game_session_resolve_cast_effect_step(&session, NULL, 0, 0x10, 0) == 9);
    assert((spawner->source_flags & 0x080U) != 0);
    /* A non spawner (item 12) is refused. */
    assert(game_session_resolve_cast_effect_step(&session, NULL, 0, 0x10, 1) == 0);
    assert(other->source_value_34 == 9);
}

static void test_leviathan_spawner_freeze_hits_every_spawner_on_the_island(void)
{
    static GameSession session;
    unsigned int index;

    memset(&session, 0, sizeof(session));
    session.island_count = 2;
    session.islands[0].location_count = 5;
    session.islands[1].location_count = 1;
    for (index = 0; index < 4; ++index)
        session.islands[0].locations[index].record_value_10 = 6 + (int32_t)index;
    session.islands[0].locations[4].record_value_10 = 5;
    session.islands[1].locations[0].record_value_10 = 6;
    (void)spell_caster(&session, 0, 0, 0x11, 0);

    assert(game_session_resolve_cast_effect_step(&session, NULL, 0, 0x11, -1) == 4);
    for (index = 0; index < 4; ++index) {
        assert((session.islands[0].locations[index].source_flags & 0x100U) != 0);
        assert(session.islands[0].locations[index].source_value_44 == 0);
    }
    assert((session.islands[0].locations[4].source_flags & 0x100U) == 0);
    assert((session.islands[1].locations[0].source_flags & 0x100U) == 0);
}

static void test_leviathan_reevaluation_cast_starts_the_island_timer(void)
{
    static GameSession session;

    memset(&session, 0, sizeof(session));
    session.island_count = 2;
    (void)spell_caster(&session, 0, 0, 0x14, 0);
    session.floaters[0].island_index = 1;
    assert(game_session_resolve_cast_effect_step(&session, NULL, 0, 0x14, -1) == 1);
    assert(session.islands[1].leviathan_periodic_timer == 0x16);
    assert(session.islands[0].leviathan_periodic_timer == 0);
    session.floaters[0].cast_spell_kind = 0x13;
    assert(game_session_resolve_cast_effect_step(&session, NULL, 0, 0x14, -1) == 0);
}

static void test_cast_steps_reject_invalid_callers(void)
{
    static GameSession session;

    memset(&session, 0, sizeof(session));
    session.island_count = 1;
    assert(game_session_resolve_cast_effect_step(NULL, NULL, 0, 7, -1) == 0);
    assert(game_session_resolve_cast_effect_step(&session, NULL, 0, 7, -1) == 0);
    (void)spell_caster(&session, 0, 0, 7, 0);
    assert(game_session_resolve_cast_effect_step(&session, NULL, 5, 7, -1) == 0);
    assert(game_session_resolve_cast_effect_step(&session, NULL, 0, 0x30, -1) == 0);
}

static void test_cast_visual_uses_owner_effect_and_one_frame_per_two_ticks(void)
{
    static GameSession session;
    int visual = -1;
    unsigned int frame = 99;
    unsigned int tick;
    uint8_t owner;

    memset(&session, 0, sizeof(session));
    session.island_count = 1;
    for (owner = 0; owner < 4; ++owner) {
        (void)spell_caster(&session, owner, owner, 0, 0);
        session.floaters[owner].x = 10;
    }
    /* Kind 0 uses the owner's own PCAST/SCAST/MCAST/LCAST effect (0..3). */
    for (owner = 0; owner < 4; ++owner) {
        assert(game_session_schedule_cast_effect_step(&session, owner, 3, -1, 40)
               == 0); /* kind 3 needs a valid target site: refused */
    }
    session.islands[0].location_count = 1;
    for (owner = 0; owner < 4; ++owner) {
        session.floaters[owner].cast_spell_kind = 4;
        assert(game_session_schedule_cast_effect_step(
                   &session, owner, 4, 0, 40));
    }
    for (tick = 0; tick < 5; ++tick) game_session_tick_cast_effects(&session, tick + 1, NULL);
    for (owner = 0; owner < 4; ++owner) {
        assert(game_session_cast_effect_visual(&session, owner, &visual, &frame));
        assert(visual == (int)owner);
        assert(frame == 2); /* 5 ticks / 2 */
    }
    for (tick = 5; tick < 200 && session.cast_effects[0].active; ++tick)
        game_session_tick_cast_effects(&session, tick + 1, NULL);
    /* Frame never passes the last frame of LEVELFRAMES (PCAST has 17). */
    session.cast_effects[0].active = 1;
    session.cast_effects[0].animation_ticks = 500;
    assert(game_session_cast_effect_visual(&session, 0, &visual, &frame));
    assert(visual == 0 && frame == 16);
    /* UPGRADE travel loops its six frames; FREEZESC impact clamps at 16. */
    session.cast_effects[0].animation_phase = 2;
    assert(game_session_cast_effect_visual(&session, 0, &visual, &frame));
    assert(visual == 10 && frame < 6);
    session.cast_effects[0].animation_phase = 3;
    assert(game_session_cast_effect_visual(&session, 0, &visual, &frame));
    assert(visual == 11 && frame == 16);
    /* Inactive slots and out-of-range slots draw nothing. */
    assert(!game_session_cast_effect_visual(&session, 31, &visual, &frame));
    assert(!game_session_cast_effect_visual(&session, 32, &visual, &frame));
    assert(!game_session_cast_effect_visual(NULL, 0, &visual, &frame));
}
