#include<stdio.h>

#include"alloc.h"
#include"node.h"
#include"helper.h"
#include"heap.h"

struct heap *heap_init(int key, char *hash)
{
	struct heap *new=heap_alloc("struct heap", 1);
	new->max=heap_init_node(key, hash);

	return new;
}

void heap_de_init(struct heap *heap_in)
{
	if(heap_in->max!=NULL)
		heap_traverse(heap_in, heap_de_init_list);

	heap_dealloc("struct heap", heap_in, 1);
}

struct heap_node *heap_insert(struct heap *heap_in, int key, char *hash)
{
	struct heap_node *new=heap_init_node(key, hash);

	heap_add_node(heap_in->max, new);
	if(new->key>heap_in->max->key)
		heap_in->max=new;

	return new;
}

struct heap_node *heap_remove_max(struct heap *heap_in)
{
	if(heap_in->max==NULL)
		//empty heap
		return NULL;
	struct heap_node *curr_max=heap_in->max;
	if(curr_max->degree)
		heap_detach_children(curr_max);
	struct heap_node *curr;
	if((curr=heap_detach_node(curr_max, 1))==curr_max) {
		//there is only one node
		heap_in->max=NULL;
		goto exit;
	}

	heap_in->max=heap_find_max(curr);
	curr=heap_in->max->nxt;
	while(1) {
		struct heap_node *tmp=curr->nxt;
		int flag=0;
		for(tmp; tmp!=curr; tmp=tmp->nxt) {
			//loop through the list to compare with curr
			//printf("Tmp: %d\tCurr: %d\n", tmp->key, curr->key);
			if(tmp->degree==curr->degree) {
				//we always choose the winning tree as current
				curr=heap_meld(tmp, curr);
				flag=1;
				break;
			}
		}
		if(!flag && curr!=heap_in->max)
			//move ahead if current has no more left to meld
			curr=curr->nxt;
		else
			break;
	}
exit:
	return curr_max;
}

void heap_inc_key(struct heap *heap_in, struct heap_node *trgt, int set_to)
{
	trgt->key=set_to;

	if(trgt->parent!=NULL && trgt->key > trgt->parent->key) {
		struct heap_node *curr=trgt->parent;
		while(curr!=NULL && curr->child_cut!=0) {
			struct heap_node *tmp=curr->parent;
			heap_detach_node(curr, 0);
			heap_add_node(heap_in->max, curr);
			curr->child_cut=0;
			curr=tmp;
		}
		heap_detach_node(trgt, 0);
		heap_add_node(heap_in->max, trgt);
	}
	if(trgt->key > heap_in->max->key)
		heap_in->max=trgt;
}
