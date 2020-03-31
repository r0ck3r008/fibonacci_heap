#ifndef HMAP_ALLOC_H
#define HMAP_ALLOC_H

#include"node.h"
#include"hmap.h"

void *hmap_alloc(char *, int);
void hmap_dealloc(char *, void *, int);

#endif
