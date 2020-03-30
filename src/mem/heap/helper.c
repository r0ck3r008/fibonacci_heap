#include<stdio.h>

#include"helper.h"

void traverse(struct heap *heap_in, void (fn)(struct node *))
{
	struct node *curr=heap_in->max->nxt;
	struct node *curr_parent=NULL;
	struct node *curr_first=heap_in->max;
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

struct node *meld(struct node *tree1, struct node *tree2)
{
	if(tree1->key>tree2->key) {
		detach_node(tree2, 0);
		tree2->parent=tree1;
		if(tree1->child==NULL) {
			tree1->child=tree2;
			mk_dbl_cir_lst(tree2);
		} else {
			add_node(tree1->child, tree2);
		}
		tree1->degree++;
		return tree1;
	} else {
		detach_node(tree1, 0);
		tree1->parent=tree2;
		if(tree2->child==NULL) {
			tree2->child=tree1;
			mk_dbl_cir_lst(tree1);
		} else {
			add_node(tree2->child, tree1);
		}
		tree2->degree++;
		return tree2;
	}
}

void detach_children(struct node *curr_max)
{
	struct node *curr=curr_max->child;
	for(int i=0; i<curr_max->degree; i++) {
		struct node *tmp=detach_node(curr, 1);
		add_node(curr_max, curr);
		curr=tmp;
	}
	curr_max->degree=0;
	curr_max->child=NULL;
}
