#ifndef HEAP_ALLOC_H
#define HEAP_ALLOC_H

#include"../heap.h"

void *heap_alloc(char *, int);
void heap_dealloc(char *, void *, int);

#endif
