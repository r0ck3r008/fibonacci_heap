#ifndef NODE_H
#define NODE_H

#include"../mem.h"

struct node
{
	int val;
	int loser;
	int children;
	struct node *parent, *child;
	struct node *nxt, *prev;
	void *payload;
};

struct node *init_node(void *, int);
struct node *move_to_start(struct node *);
struct node *move_to_finish(struct node *);
void add_node(struct node *, struct node *);
void make_start(struct node *);
struct node *find_max(struct node *);
void swap_nodes(struct node *, struct node *);
void print_list(struct node *);
void de_init_list(struct node *);
void detach_node(struct node *);
void dealloc_node(struct node *);

#endif
