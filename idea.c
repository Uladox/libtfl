#include <stdint.h>
#include <stdlib.h>

#define NIT_SHORT_NAMES
#include <nitlib/list.h>
#include <nitlib/hashmap.h>

#define TFL_IDEA_TYPE_SHORT_NAME
#include "idea.h"

static int
map_idea_compare(const void *entry_key, uint32_t entry_key_size,
		 const void *key, uint32_t key_size)
{
	(void) entry_key_size;
	(void) key_size;

	return entry_key == key;
}

static void
map_idea_free(void *key, void *storage)
{
	(void) key;
	(void) storage;

	return;
}

struct tfl_idea *
tfl_idea_map_new(struct tfl_idea *sys, unsigned int sequence)
{
	struct tfl_idea *idea = malloc(sizeof(*idea));

	idea->type = MAP;
	idea->sys = sys;
	idea->dat.map = hashmap_new(sequence, map_idea_compare, map_idea_free);

	return idea;
}

struct tfl_idea *
tfl_idea_map_get(struct tfl_idea *idea, struct tfl_idea *input)
{
	return hashmap_get(idea->dat.map, &input, sizeof(input));
}

enum nit_map_occured
tfl_idea_map_add(struct tfl_idea *map, struct tfl_idea *key,
		 struct tfl_idea *value)
{
	return nit_hashmap_add(map->dat.map, key, sizeof(key), value);
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
