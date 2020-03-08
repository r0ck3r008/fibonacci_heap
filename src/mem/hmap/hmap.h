#ifndef HMAP_H
#define HMAP_H

#include"../mem.h"
#define HMAP_SIZE 100

struct hmap
{
	struct node **map;
};

struct data
{
	struct node *addr;
	char *key;
};

struct hmap *init_hmap();
struct data *init_data(struct node *, char *);
int hash_it(char *);
void insert_hmap(struct hmap *, char *, int);
struct node *get_addr(struct hmap *, char *);
void de_init_hmap(struct hmap *);

#endif
