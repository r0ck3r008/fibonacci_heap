#include"helper.h"

void traverse(struct heap *heap_in, void (*fn)(struct node *))
{
	struct node *curr_parent=heap_in->trees;
	struct node *curr=curr_parent;
	while(1) {
		if(curr->nxt!=NULL) {
			if(curr->child!=NULL) {
				//found a deeper level, traverse to it
				struct node *tmp=curr->child;
				curr_parent=curr;
				curr=tmp;
				continue;
			}
			curr=curr->nxt;
		} else {
			//end of this level, no deeper level found
			//delete this level now
			fn(curr);
			//move a level up
			curr=curr_parent;
		}
		if(curr==heap_in->trees)
			break;
	}
}

void meld(struct node *tree1, struct node *tree2)
{
	if(tree1->val>tree2->val) {
		tree2->parent=tree1;
		if(tree1->child==NULL)
			tree1->child=tree2;
		else
			add_node(tree1->child, tree2);
	} else {
		tree1->parent=tree2;
		if(tree2->child==NULL)
			tree2->child=tree1;
		else
			add_node(tree2->child, tree1);
	}
}
