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
		return NULL;

	struct heap_node *curr_max=heap_in->max;
	if(curr_max->degree)
		heap_detach_children(curr_max);

	struct heap_node *tmp_lst=heap_init_node(0, NULL);
	tmp_lst->degree=-1;
	struct heap_node *curr=curr_max->nxt;
	for(curr; curr!=curr_max;) {
		struct heap_node *tmp=heap_find_by_deg(tmp_lst, curr->degree);
		heap_detach_node(curr, 0);
		if(tmp==NULL) {
			heap_add_node(tmp_lst, curr);
		} else {
			while(tmp!=NULL) {
				heap_detach_node(tmp, 0);
				curr=heap_meld(curr, tmp);
				tmp=heap_find_by_deg(tmp_lst, curr->degree);
			}
			heap_add_node(tmp_lst, curr);
		}
		curr=heap_in->max->nxt;
	}

	heap_detach_node(curr_max, 0);
	curr=heap_detach_node(tmp_lst, 1);
	if(curr==tmp_lst)
		heap_in->max=NULL;
	else
		heap_in->max=heap_find_max(curr);

exit:
	return curr_max;
}

void heap_inc_key(struct heap *heap_in, struct heap_node *trgt, int set_to)
{
	trgt->key=set_to;

	if((trgt->parent!=NULL) && (trgt->key > trgt->parent->key)) {
		struct heap_node *curr=trgt;
		while(curr!=NULL) {
			struct heap_node *tmp=curr->parent;
			heap_detach_node(curr, 0);
			heap_add_node(heap_in->max, curr);
			curr->child_cut=0;
			if(tmp!=NULL) {
				if(tmp->child==curr) {
					tmp->child=NULL;
					tmp->degree=0;
				}
				if(!tmp->child_cut) {
					tmp->child_cut=1;
					break;
				}
			} else {
				curr=tmp;
			}
		}
	}
	if(trgt->key > heap_in->max->key)
		heap_in->max=trgt;
}
