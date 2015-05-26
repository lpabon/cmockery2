
#include <stdlib.h>

struct game_event;

void run_game(void (*event_handler)(struct game_event *event), struct game_event *events[], int num_events)
{
	int i = rand() % num_events;
	event_handler(events[i]);
} /* run_game */
