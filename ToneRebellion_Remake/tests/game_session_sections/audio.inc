/* Effect SOUND rules (FUN_00416a9a creates the instance, FUN_004181a6 plays
   it): death/birth/build sounds are tagged with the instance island and play
   only while that island is displayed on the island screen. */

static void setup_audio_session(GameSession *session)
{
    setup_panic_island(session, 2, 1);
    session->island_count = 3;
    session->floaters[0].island_index = 1;
    session->floaters[0].current_hit_points = 3;
    session->floaters[2].island_index = 1;
}

static void kill_with_power(GameSession *session, unsigned int index)
{
    unsigned int tries;
    for (tries = 0; tries < 500 &&
         session->floaters[index].current_hit_points != 0; ++tries)
        (void)game_session_damage_floater_from_power(session, index, 5000);
    assert(session->floaters[index].current_hit_points == 0);
}

static void test_death_queues_one_island_tagged_event(void)
{
    GameSession session;
    GameSessionAudioEvent event;

    setup_audio_session(&session);
    kill_with_power(&session, 0);
    assert(game_session_pop_audio_event(&session, &event));
    assert(event.kind == GAME_SESSION_AUDIO_FLOATER_DEATH);
    assert(event.owner_id == 0);
    assert(event.island == 1);
    /* Flag 0x008 blocks a second death event for the same floater. */
    assert(!game_session_pop_audio_event(&session, &event));
    assert(game_session_damage_floater_from_power(&session, 0, 5000) == 0);
    assert(!game_session_pop_audio_event(&session, &event));
}

static void test_leviathan_death_uses_the_levdeath_owner(void)
{
    GameSession session;
    GameSessionAudioEvent event;

    setup_audio_session(&session);
    session.floaters[2].current_hit_points = 1;
    kill_with_power(&session, 2);
    assert(game_session_pop_audio_event(&session, &event));
    /* FUN_00416a9a case 1: raw type 4 selects levdeath. */
    assert(event.owner_id == 4 && event.island == 1);
}

static void test_non_lethal_hit_makes_no_sound(void)
{
    GameSession session;
    GameSessionAudioEvent event;
    unsigned int tries;

    setup_audio_session(&session);
    session.floaters[0].current_hit_points = 30000;
    for (tries = 0; tries < 20; ++tries)
        (void)game_session_damage_floater_from_power(&session, 0, 1);
    assert(session.floaters[0].current_hit_points > 0);
    assert(!game_session_pop_audio_event(&session, &event));
}

static void test_audio_events_play_only_on_the_displayed_island(void)
{
    GameSession session;
    GameSessionAudioEvent event;

    memset(&session, 0, sizeof(session));
    assert(game_session_queue_audio_event_at(
        &session, GAME_SESSION_AUDIO_FLOATER_DEATH, 0, 1));
    assert(game_session_pop_audio_event(&session, &event));
    assert(game_session_audio_event_is_audible(&event, 1, 1));
    assert(!game_session_audio_event_is_audible(&event, 1, 0));
    assert(!game_session_audio_event_is_audible(&event, 0, 1));

    assert(game_session_queue_audio_event_at(
        &session, GAME_SESSION_AUDIO_BUILD, 2, 2));
    assert(game_session_queue_audio_event_at(
        &session, GAME_SESSION_AUDIO_FLOATER_BIRTH, 4, 2));
    assert(game_session_pop_audio_event(&session, &event));
    assert(game_session_audio_event_is_audible(&event, 1, 2));
    assert(!game_session_audio_event_is_audible(&event, 1, 1));
    assert(game_session_pop_audio_event(&session, &event));
    assert(!game_session_audio_event_is_audible(&event, 1, 1));

    /* An event without an island never sounds. */
    assert(game_session_queue_audio_event(
        &session, GAME_SESSION_AUDIO_FLOATER_DEATH, 0));
    assert(game_session_pop_audio_event(&session, &event));
    assert(!game_session_audio_event_is_audible(&event, 1, 0));

    /* Casts carry the caster island in owner_id. */
    assert(game_session_queue_cast_audio(&session, 1, 0));
    assert(game_session_pop_audio_event(&session, &event));
    assert(game_session_audio_event_is_audible(&event, 1, 1));
    assert(!game_session_audio_event_is_audible(&event, 1, 0));

    /* Bridge island is unresolved (FUN_004669bd): stays ungated. */
    assert(game_session_queue_audio_event(
        &session, GAME_SESSION_AUDIO_BRIDGE, -1));
    assert(game_session_pop_audio_event(&session, &event));
    assert(game_session_audio_event_is_audible(&event, 1, 0));
}

static void test_audio_queue_is_fifo_and_bounded(void)
{
    GameSession session;
    GameSessionAudioEvent event;
    unsigned int i;

    memset(&session, 0, sizeof(session));
    for (i = 0; i < GAME_SESSION_MAX_AUDIO_EVENTS; ++i)
        assert(game_session_queue_audio_event_at(
            &session, GAME_SESSION_AUDIO_FLOATER_DEATH, 0, (uint8_t)(i % 7)));
    assert(!game_session_queue_audio_event_at(
        &session, GAME_SESSION_AUDIO_FLOATER_DEATH, 0, 0));
    for (i = 0; i < GAME_SESSION_MAX_AUDIO_EVENTS; ++i) {
        assert(game_session_pop_audio_event(&session, &event));
        assert(event.island == i % 7);
    }
    assert(!game_session_pop_audio_event(&session, &event));
}

static void test_audio_effect_sounds(void)
{
    test_death_queues_one_island_tagged_event();
    test_leviathan_death_uses_the_levdeath_owner();
    test_non_lethal_hit_makes_no_sound();
    test_audio_events_play_only_on_the_displayed_island();
    test_audio_queue_is_fifo_and_bounded();
}
