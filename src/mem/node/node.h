#ifndef NODE_H
#define NODE_H

#include"../mem.h"

struct node
{
	int val;
	struct node *parent;
	struct node *nxt, *prev;
	void *payload;
};

struct node *init_node(void *, int);
struct node *init_list();
void de_init_list(struct node *);
void add_node(struct node *, struct node *);
void del_node(struct node *);

#endif
