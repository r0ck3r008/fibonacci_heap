#include<stdio.h>
#include<string.h>

#include"hmap.h"

struct hmap *init_hmap()
{
	struct hmap *h_map=alloc("struct hmap", 1);
	h_map->map=alloc("struct node *", HMAP_SIZE);
	for(int i=0; i<HMAP_SIZE; i++)
		h_map->map[i]=NULL;

	return h_map;
}

struct data *init_data(struct node *hash_node, char *key)
{
	struct data *hmap_data=alloc("struct data", 1);
	hmap_data->addr=hash_node;
	hmap_data->key=key;

	return hmap_data;
}

int hash_it(char *key)
{
	//the hash value is just a serialized integer representation of the char *hash
	char *k=key;
	int sum=0;
	while(*k!='\0') {
		sum+=(int)*k;
		k+=sizeof(char);
	}

	return sum%HMAP_SIZE;
}

struct node *insert_hmap(struct hmap *hmap_in, char *key, int val)
{
	int k=hash_it(key);
	struct node *heap_node=init_node((void *)key, val);
	struct data *hmap_data=init_data(heap_node, key);
	struct node *hmap_node=init_node((void *)hmap_data, val);

	if(hmap_in->map[k]==NULL) {
		hmap_in->map[k]=hmap_node;
	} else {
		add_node(hmap_in->map[k], hmap_node);
	}

	return heap_node;
}

struct node *get_addr(struct hmap *hmap_in, char *key)
{
	int k=hash_it(key);
	struct node *hmap_node=hmap_in->map[k];
	if(hmap_node==NULL) {
		return NULL;
	} else if(hmap_node->nxt!=NULL) {
		struct node *curr=hmap_in->map[k];
		int flag=0;
		for(curr; curr!=NULL; curr=curr->nxt) {
			if(!strcmp(((struct data *)curr->payload)->key, key)) {
				flag=1;
				break;
			}
		}
		if(flag)
			return ((struct data *)curr->payload)->addr;
		else
			return NULL;
	} else {
		return ((struct data *)hmap_node->payload)->addr;
	}
}

void de_init_hmap(struct hmap *hmap_in)
{
	for(int i=0; i<HMAP_SIZE; i++) {
		if(hmap_in->map[i]!=NULL) {
			struct node *curr=hmap_in->map[i];
			for(curr; curr!=NULL; curr=curr->nxt)
				dealloc((struct data *)curr->payload,
					"struct data", 1);
			de_init_list(hmap_in->map[i]);
		}
	}
	dealloc(hmap_in->map, "struct node *", HMAP_SIZE);

	dealloc(hmap_in, "struct hmap", 1);
}
