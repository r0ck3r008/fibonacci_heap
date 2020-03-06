#include<stdio.h>

#include"helper.h"

void traverse(struct heap *heap_in, void(*fn)(struct node *))
{
	//assuming the heap_in->trees is the starting pointer
	struct node *curr_parent=heap_in->trees;
	struct node *curr=curr_parent;
	struct node *last_child=NULL;

	while(1) {
		if(curr->child!=NULL && curr->child!=last_child) {
			//traverse down a level
			curr_parent=curr;
			curr=curr->child;
			continue;
		}

		if(curr->nxt!=NULL) {
			//keep moving along
				curr=curr->nxt;
		} else {
			//end of current level, execute given function
			//on this level
			fn(curr);
			//move up a level
			last_child=curr;
			curr=curr_parent;
			if(curr->parent!=NULL)
				curr_parent=curr->parent;
			else
				//root level reached
				break;
		}
	}
}

void meld(struct node *tree1, struct node *tree2)
{
	if(tree1->val < tree2->val) {
		detach_node(tree1);
		tree1->parent=tree2;
		if(tree2->child==NULL)
			tree2->child=tree1;
		else
			add_node(tree2->child, tree1);
		tree2->children++;
	} else {
		detach_node(tree2);
		tree2->parent=tree1;
		if(tree1->child==NULL)
			tree1->child=tree2;
		else
			add_node(tree1->child, tree2);
		tree1->children++;
	}
}

void detach_children(struct heap *heap_in, struct node *parent)
{
	struct node *curr=move_to_start(parent->child);
	for(int i=0; i<parent->children; i++) {
		struct node *tmp=curr->nxt;
		detach_node(curr);
		add_node(heap_in->trees, curr);
		curr=tmp;
	}
	parent->child=NULL;
	parent->children=0;
}
