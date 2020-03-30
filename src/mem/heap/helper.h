#ifndef HELPER_H
#define HELPER_H

#include"heap.h"

void traverse(struct heap *, void (fn)(struct node *));
struct node *meld(struct node *, struct node *);
void detach_children(struct node *);

#endif
