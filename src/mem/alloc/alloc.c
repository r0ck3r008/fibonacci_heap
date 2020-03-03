#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include"alloc.h"

void *alloc(char *type, int size)
{
	void *ret=NULL;

	if(!strcmp(type, "char")) {
		ret=malloc(size*sizeof(char));
		explicit_bzero(ret, size*sizeof(char));

	} else if(!strcmp(type, "struct node")) {
		ret=malloc(size*sizeof(struct node));
		explicit_bzero(ret, size*sizeof(struct node));

	}

	if(ret==NULL) {
		fprintf(stderr, "[-]Error in allocating %d bytes for %s type\n",
			size, type);
		_exit(-1);
	}

	return ret;
}

void dealloc(void *buf, char *type, int size)
{
	if(!strcmp(type, "char")) {
		explicit_bzero((char *)buf, sizeof(char)*size);
	} else if(!strcmp(type, "struct node")) {
		explicit_bzero((struct node *)buf, sizeof(struct node)*size);
	}

	free(buf);
}
