#include <stdint.h>
#include <stdlib.h>

#define NIT_SHORT_NAMES
#include <nitlib/list.h>
#include <nitlib/hashmap.h>

#define TFL_IDEA_TYPE_SHORT_NAME
#include "idea.h"

struct tfl_idea *
tfl_idea_run(struct tfl_idea *idea, struct tfl_idea *input);

struct tfl_idea *
tfl_idea_map_get(struct tfl_idea *idea, struct tfl_idea *input)
{
	return hashmap_get(idea->dat.map, &input, sizeof(input));
}

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
