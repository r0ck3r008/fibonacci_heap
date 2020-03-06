#include<stdio.h>

#include"helper.h"
#include"heap.h"

struct heap *init_heap(void *payload, int val)
{
	struct heap *heap_new=alloc("struct heap", 1);
	heap_new->trees=init_node(payload, val);

	return heap_new;
}

void insert(struct heap *heap_in, void *payload, int val)
{
	struct node *new_node=init_node(payload, val);
	add_node(heap_in->trees, new_node);

	if(heap_in->trees->val < new_node->val) {
		make_start(new_node);
		heap_in->trees=new_node;
	}
}

struct node *remove_max(struct heap *heap_in)
{
	if(heap_in->trees==NULL)
		return NULL;

	if(heap_in->trees->children)
		detach_children(heap_in, heap_in->trees);
	struct node *curr_max=heap_in->trees;
	if(curr_max->nxt!=NULL) {
		heap_in->trees=curr_max->nxt;
		detach_node(curr_max);
		heap_in->trees=find_max(heap_in->trees);
	} else {
		//if even after detaching children as first operation, the list
		//curr_max->nxt is null, then it must be a single element in
		//tree, thus not performing remove_max
		detach_node(curr_max);
		heap_in->trees=NULL;
	}

	int flag=1;
	struct node *curr=heap_in->trees;
	while(curr!=NULL) {
		flag=0;
		struct node *tmp;
		for(tmp=heap_in->trees; tmp!=NULL;) {
			if(tmp!=curr && tmp->children==curr->children) {
				flag=1;
				meld(tmp, curr);
				break;
			}
			tmp=tmp->nxt;
		}
		if(flag)
			curr=heap_in->trees;
		else
			curr=curr->nxt;
	}

	return curr_max;
}

void print_heap(struct heap *heap_in)
{
	if(heap_in->trees==NULL)
		return;
	traverse(heap_in, print_list);
}

void de_init_heap(struct heap *heap_in)
{
	traverse(heap_in, de_init_list);

	dealloc(heap_in, "struct heap", 1);
}
