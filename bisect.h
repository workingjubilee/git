#ifndef BISECT_H
#define BISECT_H

struct commit_list;
struct repository;
#define BISECT_FIND_ALL	(1U<<0)
#define BISECT_FIRST_PARENT	(1U<<1)

/*
 * Find bisection. If something is found, `reaches` will be the number of
 * commits that the best commit reaches. `all` will be the count of
 * non-SAMETREE commits. If nothing is found, `list` will be NULL.
 * Otherwise, it will be either all non-SAMETREE commits or the single
 * best commit, as chosen by the flag `BISECT_FIND_ALL`.
 */
void find_bisection(struct commit_list **list, int *reaches, int *all,
		    unsigned bisect_flags);

struct commit_list *filter_skipped(struct commit_list *list,
				   struct commit_list **tried,
				   int show_all,
				   int *count,
				   int *skipped_first);

#define BISECT_SHOW_ALL		(1<<0)
#define REV_LIST_QUIET		(1<<1)

struct rev_list_info {
	struct rev_info *revs;
	int flags;
	int show_timestamp;
	int hdr_termination;
	const char *header_prefix;
};

/*
 * Coordinates a bisection by examining input made available so far,
 * setting up internal variables, then calling a bisection with them.
 * no_checkout directs this to only update BISECT_HEAD refs.
 *
 * Exit code 10 on successful bisection, so caller should exit with 0.
 * Exit code 4 when no commits were found to bisect through.
 * Exit code 1 MAY result from skipping the commit it would report.
 *
 * Otherwise, returns a call to command handlers which choose an exit.
 */
int bisect_next_all(struct repository *r,
		    const char *prefix,
		    int no_checkout);

int estimate_bisect_steps(int all);

void read_bisect_terms(const char **bad, const char **good);

int bisect_clean_state(void);

#endif
