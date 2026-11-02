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
   a linked caster at floater 0. The cast pools live on the building
   (FUN_0045da2a/FUN_0045da80); the Hall holds an unrelated decoy stock. */
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
    hall->resource_stock[GAME_RESOURCE_MAGIC_TONE] = 500;
    hall->resource_stock[GAME_RESOURCE_CRYSTAL_TONE] = 500;
    building = &session->islands[0].locations[1];
    building->record_value_10 = 0x2f + owner * 16;
    building->owner_id = owner;
    building->resource_stock[GAME_RESOURCE_MAGIC_TONE] = magic;
    building->resource_stock[GAME_RESOURCE_CRYSTAL_TONE] = crystal;
    building->source_value_14 = owner;
    building->source_location_slot_18 = 0;
    building->charge_floater_slots[0] = 0;
    (void)spell_caster(session, 0, owner, 0, level);
}

static void test_cast_dispatch_debits_both_tones_only_when_both_suffice(void)
{
    static GameSession session;
    GameRuntimeLocation *site;

    /* Owner 1 subtype 0x15 is kind 0: 9 Magic + 7 Crystal. */
    setup_cast_dispatch(&session, 1, 0, 8, 7);
    site = &session.islands[0].locations[1];
    assert(game_session_queue_cast_action(&session, 1, 0, 1, 0x15));
    assert(game_session_dispatch_cast_actions(&session) == 0);
    assert(site->resource_stock[GAME_RESOURCE_MAGIC_TONE] == 8);
    assert(site->resource_stock[GAME_RESOURCE_CRYSTAL_TONE] == 7);
    assert(session.cast_action_count == 0);
    assert(session.floaters[0].active_order_action == 0);

    setup_cast_dispatch(&session, 1, 0, 9, 6);
    assert(game_session_queue_cast_action(&session, 1, 0, 1, 0x15));
    assert(game_session_dispatch_cast_actions(&session) == 0);
    assert(session.islands[0].locations[1]
               .resource_stock[GAME_RESOURCE_MAGIC_TONE] == 9);

    setup_cast_dispatch(&session, 1, 0, 10, 8);
    assert(game_session_queue_cast_action(&session, 1, 0, 1, 0x15));
    assert(game_session_dispatch_cast_actions(&session) == 1);
    site = &session.islands[0].locations[1];
    assert(site->resource_stock[GAME_RESOURCE_MAGIC_TONE] == 1);
    assert(site->resource_stock[GAME_RESOURCE_CRYSTAL_TONE] == 1);
    assert(session.floaters[0].active_order_action == 0x13);
    assert(session.floaters[0].cast_spell_kind == 0);
    assert(session.floaters[0].order_target_location == 1);
}

static void test_cast_glyph_eight_discounts_magic_only(void)
{
    static GameSession session;
    GameRuntimeLocation *site;

    setup_cast_dispatch(&session, 1, 0, 6, 7);
    session.economy[1].glyph_mask = 0x0100U;
    assert(game_session_queue_cast_action(&session, 1, 0, 1, 0x15));
    assert(game_session_dispatch_cast_actions(&session) == 1); /* 9*2/3 = 6 */
    site = &session.islands[0].locations[1];
    assert(site->resource_stock[GAME_RESOURCE_MAGIC_TONE] == 0);
    assert(site->resource_stock[GAME_RESOURCE_CRYSTAL_TONE] == 0);

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
    assert(session.islands[0].locations[1]
               .resource_stock[GAME_RESOURCE_MAGIC_TONE] == 200);

    setup_cast_dispatch(&session, 0, 1, 200, 200);
    assert(game_session_queue_cast_action(&session, 0, 0, 1, 0x19));
    assert(game_session_dispatch_cast_actions(&session) == 1);
    assert(session.floaters[0].cast_spell_kind == 11);
    assert(session.islands[0].locations[1]
               .resource_stock[GAME_RESOURCE_MAGIC_TONE] == 200 - 33);

    /* A worker already casting is skipped, so nobody can take the order. */
    setup_cast_dispatch(&session, 0, 1, 200, 200);
    session.floaters[0].active_order_action = 0x13;
    assert(game_session_queue_cast_action(&session, 0, 0, 1, 0x19));
    assert(game_session_dispatch_cast_actions(&session) == 0);
}

