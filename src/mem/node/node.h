#ifndef NODE_H
#define NODE_H

#include"../mem.h"

struct node
{
	int val;
	struct node *parent, *child;
	struct node *nxt, *prev;
	void *payload;
};

struct node *init_list(void *, int);
void de_init_list(struct node *);
struct node *move_first(struct node *);
void add_node(struct node *, struct node *);
void remove_node(struct node *);
void del_node(struct node *);

#endif
