/* Include these
 * #include <stdint.h>
 * #include <nitlib/list.h>
 * #include <nitlib/hashmap.h>
 */

#ifdef TFL_IDEA_TYPE_SHORT_NAME
enum tfl_idea_type {
        SYS,
        FUNC,
        LIST,
        C_FUNC,
        MAP,
        AXIOM
};
#else
enum tfl_idea_type {
        TFL_SYS,
        TFL_FUNC,
        TFL_LIST,
        TFL_C_FUNC,
        TFL_MAP,
        TFL_AXIOM
};
#endif


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
tfl_idea_run(struct tfl_idea *idea, struct tfl_idea *input);
