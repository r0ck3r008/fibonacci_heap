#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include"alloc.h"

void *alloc(char *type, int size)
{
	void *ret=NULL;
	if(!strcmp(type, "struct node")) {
		ret=malloc(sizeof(struct node)*size);
		explicit_bzero(ret, sizeof(struct node)*size);
	} else if(!strcmp(type, "struct heap")) {
		ret=malloc(sizeof(struct heap)*size);
		explicit_bzero(ret, sizeof(struct heap)*size);
	}

	if(ret==NULL) {
		fprintf(stderr, "[-]Error in allocating %d bytes to %s type!\n",
			size, type);
		_exit(-1);
	}

	return ret;
}

void dealloc(char *type, void *buf, int size)
{
	if(!strcmp(type, "struct node")) {
		explicit_bzero(buf, sizeof(struct node)*size);
		free((struct node *)buf);
	} else if(!strcmp(type, "struct heap")) {
		explicit_bzero(buf, sizeof(struct node)*size);
		free((struct heap *)buf);
	}

	buf=NULL;
}
