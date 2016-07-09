#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>

#include <unistd.h>

#define NIT_SHORT_NAMES
#include <nitlib/list.h>
#include <nitlib/hashmap.h>

#include "idea.h"



/* struct tfl_player { */
/* 	struct tfl_idea *shell; */
/* 	/\* struct tfl_idea *pre; *\/ */
/* 	/\* struct tfl_idea *fig; *\/ */
/* 	struct tfl_idea *kernel; */
/* 	struct tfl_idea *conv; */
/* }; */

extern struct tfl_idea the_term;

struct tfl_idea *
term_print(struct tfl_idea *idea)
{
	sleep(1);

	if (idea == &the_term)
		printf("THE TERM!\n");

	return &the_term;
}

struct tfl_idea the_term = {
	.dat.c_func = term_print,
	.type = TFL_C_FUNC,
	.sys = NULL
};

struct tfl_player {
	struct tfl_idea *old_world;
	struct tfl_idea *new_world;
	struct tfl_idea *main;
} player;

void
tfl_player_run(struct tfl_player *player)
{
	/* struct tfl_idea *the_world = player->the_world; */

	while (1) {
		struct tfl_idea *old_world = player->old_world;

	        player->old_world = tfl_idea_run(player->main, old_world);
	}

}

int
main(int argc, char *argv[])
{
	player.old_world = &the_term;
	player.main = &the_term;
	tfl_player_run(&player);
	/* tfl_idea_run(&the_term, &the_term); */
	/* the_term.dat.c_func(&the_term); */
}

