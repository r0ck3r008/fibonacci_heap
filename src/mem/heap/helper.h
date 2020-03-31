#ifndef HEAP_HELPER_H
#define HEAP_HELPER_H

#include"../heap.h"

void heap_traverse(struct heap *,
			void (fn)(struct heap_node *));
struct heap_node *heap_meld(struct heap_node *,
			struct heap_node *);
void heap_detach_children(struct heap_node *);

#endif
