#include<stdio.h>
#include<string.h>

#include"alloc.h"
#include"node.h"

struct hmap_node *hmap_init_node(char *key, struct node *node_addr)
{
	struct hmap_node *ret=hmap_alloc("struct hmap_node", 1);
	char *new_key=hmap_alloc("char", 64);
	sprintf(new_key, "%s", key);
	ret->key=key;
	ret->node_addr=node_addr;
	ret->nxt=NULL;

	return ret;
}

void hmap_de_init_list(struct hmap_node *start)
{
	struct hmap_node *curr=start->nxt;
	while(start->nxt!=NULL)
		hmap_dealloc("struct hmap_node", start->nxt, 1);

	hmap_dealloc("struct hmap_node", start, 1);
}

void hmap_add_node(struct hmap_node *start, struct hmap_node *new)
{
	struct hmap_node *curr=start;
	for(curr; curr->nxt!=NULL; curr=curr->nxt);

	curr->nxt=new;
}

struct node *hmap_find_node(struct hmap_node *start, char *key)
{
	struct hmap_node *curr=start;
	int flag=0;
	for(curr; curr!=NULL; curr=curr->nxt) {
		if(!strcmp(curr->key, key)) {
			flag=1;
			break;
		}
	}

	if(!flag)
		return NULL;
	return curr->node_addr;
}