static void test_cast_pools_are_the_buildings_not_the_halls(void)
{
    static GameSession session;
    const GameRuntimeLocation *hall;

    /* FUN_0045da2a reads the casting site's +0x2c/+0x2a: a full Hall does
       not pay for an empty building. */
    setup_cast_dispatch(&session, 1, 0, 0, 0);
    hall = &session.islands[0].locations[0];
    assert(game_session_queue_cast_action(&session, 1, 0, 1, 0x15));
    assert(game_session_dispatch_cast_actions(&session) == 0);
    assert(hall->resource_stock[GAME_RESOURCE_MAGIC_TONE] == 500);
    assert(hall->resource_stock[GAME_RESOURCE_CRYSTAL_TONE] == 500);

    /* FUN_0045da80 debits only the building. */
    setup_cast_dispatch(&session, 1, 0, 9, 7);
    hall = &session.islands[0].locations[0];
    assert(game_session_queue_cast_action(&session, 1, 0, 1, 0x15));
    assert(game_session_dispatch_cast_actions(&session) == 1);
    assert(session.islands[0].locations[1]
               .resource_stock[GAME_RESOURCE_MAGIC_TONE] == 0);
    assert(session.islands[0].locations[1]
               .resource_stock[GAME_RESOURCE_CRYSTAL_TONE] == 0);
    assert(hall->resource_stock[GAME_RESOURCE_MAGIC_TONE] == 500);
    assert(hall->resource_stock[GAME_RESOURCE_CRYSTAL_TONE] == 500);
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
    assert(session.islands[0].locations[1]
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
        assert(game_session_schedule_cast_effect_step(&session, owner, 3, -1)
               == 0); /* kind 3 needs a valid target site: refused */
    }
    session.islands[0].location_count = 1;
    for (owner = 0; owner < 4; ++owner) {
        session.floaters[owner].cast_spell_kind = 4;
        assert(game_session_schedule_cast_effect_step(
                   &session, owner, 4, 0));
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
    session.cast_effects[0].animation_phase = GAME_CAST_PHASE_START;
    assert(game_session_cast_effect_visual(&session, 0, &visual, &frame));
    assert(visual == 0 && frame == 16);
    /* UPGRADE travel loops its six frames; kind 4 finishes on BLDARMOR. */
    session.cast_effects[0].animation_phase = GAME_CAST_PHASE_TRAVEL;
    assert(game_session_cast_effect_visual(&session, 0, &visual, &frame));
    assert(visual == 10 && frame < 6);
    session.cast_effects[0].animation_phase = GAME_CAST_PHASE_FINISH;
    assert(game_session_cast_effect_visual(&session, 0, &visual, &frame));
    assert(visual == 18 && frame == 17);
    /* Inactive slots and out-of-range slots draw nothing. */
    assert(!game_session_cast_effect_visual(&session, 31, &visual, &frame));
    assert(!game_session_cast_effect_visual(&session, 32, &visual, &frame));
    assert(!game_session_cast_effect_visual(NULL, 0, &visual, &frame));
}

static void test_attack_impact_visual_steps_one_frame_per_odd_update(void)
{
    static GameSession session;
    GameFloaterStart *attacker;
    unsigned int realm = 9;
    unsigned int frame = 99;
    uint16_t x = 0;
    uint16_t y = 0;
    unsigned int tick;

    memset(&session, 0, sizeof(session));
    session.island_count = 1;
    attacker = spell_caster(&session, 0, 0, 0, 0);
    attacker->attack_realm = 2;
    attacker->attack_impact_frame_counts[1] = 4;
    session.effect_impact_frame_starts[2][1] = 10;

    assert(!game_session_attack_effect_visual(&session, 0, &realm, &frame, &x, &y));
    game_session_start_attack_effect(&session, attacker, 3, 321, 123); /* level 1 */
    assert(attacker->attack_effect_active && session.active_attack_effect_count == 1);
    assert(game_session_attack_effect_visual(&session, 0, &realm, &frame, &x, &y));
    assert(realm == 2 && frame == 10 && x == 321 && y == 123);
    game_session_tick_combat_effects(&session, 1); /* odd tick: next frame */
    assert(game_session_attack_effect_visual(&session, 0, &realm, &frame, &x, &y));
    assert(frame == 11);
    game_session_tick_combat_effects(&session, 2); /* even tick: unchanged */
    assert(game_session_attack_effect_visual(&session, 0, &realm, &frame, &x, &y));
    assert(frame == 11);
    for (tick = 3; tick < 9; tick += 2)
        game_session_tick_combat_effects(&session, tick);
    assert(game_session_attack_effect_visual(&session, 0, &realm, &frame, &x, &y));
    assert(frame == 13); /* clamped on the last of 4 frames */
    game_session_tick_combat_effects(&session, 9);
    assert(!attacker->attack_effect_active); /* released after frames + 1 */
    assert(!game_session_attack_effect_visual(&session, 0, &realm, &frame, &x, &y));
    assert(session.active_attack_effect_count == 0);
}

static const char test_effects_text[] =
    "// test\n"
    "EFFECT BHOOD\nTYPE ONESHOT\nREALM PHY\nSHAPE PT1B\n"
    "LEVELFRAMES 4 1,15 16,30 31,46 47,62\nSOUND BHOOD\n\n"
    "EFFECT GAZECAST\nTYPE CAST\nREALM SUP\nSHAPE PT2CAST\n"
    "LEVELFRAMES 1 1,3\nCHAIN GAZER\n\n"
    "EFFECT GAZER\nTYPE BULLET\nREALM SUP\nSHAPE PT2B\n"
    "LEVELFRAMES 4 1,7 8,14 15,21 22,28\n\n"
    "EFFECT LTNG\nTYPE LIGHTNING\n;SHAPE IGNORED\nSHAPE M-FXTR2\n"
    "LEVELFRAMES 1 1,6\nSPEED 13\n";

static void test_effect_defs_parse_types_levels_chain_and_speed(void)
{
    static FloaterCatalog catalog;
    char error[96] = "";

    memset(&catalog, 0, sizeof(catalog));
    strcpy(catalog.rows[1].attack_effect_name, "gazecast");
    strcpy(catalog.rows[2].attack_effect_name, "BHOOD");
    strcpy(catalog.rows[3].attack_effect_name, "nosuch");
    assert(floater_catalog_load_effect_defs(
        (const unsigned char *)test_effects_text, sizeof(test_effects_text) - 1U,
        &catalog, error, sizeof(error)));
    assert(catalog.effect_count == 4);
    assert(catalog.effects[0].type == FLOATER_EFFECT_ONESHOT);
    assert(catalog.effects[0].level_count == 4 && catalog.effects[0].speed == 5);
    assert(catalog.effects[0].level_start[1] == 15 &&
           catalog.effects[0].level_frames[1] == 15);
    assert(catalog.effects[1].type == FLOATER_EFFECT_CAST &&
           catalog.effects[1].chain == 2); /* GAZECAST -> GAZER */
    assert(strcmp(catalog.effects[2].shape, "PT2B") == 0);
    assert(catalog.effects[3].type == FLOATER_EFFECT_LIGHTNING &&
           catalog.effects[3].speed == 13 &&
           strcmp(catalog.effects[3].shape, "M-FXTR2") == 0);
    assert(catalog.rows[1].attack_effect_def == 1); /* case-insensitive */
    assert(catalog.rows[2].attack_effect_def == 0);
    assert(catalog.rows[3].attack_effect_def == -1);
    assert(catalog.rows[0].attack_effect_def == -1);
    assert(!floater_catalog_load_effect_defs(
        (const unsigned char *)"EFFECT X\nLEVELFRAMES 9 1,2\n", 27, &catalog,
        error, sizeof(error)));
    assert(!floater_catalog_load_effect_defs(NULL, 0, &catalog, error, sizeof(error)));
}

static void setup_attack_visual_session(GameSession *session, uint8_t type,
                                        uint8_t subtype, int16_t def_index)
{
    static FloaterCatalog catalog;
    int row;
    memset(&catalog, 0, sizeof(catalog));
    assert(floater_catalog_load_effect_defs(
        (const unsigned char *)test_effects_text, sizeof(test_effects_text) - 1U,
        &catalog, NULL, 0));
    memset(session, 0, sizeof(*session));
    session->island_count = 1;
    for (row = 0; row < FLOATER_CATALOG_ROW_COUNT; ++row)
        session->attack_effect_row_def[row] = -1;
    memcpy(session->attack_effect_defs, catalog.effects, sizeof(catalog.effects));
    row = type == 4 ? subtype + 27 : type * 9 + subtype;
    session->attack_effect_row_def[row] = def_index;
    session->attack_effect_row_offset_x[row] = 10;
    session->attack_effect_row_offset_y[row] = -4;
}

static void test_oneshot_attack_visual_plays_once_at_the_attacker(void)
{
    static GameSession session;
    GameFloaterStart *attacker;
    int def = -1;
    unsigned int frame = 0;
    uint16_t x = 0;
    uint16_t y = 0;
    uint8_t island = 9;
    int impact = 0;
    unsigned int tick;

    setup_attack_visual_session(&session, 1, 1, 0); /* BHOOD */
    attacker = spell_caster(&session, 0, 0, 0, 1);  /* level 1: frames 16..30 */
    attacker->type_index = 1;
    attacker->source_subtype = 1;
    assert(game_session_spawn_attack_visual(&session, attacker, -1, 6, 50, 50, 0));
    assert(game_session_attack_visual(&session, 0, &def, &frame, &x, &y, &island, &impact));
    assert(def == 0 && frame == 15 && x == 1000 && y == 1000 && island == 0);
    for (tick = 0; tick < 14; ++tick) game_session_tick_combat_effects(&session, 1);
    assert(game_session_attack_visual(&session, 0, &def, &frame, &x, &y, &island, &impact));
    assert(frame == 29);
    game_session_tick_combat_effects(&session, 1);
    assert(!game_session_attack_visual(&session, 0, &def, &frame, &x, &y, &island, &impact));
    /* Even ticks never step. */
    assert(game_session_spawn_attack_visual(&session, attacker, -1, 6, 50, 50, 0));
    game_session_tick_combat_effects(&session, 2);
    assert(game_session_attack_visual(&session, 0, &def, &frame, &x, &y, &island, &impact));
    assert(frame == 15);
}

static void test_melee_impact_lands_on_the_target(void)
{
    /* FUN_00416ff8: when a non-bullet attack effect hits, its IMPACT is
       placed on the target with a FUN_00467260(0xf) - 7 offset per axis. */
    static GameSession session;
    GameFloaterStart *attacker;
    int def = -1;
    unsigned int frame = 0;
    uint16_t x = 0;
    uint16_t y = 0;
    uint8_t island = 9;
    int impact = -1;
    unsigned int tick;

    setup_attack_visual_session(&session, 1, 1, 0); /* BHOOD (ONESHOT) */
    attacker = spell_caster(&session, 0, 0, 0, 1);
    attacker->type_index = 1;
    attacker->source_subtype = 1;
    attacker->attack_realm = 0;
    attacker->order_target_floater = 1;
    add_test_worker(&session, 1, 0, 1200, 900, 4);
    session.effect_impact_frame_counts[0][1] = 4;
    assert(game_session_spawn_attack_visual(&session, attacker, -1, 6,
                                            1200, 900, 2));
    for (tick = 0; tick < 40 && impact < 0; ++tick) {
        game_session_tick_combat_effects(&session, 1);
        assert(game_session_attack_visual(&session, 0, &def, &frame, &x, &y,
                                          &island, &impact));
    }
    assert(impact == 0);
    assert(x >= 1193 && x <= 1207 && y >= 893 && y <= 907);
}

static void test_cast_attack_visual_chains_into_a_bullet_that_reaches_its_target(void)
{
    static GameSession session;
    GameFloaterStart *attacker;
    int def = -1;
    unsigned int frame = 0;
    uint16_t x = 0;
    uint16_t y = 0;
    uint8_t island = 0;
    int impact = 0;
    unsigned int tick;

    setup_attack_visual_session(&session, 1, 2, 1); /* GAZECAST -> GAZER */
    attacker = spell_caster(&session, 0, 0, 0, 0);
    attacker->type_index = 1;
    attacker->source_subtype = 2;
    attacker->order_target_floater = 1;
    add_test_worker(&session, 1, 0, 1100, 1000, 4);
    assert(game_session_spawn_attack_visual(&session, attacker, -1, 6, 1100, 1000, 0));
    assert(game_session_attack_visual(&session, 0, &def, &frame, &x, &y, &island, &impact));
    assert(def == 1 && x == 1000); /* cast stays on the attacker, no attxy */
    for (tick = 0; tick < 3; ++tick) game_session_tick_combat_effects(&session, 1);
    assert(game_session_attack_visual(&session, 0, &def, &frame, &x, &y, &island, &impact));
    assert(def == 2 && frame == 0 && x == 1000); /* chained into GAZER */
    game_session_tick_combat_effects(&session, 1);
    assert(game_session_attack_visual(&session, 0, &def, &frame, &x, &y, &island, &impact));
    assert(x == 1005 && y == 1000 && frame == 1); /* SPEED 5 toward the target */
    session.floaters[1].x = 1200; /* the bullet pursues a moving target */
    game_session_tick_combat_effects(&session, 1);
    assert(game_session_attack_visual(&session, 0, &def, &frame, &x, &y, &island, &impact));
    assert(x == 1010);
    for (tick = 0; tick < 100 &&
         game_session_attack_visual(&session, 0, &def, &frame, &x, &y, &island, &impact);
         ++tick)
        game_session_tick_combat_effects(&session, 1);
    assert(!game_session_attack_visual(&session, 0, &def, &frame, &x, &y, &island, &impact));
    assert(tick > 30 && tick < 60); /* ~190 px at 5 px per odd update */
}

static void test_bullet_visual_applies_attxy_mirroring_and_timeout(void)
{
    static GameSession session;
    GameFloaterStart *attacker;
    int def;
    unsigned int frame;
    uint16_t x;
    uint16_t y;
    uint8_t island;
    int impact;
    unsigned int tick;

    setup_attack_visual_session(&session, 1, 2, 2); /* GAZER bullet */
    attacker = spell_caster(&session, 0, 0, 0, 0);
    attacker->type_index = 1;
    attacker->source_subtype = 2;
    assert(game_session_spawn_attack_visual(&session, attacker, -1, 7, 60000, 1000, 0));
    assert(game_session_attack_visual(&session, 0, &def, &frame, &x, &y, &island, &impact));
    assert(x == 1010 && y == 996);
    session.attack_visuals[0].active = 0;
    attacker->facing_left = 1;
    assert(game_session_spawn_attack_visual(&session, attacker, -1, 7, 60000, 1000, 0));
    assert(game_session_attack_visual(&session, 0, &def, &frame, &x, &y, &island, &impact));
    assert(x == 990 && y == 1004); /* offsets negate when mirrored */
    /* A far destination ends through the 200-update timeout. */
    for (tick = 0; tick < 300 &&
         game_session_attack_visual(&session, 0, &def, &frame, &x, &y, &island, &impact);
         ++tick)
        game_session_tick_combat_effects(&session, 1);
    assert(tick == 201);
}

static void test_lightning_visual_grows_toward_the_target_then_ends(void)
{
    static GameSession session;
    GameFloaterStart *attacker;
    GameLightningSegment segments[GAME_LIGHTNING_MAX_SEGMENTS];
    int def;
    int impact;
    unsigned int frame;
    uint16_t x;
    uint16_t y;
    uint8_t island;
    unsigned int tick;

    setup_attack_visual_session(&session, 1, 3, 3); /* LIGHTNING */
    attacker = spell_caster(&session, 0, 0, 0, 0);
    attacker->type_index = 1;
    attacker->source_subtype = 3;
    assert(game_session_spawn_attack_visual(&session, attacker, -1, 7, 700, 1000, 0));
    /* The bolt is anchored on the target. */
    assert(game_session_attack_visual(&session, 0, &def, &frame, &x, &y, &island,
                                      &impact));
    assert(x == 700 && y == 1000);
    session.attack_visuals[0].bolt_seed = 0; /* every segment: index 0 */
    session.attack_visuals[0].bolt_bits = 0;
    assert(game_session_lightning_segments(&session, 0, segments) == 1);
    assert(segments[0].x == 700 && segments[0].y == 600 && segments[0].frame == 0);
    for (tick = 0; tick < 4; ++tick) game_session_tick_combat_effects(&session, 1);
    session.attack_visuals[0].bolt_bits = 0;
    assert(game_session_lightning_segments(&session, 0, segments) == 5);
    assert(segments[4].y == 1000 - 0x28 * 10);
    /* Seed 5: iteration 0 uses index 5 (dx -37, mirrored, x -= 1 after), the
       pattern reloads at iteration 4, so the first visible segment (iteration
       5, reveal 4) sits at x = 700 - 38 - 38 and is plain index 0. */
    session.attack_visuals[0].bolt_seed = 5;
    session.attack_visuals[0].bolt_bits = 1U << 5; /* +1 frame on iteration 5 */
    assert(game_session_lightning_segments(&session, 0, segments) == 5);
    assert(segments[0].x == 700 - 76 && segments[0].frame == 1 &&
           segments[0].mirrored == 0);
    /* Index 3..5 are mirrored: seed 0b101 with the reload at iteration 4
       makes iteration 4 (hidden at reveal 4) mirrored; reveal 5 shows it. */
    session.attack_visuals[0].ticks = 5;
    assert(game_session_lightning_segments(&session, 0, segments) == 6);
    assert(segments[0].mirrored == 1 && segments[0].frame == 4 &&
           segments[0].x == 700 - 38 - 37);
    /* Ends after the reveal counter passes 19. */
    session.attack_visuals[0].ticks = 4;
    for (tick = 4; tick < 19; ++tick) game_session_tick_combat_effects(&session, 1);
    assert(game_session_attack_visual(&session, 0, &def, &frame, &x, &y, &island,
                                      &impact));
    game_session_tick_combat_effects(&session, 1);
    assert(!game_session_attack_visual(&session, 0, &def, &frame, &x, &y, &island,
                                       &impact));
    assert(game_session_lightning_segments(&session, 0, segments) == 0);
    /* A non-lightning slot has no segments. */
    assert(game_session_lightning_segments(&session, 5, segments) == 0);
}

static void test_missing_atteff_rows_are_not_spawned(void)
{
    static GameSession session;
    GameFloaterStart *attacker;

    setup_attack_visual_session(&session, 1, 3, 3);
    attacker = spell_caster(&session, 0, 0, 0, 0);
    attacker->type_index = 1;
    attacker->source_subtype = 4; /* row without atteff */
    assert(!game_session_spawn_attack_visual(&session, attacker, -1, 6, 1, 1, 0));
    assert(!game_session_spawn_attack_visual(NULL, attacker, -1, 6, 1, 1, 0));
}

static void test_arrived_bullet_turns_into_the_realm_impact_when_the_hit_landed(void)
{
    static GameSession session;
    GameFloaterStart *attacker;
    int def;
    int impact = -1;
    unsigned int frame;
    uint16_t x;
    uint16_t y;
    uint8_t island;
    unsigned int tick;

    setup_attack_visual_session(&session, 1, 2, 2); /* GAZER bullet */
    session.effect_impact_frame_starts[1][1] = 20;
    session.effect_impact_frame_counts[1][1] = 3;
    attacker = spell_caster(&session, 0, 0, 0, 0);
    attacker->type_index = 1;
    attacker->source_subtype = 2;
    attacker->attack_realm = 1; /* SUP */
    attacker->order_target_floater = -1;
    /* damage 3 -> level 1; target 40 px away at SPEED 5, arrival within 6 */
    assert(game_session_spawn_attack_visual(&session, attacker, -1, 7, 1050, 1000, 3));
    for (tick = 0; tick < 20; ++tick) {
        game_session_tick_combat_effects(&session, 1);
        assert(game_session_attack_visual(&session, 0, &def, &frame, &x, &y,
                                          &island, &impact));
        if (impact >= 0) break;
    }
    assert(impact == 1 && def == -1);
    assert(frame == 20);
    assert(x >= 1044 && x <= 1050);
    assert(y >= 996 && y <= 1000); /* arrival is within 6 px, not exact */
    game_session_tick_combat_effects(&session, 1);
    assert(game_session_attack_visual(&session, 0, &def, &frame, &x, &y, &island, &impact));
    assert(frame == 21);
    game_session_tick_combat_effects(&session, 1);
    assert(game_session_attack_visual(&session, 0, &def, &frame, &x, &y, &island, &impact));
    assert(frame == 22);
    game_session_tick_combat_effects(&session, 1);
    assert(!game_session_attack_visual(&session, 0, &def, &frame, &x, &y, &island, &impact));

    /* A miss (damage 0) just frees the slot on arrival. */
    assert(game_session_spawn_attack_visual(&session, attacker, -1, 7, 1050, 1000, 0));
    for (tick = 0; tick < 40 && game_session_attack_visual(&session, 0, &def,
             &frame, &x, &y, &island, &impact); ++tick) {
        assert(impact < 0);
        game_session_tick_combat_effects(&session, 1);
    }
    assert(!game_session_attack_visual(&session, 0, &def, &frame, &x, &y, &island, &impact));
}

/* Leviathan unit (type 4, atteff GAZER bullet) at (1000,1000) striking a
   worker 100 px away; the attack state fires on the first combat tick. */
static void setup_deferred_strike(GameSession *session, uint32_t seed)
{
    GameFloaterStart *attacker;
    setup_attack_visual_session(session, 4, 0, 2);
    session->random_state = seed;
    session->effect_impact_frame_starts[1][1] = 20;
    session->effect_impact_frame_counts[1][1] = 3;
    session->effect_impact_frame_starts[1][2] = 30;
    session->effect_impact_frame_counts[1][2] = 3;
    session->effect_impact_frame_starts[1][3] = 40;
    session->effect_impact_frame_counts[1][3] = 3;
    session->effect_impact_frame_starts[1][0] = 10;
    session->effect_impact_frame_counts[1][0] = 3;
    attacker = spell_caster(session, 0, 4, 0, 0);
    attacker->type_index = 4;
    attacker->source_subtype = 0;
    attacker->attack_strength = 2; /* low hit chance: both outcomes occur */
    attacker->attack_realm = 1;
    attacker->movement_state = 6;
    attacker->attack_period = 0;
    attacker->attack_timer = 0;
    attacker->order_target_floater = 1;
    attacker->source_runtime_flags |= 0x040U;
    add_test_worker(session, 1, 0, 1100, 1000, 0);
}

static void test_atteff_bullet_hit_is_resolved_on_arrival_not_at_the_strike(void)
{
    static GameSession session;
    uint32_t seed;
    unsigned int hits = 0;
    unsigned int misses = 0;

    for (seed = 1; seed <= 40; ++seed) {
        int def;
        int impact = -1;
        unsigned int frame;
        uint16_t x;
        uint16_t y;
        uint8_t island;
        unsigned int tick;
        int16_t hp_before;
        int arrived_tick = -1;

        setup_deferred_strike(&session, seed * 2654435761U); /* spread seeds */
        session.floaters[0].attack_strength = (uint8_t)(seed % 7U); /* mixed hit chances */
        hp_before = session.floaters[1].current_hit_points;
        game_session_tick_floater_combat(&session, 0);
        /* The strike spawns the bullet but deals nothing yet. */
        assert(session.attack_visuals[0].active && session.attack_visuals[0].pending_hit);
        assert(session.floaters[1].current_hit_points == hp_before);
        assert(session.floaters[0].attack_effect_active &&
               session.floaters[0].attack_effect_waits_visual &&
               session.floaters[0].attack_effect_hidden);
        assert(!game_session_attack_effect_visual(&session, 0, &(unsigned int){0},
            &(unsigned int){0}, &(uint16_t){0}, &(uint16_t){0}));
        for (tick = 0; tick < 100; ++tick) {
            game_session_tick_combat_effects(&session, 1);
            if (arrived_tick < 0 && !session.attack_visuals[0].pending_hit) {
                arrived_tick = (int)tick;
                break;
            }
            /* In flight: no damage, attacker still attacking. */
            assert(session.floaters[1].current_hit_points == hp_before);
            assert(session.floaters[0].attack_effect_waits_visual);
        }
        assert(arrived_tick >= 15 && arrived_tick <= 25); /* ~95 px at 5 */
        if (session.floaters[1].current_hit_points < hp_before) {
            ++hits;
            /* A landed hit turns the same slot into the realm impact. */
            assert(game_session_attack_visual(&session, 0, &def, &frame, &x, &y,
                                              &island, &impact));
            assert(impact == 1 && x >= 1094);
            assert(session.floaters[0].attack_effect_waits_visual);
        } else {
            ++misses;
            assert(!session.attack_visuals[0].active);
        }
        /* Once the slot is gone the attacker is released. */
        for (tick = 0; tick < 20; ++tick) game_session_tick_combat_effects(&session, 1);
        assert(!session.attack_visuals[0].active);
        assert(!session.floaters[0].attack_effect_active &&
               !session.floaters[0].attack_effect_waits_visual);
        assert(session.active_attack_effect_count == 0);
        game_session_tick_floater_combat(&session, 0);
        game_session_tick_floater_combat(&session, 0);
        assert(session.floaters[0].movement_state == 0);
    }
    assert(hits > 0 && misses > 0); /* both outcomes exercised across seeds */
}

static void test_deferred_hit_is_deterministic_for_a_given_seed(void)
{
    static GameSession first;
    static GameSession second;
    unsigned int tick;

    setup_deferred_strike(&first, 7);
    setup_deferred_strike(&second, 7);
    game_session_tick_floater_combat(&first, 0);
    game_session_tick_floater_combat(&second, 0);
    for (tick = 0; tick < 60; ++tick) {
        game_session_tick_combat_effects(&first, 1);
        game_session_tick_combat_effects(&second, 1);
    }
    assert(first.floaters[1].current_hit_points ==
           second.floaters[1].current_hit_points);
    assert(first.random_state == second.random_state);
    /* The cosmetic visual stream never feeds the simulation RNG: draw-only
       lightning ticks leave random_state untouched. */
    setup_attack_visual_session(&first, 1, 3, 3);
    first.random_state = 1234;
    {
        GameFloaterStart *attacker = spell_caster(&first, 0, 0, 0, 0);
        attacker->type_index = 1;
        attacker->source_subtype = 3;
        assert(game_session_spawn_attack_visual(&first, attacker, -1, 7, 1, 1, 0));
    }
    for (tick = 0; tick < 25; ++tick) game_session_tick_combat_effects(&first, 1);
    assert(first.random_state == 1234);
}

static void test_dead_attacker_effect_deals_no_damage_and_frees_the_slot(void)
{
    static GameSession session;
    unsigned int tick;
    int16_t hp;

    setup_deferred_strike(&session, 3);
    hp = session.floaters[1].current_hit_points;
    game_session_tick_floater_combat(&session, 0);
    session.floaters[0].is_active = 0; /* attacker dies mid-flight */
    for (tick = 0; tick < 60; ++tick) game_session_tick_combat_effects(&session, 1);
    assert(session.floaters[1].current_hit_points == hp);
    assert(!session.attack_visuals[0].active);
    assert(!session.floaters[0].attack_effect_waits_visual);
    assert(session.active_attack_effect_count == 0);
}

static void test_weak_attackers_still_hit_at_the_strike(void)
{
    /* Path B (no atteff): damage lands at the strike, impact right away. */
    static GameSession session;
    uint32_t seed;
    unsigned int hits = 0;

    for (seed = 1; seed <= 40 && hits == 0; ++seed) {
        setup_deferred_strike(&session, seed);
        session.floaters[0].type_index = 0; /* a plain worker: no atteff row */
        session.floaters[0].attack_strength = 3;
        session.floaters[0].attack_impact_frame_counts[0] = 3;
        session.floaters[0].attack_impact_frame_counts[1] = 3;
        session.floaters[0].attack_impact_frame_counts[2] = 3;
        session.floaters[0].attack_impact_frame_counts[3] = 3;
        game_session_tick_floater_combat(&session, 0);
        assert(!session.attack_visuals[0].active);
        assert(!session.floaters[0].attack_effect_waits_visual);
        if (session.floaters[1].current_hit_points < 200) {
            ++hits;
            assert(session.floaters[0].attack_effect_active); /* impact timer */
        }
    }
    assert(hits > 0);
}

static void test_attack_bookkeeping_goes_to_the_attacker(void)
{
    /* FUN_004200d2 / FUN_00420188 run with ECX = attacker (call site
       0x41ec64): a positive hit bumps the attacker's +0x08 and every attempt
       consumes one attacker charge (+0x22). The target is left alone. */
    static GameSession session;
    GameRuntimeLocation *site;
    uint32_t seed;
    unsigned int hits = 0;
    unsigned int misses = 0;

    for (seed = 1; seed <= 60; ++seed) {
        int32_t damage;
        memset(&session, 0, sizeof(session));
        session.island_count = 1;
        /* Spread the seeds: nearby seeds give nearby first draws. */
        session.random_state = seed * 0x9e3779b1U;
        add_test_worker(&session, 0, 0, 1000, 1000, 0);
        add_test_worker(&session, 1, 0, 1010, 1000, 1);
        session.floaters[0].attack_level_flags = 3;
        session.floaters[0].charge_current = 3;
        session.floaters[0].source_link_0c = -1;
        session.floaters[1].charge_current = 2;
        session.floaters[1].source_link_0c = -1;
        damage = game_session_resolve_attack_hit(&session, 0, 6, 1, -1);
        assert(session.floaters[0].charge_current == 2);
        assert(session.floaters[0].source_progress_08 == (damage > 0 ? 1U : 0U));
        assert(session.floaters[1].charge_current == 2);
        assert(session.floaters[1].source_progress_08 == 0);
        if (damage > 0) ++hits; else ++misses;
    }
    assert(hits > 0 && misses > 0);

    /* A plain uncharged worker damages a site; the site's +0x22 visibility
       byte is not consumed. */
    memset(&session, 0, sizeof(session));
    session.island_count = 1;
    session.islands[0].location_count = 1;
    site = &session.islands[0].locations[0];
    site->record_value_10 = 12;
    site->owner_id = -1;
    site->source_value_14 = -1;
    site->source_value_34 = 100;
    site->source_value_22 = 0x03;
    site->tribe_visibility_mask = 0x03;
    add_test_worker(&session, 0, 0, 1000, 1000, 0);
    session.floaters[0].attack_level_flags = 3;
    session.floaters[0].source_link_0c = -1;
    assert(game_session_resolve_attack_hit(&session, 0, 7, -1, 0) > 0);
    assert(site->source_value_34 < 100);
    assert(site->source_value_22 == 0x03);
    assert(site->tribe_visibility_mask == 0x03);
    assert(site->source_progress_08 == 0);
    assert(session.floaters[0].source_progress_08 == 1);
}

static void test_out_of_range_caster_walks_then_casts(void)
{
    /* FUN_0041e569 steps state 0x13 through FUN_00422d27 before
       FUN_0042383d: out of range the +0x34 counter does not move; in range
       the destination is parked on the caster, the counter runs and the
       finished cast (flag 0x200) adds 5 to +0x08. */
    static GameSession session;
    PadCatalog catalog;
    GameFloaterStart *caster;
    GameRuntimeLocation *site;
    uint32_t tick;
    int reached = 0;

    make_pad_catalog(&catalog);
    memset(&session, 0, sizeof(session));
    session.island_count = 1;
    session.islands[0].location_count = 1;
    session.islands[0].floater_max_x[0] = 0x9ff;
    site = &session.islands[0].locations[0];
    site->x = 1600;
    site->y = 200;
    site->owner_id = -1;
    site->source_value_14 = -1;
    caster = spell_caster(&session, 0, 0, 0, 0); /* range 300 */
    caster->x = 1000;
    caster->y = 200;
    caster->movement_speed = 4;
    caster->active_order_action = 0x13;
    caster->movement_state = 0x13;
    caster->order_target_location = 0;
    caster->order_target_floater = -1;
    caster->order_progress = UINT8_MAX;

    game_session_tick_floater_moves(&session, 1, &catalog);
    assert(caster->active_order_action == 0x13);
    assert(caster->x > 1000);
    assert(caster->order_timer == 0);
    for (tick = 2; tick < 2000 && caster->active_order_action == 0x13; ++tick) {
        if (!reached && caster->order_timer != 0) {
            reached = 1;
            assert(caster->x >= 1600 - 300);
            assert(caster->destination_x == caster->x);
            assert(caster->destination_y == caster->y);
        }
        game_session_tick_floater_moves(&session, tick, &catalog);
    }
    assert(reached);
    assert(caster->active_order_action == 0);
    assert(caster->source_progress_08 == 5);
}

static void test_spore_deaths_go_through_the_native_damage_guard(void)
{
    /* FUN_004204bc: flag 0x8 blocks it; otherwise the amount is subtracted
       and a result below 1 starts the death with its sound and tallies. */
    static GameSession session;
    GameSessionAudioEvent event;
    GameFloaterStart *spore;
    GameRuntimeLocation *site;
    PadCatalog catalog;

    memset(&session, 0, sizeof(session));
    session.island_count = 1;
    add_test_worker(&session, 0, 0, 1000, 200, 1);
    session.floaters[0].current_hit_points = 3;
    game_session_apply_floater_damage(&session, &session.floaters[0], 1, -1);
    assert(session.floaters[0].current_hit_points == 2);
    assert((session.floaters[0].source_runtime_flags & 0x008U) == 0);
    assert(!game_session_pop_audio_event(&session, &event));

    /* Zero hit points without the flag still dies (the port used to skip). */
    session.floaters[0].current_hit_points = 0;
    game_session_apply_floater_damage(&session, &session.floaters[0], 1, -1);
    assert((session.floaters[0].source_runtime_flags & 0x008U) != 0);
    assert(session.floaters[0].source_death_timer == 0);
    assert(session.economy[0].floater_losses == 1);
    assert(game_session_pop_audio_event(&session, &event));
    assert(event.kind == GAME_SESSION_AUDIO_FLOATER_DEATH);

    /* An already dying floater keeps its death timer and makes no sound. */
    session.floaters[0].source_death_timer = 7;
    game_session_apply_floater_damage(&session, &session.floaters[0], 50, -1);
    assert(session.floaters[0].source_death_timer == 7);
    assert(session.economy[0].floater_losses == 1);
    assert(!game_session_pop_audio_event(&session, &event));

    /* FUN_0041e569 case 0: a Spore reaching a site flagged 0x200 dies through
       FUN_004204bc(current hit points, -1). */
    make_pad_catalog(&catalog);
    memset(&session, 0, sizeof(session));
    session.island_count = 1;
    session.islands[0].location_count = 1;
    site = &session.islands[0].locations[0];
    site->x = 1000;
    site->y = 200;
    site->owner_id = -1;
    site->source_value_14 = -1;
    site->source_flags = 0x200U;
    site->source_effect_timer_38 = 10; /* timed flag survives this tick */
    add_test_worker(&session, 0, 0, 1000, 200, 4);
    spore = &session.floaters[0];
    spore->type_index = 4;
    spore->source_subtype = 9;
    spore->current_hit_points = 6;
    spore->source_link_0c = -1;
    spore->active_order_action = 1;
    spore->movement_state = 1;
    spore->order_target_location = 0;
    spore->order_target_floater = -1;
    game_session_tick_floater_moves(&session, 1, &catalog);
    assert((spore->source_runtime_flags & 0x008U) != 0);
    assert(spore->current_hit_points == 0);
    assert(game_session_pop_audio_event(&session, &event));
    assert(event.kind == GAME_SESSION_AUDIO_FLOATER_DEATH);
}

/* Island 0 with a Spore (floater 0) at (100, 100) and free sites of the given
   renderer classes along y = 100, ten units apart starting at x = 200. */
static GameFloaterStart *setup_spore_sites(GameSession *session,
                                           const uint8_t *classes,
                                           unsigned int count)
{
    GameFloaterStart *spore;
    unsigned int index;

    memset(session, 0, sizeof(*session));
    session->island_count = 1;
    session->islands[0].location_count = (uint16_t)count;
    for (index = 0; index < count; ++index) {
        GameRuntimeLocation *site = &session->islands[0].locations[index];
        site->renderer_class = classes[index];
        site->owner_id = -1;
        site->source_value_14 = -1;
        site->source_location_slot_18 = -1;
        site->x = (uint16_t)(200 + index * 10);
        site->y = 100;
    }
    add_test_worker(session, 0, 0, 100, 100, 4);
    spore = &session->floaters[0];
    spore->type_index = 4;
    spore->source_subtype = 9;
    spore->current_hit_points = 4;
    spore->order_target_location = -1;
    spore->order_target_floater = -1;
    return spore;
}

static void test_spore_prefers_building_pads_until_markers_allow_sources(void)
{
    static GameSession session;
    static const uint8_t pad_and_source[2] = {0, 1};
    static const uint8_t source_only[1] = {1};
    GameFloaterStart *spore;

    /* FUN_0042219e: with no remaining marker the class-1 site is ignored. */
    spore = setup_spore_sites(&session, pad_and_source, 2);
    assert(game_session_assign_category4_subtype9_order(&session, 0, 1));
    assert(spore->active_order_action == 1);
    assert(spore->order_target_location == 0);
    assert(spore->movement_state == 1);
    assert(spore->has_move_order);
    assert(spore->destination_x == 200 && spore->destination_y == 100);

    /* Markers left and a zero site budget: the source replaces the pad
       without a roll. */
    spore = setup_spore_sites(&session, pad_and_source, 2);
    session.islands[0].leviathan_remaining_markers = 1;
    assert(game_session_assign_category4_subtype9_order(&session, 0, 1));
    assert(spore->order_target_location == 1);

    /* No pad at all: a marker is enough, whatever the roll returns. */
    spore = setup_spore_sites(&session, source_only, 1);
    session.islands[0].leviathan_remaining_markers = 1;
    session.islands[0].leviathan_site_budget = 3;
    assert(game_session_assign_category4_subtype9_order(&session, 0, 1));
    assert(spore->order_target_location == 0);

    /* ...and without markers the Spore finds nothing. */
    spore = setup_spore_sites(&session, source_only, 1);
    assert(!game_session_assign_category4_subtype9_order(&session, 0, 1));
    assert(spore->active_order_action == 0);
    assert(spore->order_target_location == -1);
}

static void test_spore_skips_claimed_sites_and_its_own_position(void)
{
    static GameSession session;
    static const uint8_t pads[3] = {0, 0, 0};
    GameFloaterStart *spore;

    spore = setup_spore_sites(&session, pads, 3);
    session.islands[0].locations[0].source_value_14 = 4; /* already claimed */
    session.islands[0].locations[1].x = 100;             /* distance 0 */
    assert(game_session_assign_category4_subtype9_order(&session, 0, 1));
    assert(spore->order_target_location == 2);

    /* A claimed record still qualifies when +0x10 and +0x24 are both 1. */
    spore = setup_spore_sites(&session, pads, 1);
    session.islands[0].locations[0].source_value_14 = 4;
    session.islands[0].locations[0].record_value_10 = 1;
    session.islands[0].locations[0].record_value_24 = 1;
    assert(game_session_assign_category4_subtype9_order(&session, 0, 1));
    assert(spore->order_target_location == 0);

    /* Other floaters never take this path. */
    spore = setup_spore_sites(&session, pads, 1);
    spore->source_subtype = 8;
    assert(!game_session_assign_category4_subtype9_order(&session, 0, 1));
    spore->source_subtype = 9;
    spore->source_runtime_flags = 0x008U; /* dying */
    assert(!game_session_assign_category4_subtype9_order(&session, 0, 1));
    assert(!game_session_assign_category4_subtype9_order(&session, 1, 1));
    assert(!game_session_assign_category4_subtype9_order(NULL, 0, 1));
}

static void test_moving_spore_retargets_only_on_its_cadence_once_claimed(void)
{
    static GameSession session;
    static const uint8_t pads[2] = {0, 0};
    GameFloaterStart *spore;

    spore = setup_spore_sites(&session, pads, 2);
    session.islands[0].locations[1].source_value_14 = 4;
    assert(game_session_assign_category4_subtype9_order(&session, 0, 1));
    assert(spore->order_target_location == 0);

    /* While the target's +0x14 is still -1 the Move order is kept, even on
       a reevaluation tick. */
    assert(!game_session_assign_category4_subtype9_order(&session, 0, 10));
    assert(spore->order_target_location == 0 && spore->has_move_order);

    /* Another Spore claims it and site 1 frees up: nothing happens off the
       (tick + index) % 10 cadence of FUN_0041e569. */
    session.islands[0].locations[0].source_value_14 = 4;
    session.islands[0].locations[1].source_value_14 = -1;
    assert(!game_session_assign_category4_subtype9_order(&session, 0, 11));
    assert(spore->order_target_location == 0 && spore->has_move_order);
    assert(game_session_assign_category4_subtype9_order(&session, 0, 20));
    assert(spore->order_target_location == 1);
    assert(spore->destination_x == 210);

    /* With no free site left the stale Move is dropped in place. */
    session.islands[0].locations[1].source_value_14 = 4;
    spore->x = 150;
    assert(!game_session_assign_category4_subtype9_order(&session, 0, 30));
    assert(spore->active_order_action == 0);
    assert(spore->order_target_location == -1);
    assert(spore->movement_state == 0 && !spore->has_move_order);
    assert(spore->destination_x == 150 && spore->destination_y == 100);
}

static void test_targetless_spore_loses_one_hp_every_128_ticks(void)
{
    static GameSession session;
    static const uint8_t none[1] = {0};
    GameFloaterStart *spore;

    spore = setup_spore_sites(&session, none, 0);
    assert(!game_session_assign_category4_subtype9_order(&session, 0, 127));
    assert(spore->current_hit_points == 4);
    assert(!game_session_assign_category4_subtype9_order(&session, 0, 128));
    assert(spore->current_hit_points == 3);
    assert(!game_session_assign_category4_subtype9_order(&session, 0, 256));
    assert(spore->current_hit_points == 2);
}

static void test_training_refreshes_the_new_subtype_combat_row(void)
{
    /* FUN_0045cd75 only stores subtype, level, +0x22 and +0x20; range, realm
       and speed are read live from FUN_00464242(type, subtype). A worker
       trained into a ranged subtype must stop using its worker range 0. */
    static GameSession session;
    static FloaterCatalog floaters;
    PadCatalog pads;
    BuildingRenderCatalog buildings = {0};
    GameRuntimeLocation *school;
    GameFloaterStart *worker;
    FloaterStats *trained;
    unsigned int slot;

    make_pad_catalog(&pads);
    make_floater_catalog(&floaters);
    trained = &floaters.rows[1]; /* type 0, subtype 1 */
    trained->attack_range = 120;
    trained->attack_realm = 2;
    trained->hit_points = 9;
    trained->max_attack_points = 4;
    trained->attack_strength = 6;
    trained->movement_speed = 7;
    assert(floater_catalog_find(&floaters, 0, 1) == trained);

    memset(&session, 0, sizeof(session));
    session.island_count = 1;
    session.islands[0].location_count = 1;
    school = &session.islands[0].locations[0];
    school->renderer_class = 0;
    school->owner_id = 0;
    school->source_value_14 = 0;
    school->record_value_10 = 0x2c;
    school->source_value_32 = 251;
    school->source_location_slot_18 = -1;
    school->charge_recent_floater = -1;
    school->charge_staff_task_handle = -1;
    for (slot = 0; slot < 8; ++slot) school->charge_floater_slots[slot] = -1;
    school->charge_floater_slots[0] = 0;
    add_test_worker(&session, 0, 0, 1000, 200, 0);
    worker = &session.floaters[0];
    worker->source_link_0c = -1;
    worker->source_runtime_flags = 0x20U;
    worker->movement_speed = 3;

    game_session_tick_item_animations_with_floaters(&session, &buildings,
                                                    &floaters, &pads);
    assert(worker->source_subtype == 1);
    assert(worker->attack_range == 120);
    assert(worker->attack_realm == 2);
    assert(worker->movement_speed == 7);
    assert(worker->charge_current == 4); /* row +8: max attack points */
    assert(worker->max_hit_points == 9); /* level 0: (0 + 2) * 9 / 2 */
    assert(worker->current_hit_points == worker->max_hit_points);
    assert(worker->max_attack_points == 4);
    assert(worker->has_wander_order == 1 && worker->wander_timer == 0);
}

static void test_trainee_death_frees_the_charge_task(void)
{
    /* FUN_0041e569 state 11 links the trainee without FUN_00421ec1: it keeps
       its CHARGE claim, and its death releases the task for another worker. */
    static GameSession session;
    FloaterCatalog floaters;
    PadCatalog pads;
    BuildingRenderCatalog buildings = {0};
    GameRuntimeLocation *school;
    int16_t handle;
    unsigned int slot;
    unsigned int tick;

    make_pad_catalog(&pads);
    make_floater_catalog(&floaters);
    memset(&session, 0, sizeof(session));
    session.island_count = 1;
    session.islands[0].location_count = 1;
    session.islands[0].floater_max_x[0] = 0x9ff;
    school = &session.islands[0].locations[0];
    school->renderer_class = 0;
    school->owner_id = 0;
    school->source_value_14 = 0;
    school->record_value_10 = 0x2c;
    school->source_value_32 = 1;
    school->source_location_slot_18 = 0;
    school->resource_stock[1] = 50;
    school->charge_recent_floater = -1;
    school->charge_staff_task_handle = -1;
    school->x = 1000;
    school->y = 200;
    for (slot = 0; slot < 8; ++slot) school->charge_floater_slots[slot] = -1;
    add_test_worker(&session, 0, 0, 1000, 200, 0);
    add_test_worker(&session, 1, 0, 1000, 200, 0);
    for (slot = 0; slot < 2; ++slot) {
        session.floaters[slot].source_link_0c = -1;
        session.floaters[slot].linked_task_slot = -1;
        session.floaters[slot].movement_speed = 3;
    }

    game_session_tick_item_animations_with_floaters(&session, &buildings,
                                                    &floaters, &pads);
    handle = school->charge_staff_task_handle;
    assert(handle >= 0);
    game_session_assign_local_resource_tasks(&session, &pads);
    assert(session.floaters[0].linked_task_slot == handle);
    for (tick = 1; tick < 5; ++tick)
        game_session_tick_floater_moves(&session, tick, &pads);
    assert(session.floaters[0].source_link_0c != -1); /* linked */
    assert(session.floaters[0].linked_task_slot == handle);

    game_session_retire_floater(&session, 0);
    assert(session.pending_events[(uint8_t)handle].active != 0);
    assert(session.pending_events[(uint8_t)handle].assigned_floater_count == 0);
    game_session_assign_local_resource_tasks(&session, &pads);
    assert(session.floaters[1].linked_task_slot == handle);
}

static void test_building_order_keeps_the_target_island(void)
{
    /* FUN_0045d867 stores the target floater's island and FUN_0045d8b2 the
       packet island in B+0x28, so a training building on island 0 can order
       its group against a target on island 1. */
    static GameSession session;
    GameRuntimeLocation *school;

    memset(&session, 0, sizeof(session));
    session.island_count = 2;
    session.islands[0].location_count = 1;
    session.islands[1].location_count = 2;
    school = &session.islands[0].locations[0];
    school->owner_id = 0;
    school->source_value_14 = 0;
    school->record_value_10 = 0x2c;
    school->source_location_slot_18 = 0;
    add_test_worker(&session, 0, 1, 500, 200, 1);

    assert(game_session_set_building_order(&session, 0, 0, 0, 6, 1, 0, 0));
    assert(school->building_order_genre == 6);
    assert(school->building_order_island == 1);
    assert(school->building_order_coordinate == 0);
    /* The target floater must be on the named island. */
    assert(!game_session_set_building_order(&session, 0, 0, 0, 8, 0, 0, 0));
    assert(game_session_set_building_order(&session, 0, 0, 0, 7, 1, 1, 0));
    assert(school->building_order_island == 1);
    assert(school->building_order_coordinate == 1);
    /* Genre 9 packs the point as (v + 5) / 10 on the target island. */
    assert(game_session_set_building_order(&session, 0, 0, 0, 9, 1, 300, 200));
    assert(school->building_order_island == 1);
    assert(school->building_order_coordinate == ((30U << 8) | 20U));
}

static void soldier(GameSession *session, unsigned int index, uint8_t owner,
                    uint16_t x, uint16_t building)
{
    GameFloaterStart *f;
    add_test_worker(session, index, 0, x, 200, owner);
    f = &session->floaters[index];
    f->type_index = owner;
    f->source_subtype = 1;
    f->current_hit_points = 60;
    f->max_hit_points = 60;
    f->charge_current = 20;
    f->attack_strength = 5;
    f->attack_level_flags = 2;
    f->movement_speed = 3;
    f->attack_period = 5;
    f->source_link_0c = 0;
    f->charge_source_island = 0;
    f->charge_source_location = building;
    f->linked_task_slot = -1;
    f->order_target_floater = -1;
    f->order_target_location = -1;
}

static GameRuntimeLocation *school(GameSession *session, uint16_t index,
                                   int32_t owner, uint16_t x)
{
    GameRuntimeLocation *b = &session->islands[0].locations[index];
    unsigned int slot;
    b->x = x;
    b->y = 200;
    b->owner_id = owner;
    b->source_value_14 = owner;
    b->record_value_10 = 0x2c + owner * 16;
    b->source_location_slot_18 = 0;
    b->charge_recent_floater = -1;
    b->charge_staff_task_handle = -1;
    for (slot = 0; slot < 8; ++slot) b->charge_floater_slots[slot] = -1;
    return b;
}

static void test_soldiers_fight_through_building_orders(void)
{
    /* FUN_004211bb case 8 advances DefendArea only after FUN_0041e569 ends
       the current state, so a defender strikes; FUN_0042219e copies a new
       building order onto a floater that is already attacking (it only
       waits while a strike, state 6/7, runs). */
    static GameSession session;
    PadCatalog pads;
    unsigned int tick;
    unsigned int index;

    make_pad_catalog(&pads);
    memset(&session, 0, sizeof(session));
    session.island_count = 1;
    session.islands[0].location_count = 2;
    for (index = 0; index < 5; ++index) {
        session.islands[0].floater_min_x[index] = 0;
        session.islands[0].floater_max_x[index] = 0x9ff;
    }
    session.random_state = 77;
    (void)school(&session, 0, 0, 600);
    (void)school(&session, 1, 1, 1300);
    soldier(&session, 0, 0, 700, 0);
    soldier(&session, 1, 1, 1000, 1);
    soldier(&session, 2, 1, 1020, 1);
    session.floaters[2].source_link_0c = -1; /* an unlinked enemy target */

    /* The defender guards its own spot; the attacker is sent at it. */
    assert(game_session_set_building_order(&session, 1, 0, 1, 9, 0, 1000, 200));
    assert(game_session_set_building_order(&session, 0, 0, 0, 6, 0, 1, 0));
    for (tick = 1; tick <= 600; ++tick)
        game_session_tick_floater_moves(&session, tick, &pads);
    assert(session.floaters[1].current_hit_points < 60);
    assert(session.floaters[0].current_hit_points < 60); /* defender struck */

    /* A new order reaches a floater still approaching its first target
       (a floater held in melee answers its holder instead, FUN_00421d82). */
    soldier(&session, 3, 0, 100, 0);
    session.floaters[0].source_link_0c = -1;
    session.floaters[3].charge_source_location = 0;
    assert(game_session_set_building_order(&session, 0, 0, 0, 6, 0, 2, 0));
    for (tick = 601; tick <= 610; ++tick)
        game_session_tick_floater_moves(&session, tick, &pads);
    assert(session.floaters[3].active_order_action == 6);
    assert(session.floaters[3].order_target_floater == 2);
    assert(game_session_set_building_order(&session, 0, 0, 0, 6, 0, 1, 0));
    for (tick = 611; tick <= 640 &&
         session.floaters[3].order_target_floater != 1; ++tick)
        game_session_tick_floater_moves(&session, tick, &pads);
    assert(session.floaters[3].order_target_floater == 1);
}

static void test_building_order_crosses_a_bridge_and_keeps_the_link(void)
{
    /* FUN_004211bb sends an order whose +0x40 island differs through
       FUN_004210a9 and replays it on arrival; FUN_0041e569 case 0x10 keeps
       +0x0c, and FUN_0042219e copies even an empty record (genre 0). */
    static GameSession session;
    PadCatalog pads;
    GameRuntimeLocation *bridge;
    GameFloaterStart *warrior;
    unsigned int tick;
    unsigned int index;

    make_pad_catalog(&pads);
    memset(&session, 0, sizeof(session));
    session.island_count = 2;
    session.islands[0].location_count = 2;
    session.islands[1].location_count = 1;
    for (index = 0; index < 5; ++index) {
        session.islands[0].floater_max_x[index] = 0x9ff;
        session.islands[1].floater_max_x[index] = 0x9ff;
    }
    session.random_state = 5;
    (void)school(&session, 0, 0, 600);
    bridge = &session.islands[0].locations[1];
    bridge->renderer_class = 2;
    bridge->source_flags = 1;
    bridge->owner_id = -1;
    bridge->bridge_neighbor_island = 1;
    bridge->x = 900;
    bridge->y = 200;
    bridge = &session.islands[1].locations[0];
    bridge->renderer_class = 2;
    bridge->source_flags = 1;
    bridge->owner_id = -1;
    bridge->bridge_neighbor_island = 0;
    bridge->x = 300;
    bridge->y = 230;
    soldier(&session, 0, 0, 700, 0);
    warrior = &session.floaters[0];
    soldier(&session, 1, 1, 600, 0);
    session.floaters[1].island_index = 1;
    session.floaters[1].source_link_0c = -1;

    /* Empty record: another action is ended. */
    warrior->active_order_action = 0x0e;
    game_session_tick_floater_moves(&session, 1, &pads);
    assert(warrior->active_order_action == 0);

    assert(game_session_set_building_order(&session, 0, 0, 0, 6, 1, 1, 0));
    game_session_tick_floater_moves(&session, 2, &pads);
    assert(warrior->movement_state == 0x11);
    assert(warrior->handoff_resume_action == 6);
    assert(warrior->order_target_floater == 1);
    for (tick = 3; tick < 1000 && warrior->island_index != 1; ++tick)
        game_session_tick_floater_moves(&session, tick, &pads);
    assert(warrior->island_index == 1);
    for (index = 0; index < 400 && warrior->active_order_action != 6; ++index)
        game_session_tick_floater_moves(&session, tick++, &pads);
    assert(warrior->active_order_action == 6);
    assert(warrior->order_target_floater == 1);
    assert(warrior->source_link_0c == 0);
    assert(warrior->charge_source_island == 0);
}

static void test_wounded_soldier_heals_in_its_building(void)
{
    /* FUN_0042219e sends a linked floater under a third of its hit points
       back to its building (action 2) when the +0x2a pool can refill it;
       FUN_0041e569 state 2 then gives one hit point per pool unit every
       ninth update inside the building (flag 1) and leaves when full. */
    static GameSession session;
    PadCatalog pads;
    GameRuntimeLocation *home;
    GameFloaterStart *wounded;
    unsigned int tick;
    unsigned int index;
    int entered = 0;

    make_pad_catalog(&pads);
    memset(&session, 0, sizeof(session));
    session.island_count = 1;
    session.islands[0].location_count = 1;
    for (index = 0; index < 5; ++index)
        session.islands[0].floater_max_x[index] = 0x9ff;
    home = school(&session, 0, 0, 600);
    home->resource_stock[GAME_RESOURCE_CRYSTAL_TONE] = 50;
    soldier(&session, 0, 0, 700, 0);
    wounded = &session.floaters[0];
    wounded->base_max_attack_points = 20;
    wounded->current_hit_points = 10; /* under 60 / 3 */

    for (tick = 1; tick <= 1000 && wounded->current_hit_points < 60; ++tick) {
        game_session_tick_floater_moves(&session, tick, &pads);
        if ((wounded->source_runtime_flags & 1U) != 0) {
            entered = 1;
            assert(wounded->x == home->x);
            assert(wounded->active_order_action == 2);
        }
    }
    assert(entered);
    assert(wounded->current_hit_points == 60);
    assert(home->resource_stock[GAME_RESOURCE_CRYSTAL_TONE] == 0);
    for (; tick <= 1100; ++tick)
        game_session_tick_floater_moves(&session, tick, &pads);
    assert((wounded->source_runtime_flags & 1U) == 0);
    assert(wounded->active_order_action != 2);
}

static void test_wounded_soldier_crosses_a_bridge_to_heal(void)
{
    /* FUN_0042219e sets action 2 toward a building on another island;
       FUN_004211bb stage 0 sends the floater over the bridge (state 0x11,
       action 9 with +0x46 = 1). The retreat check must not restart the
       order while the crossing runs, or the floater turns back on the
       bridge forever. */
    static GameSession session;
    PadCatalog pads;
    GameRuntimeLocation *bridge;
    GameRuntimeLocation *home;
    GameFloaterStart *wounded;
    unsigned int tick;
    unsigned int index;
    int crossed = 0;
    int entered = 0;

    make_pad_catalog(&pads);
    memset(&session, 0, sizeof(session));
    session.island_count = 2;
    session.islands[0].location_count = 2;
    session.islands[1].location_count = 1;
    for (index = 0; index < 5; ++index) {
        session.islands[0].floater_max_x[index] = 0x9ff;
        session.islands[1].floater_max_x[index] = 0x9ff;
    }
    home = school(&session, 0, 0, 600);
    home->resource_stock[GAME_RESOURCE_CRYSTAL_TONE] = 50;
    bridge = &session.islands[0].locations[1];
    bridge->renderer_class = 2;
    bridge->source_flags = 1;
    bridge->owner_id = -1;
    bridge->bridge_neighbor_island = 1;
    bridge->x = 900;
    bridge->y = 200;
    bridge = &session.islands[1].locations[0];
    bridge->renderer_class = 2;
    bridge->source_flags = 1;
    bridge->owner_id = -1;
    bridge->bridge_neighbor_island = 0;
    bridge->x = 300;
    bridge->y = 230;
    soldier(&session, 0, 0, 700, 0);
    wounded = &session.floaters[0];
    wounded->island_index = 1;
    wounded->current_hit_points = 10; /* under 60 / 3 */

    for (tick = 1; tick <= 3000 && wounded->current_hit_points < 60; ++tick) {
        game_session_tick_floater_moves(&session, tick, &pads);
        if (wounded->island_index == 0) crossed = 1;
        if ((wounded->source_runtime_flags & 1U) != 0) {
            entered = 1;
            assert(wounded->island_index == 0);
            assert(wounded->x == home->x);
            assert(wounded->active_order_action == 2);
        }
    }
    assert(crossed);
    assert(entered);
    assert(wounded->current_hit_points == 60);
}
