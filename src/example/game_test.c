#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <inttypes.h>
#include <cmockery.h>

struct game_event {
    int id;
    const char *message;
};

extern void run_game(void (*event_handler)(struct game_event *), struct game_event *events[], int num_events);

/* Our version of "expect_string()". It only compares as much of the message as given by the check-string length. */
static int check_event_message(const uintmax_t value, const uintmax_t check_value_data)
{
    const char *message = (const char *)value;
    const char *check = (const char *)check_value_data;
    assert_non_null(message);
    assert_non_null(check);

    /* Compare only the first part of the message determined by the check-string. */
    return( memcmp(message, check, strlen(check)) == 0 );
} /* check_event_message */

static void my_event_handler1(struct game_event *event)
{
    check_expected(event->id);
} /* my_event_handler1 */

static void my_event_handler2(struct game_event *event)
{
    check_expected(event->message);
} /* my_event_handler1 */

static void test_run_game1(void **state)
{
    int i;
    uintmax_t event_ids[5] = { 0, 1, 2, 3, 4 };

    struct game_event game_events[5] = {
        { 3, "Event 3" },
        { 1, "Event 1" },
        { 4, "Event 4" },
        { 2, "Event 2" },
        { 0, "Event 0" },
    };

    struct game_event *events[5];

    /* Populate the event list. */
    for (i = 0; i < 5; i++) events[i] = &game_events[i];

    expect_in_set(my_event_handler1, event->id, event_ids);
    run_game(my_event_handler1, events, 5);
} /* test_run_game */

static void test_run_game2(void **state)
{
    int i;

    struct game_event game_events[5] = {
        { 3, "Event: BANG" },
        { 1, "Event: BONG" },
        { 4, "Event: PING" },
        { 2, "Event: ZOOM" },
        { 0, "Event: POP" },
    };

    struct game_event *events[5];

    /* Populate the event list. */
    for (i = 0; i < 5; i++) events[i] = &game_events[i];

    expect_check(my_event_handler2, event->message, check_event_message, "Event: ");
    run_game(my_event_handler2, events, 5);
} /* test_run_game2 */

int main(void) {
    const UnitTest tests[] = {
        unit_test(test_run_game1),
        unit_test(test_run_game2),
    };
    return run_tests(tests, "game");
}
