#ifndef NODE_H
#define NODE_H

#include"../mem.h"

struct node
{
	int key;
	void *payload;
	int child_cut;
	int degree;
	struct node *parent, *nxt, *prev, *child;
};

struct node *init_node(int, void *);
void mk_dbl_cir_lst(struct node *);
struct node *detach_node(struct node *, int);
struct node *de_init_node(struct node *);
void de_init_list(struct node *);
void add_node(struct node *, struct node *);
struct node *find_max(struct node *);

#endif
