#include<stdio.h>

#include"helper.h"

void heap_traverse(struct heap *heap_in, void (fn)(struct heap_node *))
{
	struct heap_node *curr=heap_in->max->nxt;
	struct heap_node *curr_parent=NULL;
	struct heap_node *curr_first=heap_in->max;
	while(1) {
		if(curr!=curr_first) {
			curr=curr->nxt;
		} else {
			if(curr!=heap_in->max){
				//this means we are still moving up
				curr=curr_parent;
				curr_parent=curr->parent;
				if(curr->parent==NULL)
					//this means we are at top
					curr_first=heap_in->max;
				else
					curr_first=curr->nxt;
				fn(curr->child);
				curr->child=NULL;
			} else {
				//end of the top level
				fn(heap_in->max);
				break;
			}
		}

		if(curr->child!=NULL) {
			//move down
			curr_parent=curr;
			curr=curr->child;
			curr_first=curr;
		}
	}
}

struct heap_node *heap_meld(struct heap_node *tree1, struct heap_node *tree2)
{
	if(tree1->key>tree2->key) {
		heap_detach_node(tree2, 0);
		tree2->parent=tree1;
		if(tree1->child==NULL) {
			tree1->child=tree2;
			heap_mk_dbl_cir_lst(tree2);
		} else {
			heap_add_node(tree1->child, tree2);
		}
		tree1->degree++;
		return tree1;
	} else {
		heap_detach_node(tree1, 0);
		tree1->parent=tree2;
		if(tree2->child==NULL) {
			tree2->child=tree1;
			heap_mk_dbl_cir_lst(tree1);
		} else {
			heap_add_node(tree2->child, tree1);
		}
		tree2->degree++;
		return tree2;
	}
}

void heap_detach_children(struct heap_node *curr_max)
{
	struct heap_node *curr=curr_max->child;
	while(1) {
		struct heap_node *tmp=heap_detach_node(curr, 1);
		heap_add_node(curr_max, curr);
		if(curr==tmp)
			break;
		else
			curr=tmp;
	}
	curr_max->degree=0;
	curr_max->child=NULL;
}
