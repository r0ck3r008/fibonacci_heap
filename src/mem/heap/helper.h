#ifndef HELPER_H
#define HELPER_H

#include"heap.h"

//helper functions
void traverse(struct heap *,void *(*fn)(struct node *),
		struct node *);
int comp_nodes(struct node *, struct node *);
void *find(struct node *);
void meld(struct node *, struct node *);
void detach_children(struct heap *, struct node *);

#endif
