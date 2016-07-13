#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include <unistd.h>

#define NIT_SHORT_NAMES
#include <nitlib/list.h>
#include <nitlib/hashmap.h>

#include "idea.h"

extern struct tfl_idea the_term;

struct tfl_idea *
term_print(struct tfl_idea *idea)
{
	printf("%s", idea->dat.bytes);
	fflush(stdout);

	return NULL;
}

struct tfl_idea *
change(struct tfl_idea *idea)
{
	return tfl_idea_run(idea->sys, idea);
}

struct tfl_idea *
decide(struct tfl_idea *idea)
{
	usleep(8000 * 10);
	tfl_idea_run(&the_term, idea);

	if (*idea->dat.bytes == '!')
	        *idea->dat.bytes = '?';
	else
		*idea->dat.bytes = '!';

	return idea;
}

struct tfl_idea the_thought;

struct tfl_idea *
figure(struct tfl_idea *idea)
{
	(void) idea;

	return change(&the_thought);
}

struct tfl_idea the_term = {
	.dat.c_func = term_print,
	.type = TFL_C_FUNC,
	.sys = NULL
};

struct tfl_idea the_time = {
	.dat.c_func = change,
	.type = TFL_C_FUNC,
	.sys = NULL
};

struct tfl_idea the_understanding = {
	.dat.c_func = figure,
	.type = TFL_C_FUNC,
	.sys = NULL
};

struct tfl_idea the_context = {
	.dat.c_func = decide,
	.type = TFL_C_FUNC,
	.sys = NULL
};

struct tfl_idea the_thought = {
	.dat.bytes = (char []) { "! " },
	.type = TFL_AXIOM,
	.sys = &the_context
};

struct tfl_idea *
tfl_world_new(void)
{
	return tfl_idea_map_new(&the_understanding, 0);
}

struct tfl_player {
	struct tfl_idea *world;
	struct tfl_idea *time;
} player;

void
tfl_change_the_world(struct tfl_player *player)
{
	player->world = tfl_idea_run(player->time, player->world);
}

void
tfl_player_run(struct tfl_player *player)
{
	while (1)
		tfl_change_the_world(player);

}

int
main(int argc, char *argv[])
{
	player.world = tfl_world_new();
	/* tfl_idea_map_add(player.world, &the_thought, */
	/* 		 &the_thought); */
	player.time = &the_time;
	tfl_player_run(&player);
}

