#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define NIT_SHORT_NAMES
#include <nitlib/list.h>
#include <nitlib/hashmap.h>

enum tfl_idea_type {
	SYS,
	FUNC,
	LIST,
	C_FUNC,
	MAP,
	AXIOM
};

struct tfl_list {
	struct nit_dlist dlist;
	struct tfl_idea *idea;
};

struct tfl_idea {

	union {
		struct tfl_list *list;
		struct nit_hashmap *map;
		struct tfl_idea *(*c_func)(struct tfl_idea *idea);
		char *bytes;
	} dat;

	enum tfl_idea_type type;
	struct tfl_idea *sys;
};

struct tfl_idea *
tfl_idea_map_get(struct tfl_idea *idea, struct tfl_idea *input)
{
	return hashmap_get(idea->dat.map, &input, sizeof(input));
}

struct tfl_idea *
tfl_idea_run(struct tfl_idea *idea, struct tfl_idea *input);

struct tfl_idea *
tfl_idea_func(struct tfl_idea *idea, struct tfl_idea *input)
{
	struct tfl_list *list = idea->dat.list;

        foreach (list)
		input = tfl_idea_run(list->idea, input);

	return input;
}

struct tfl_idea *
tfl_idea_run(struct tfl_idea *idea, struct tfl_idea *input)
{
	if (!idea)
		return NULL;

	switch (idea->type) {
	case SYS:
	case FUNC:
	case LIST:
		return tfl_idea_func(idea, input);
	case C_FUNC:
		return idea->dat.c_func(input);
	case MAP:
	        return tfl_idea_map_get(idea, input);
	case AXIOM:
		return NULL;
	}

	return NULL;
}

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
	if (idea == &the_term)
		printf("THE TERM!\n");
	return NULL;
}

struct tfl_idea the_term = {
	.dat.c_func = term_print,
	.type = C_FUNC,
	.sys = NULL
};

int
main(int argc, char *argv[])
{
	tfl_idea_run(&the_term, &the_term);
	/* the_term.dat.c_func(&the_term); */
}

