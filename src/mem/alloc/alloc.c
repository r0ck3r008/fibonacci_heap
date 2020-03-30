#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include"alloc.h"

void *alloc(char *type, int size)
{
	void *ret=NULL;
	if(!strcmp(type, "char")) {
		ret=malloc(sizeof(char)*size);
		explicit_bzero(ret, sizeof(char)*size);
	} else if(!strcmp(type, "struct node")) {
		ret=malloc(sizeof(struct node)*size);
		explicit_bzero(ret, sizeof(struct node)*size);
	} else if(!strcmp(type, "struct heap")) {
		ret=malloc(sizeof(struct heap)*size);
		explicit_bzero(ret, sizeof(struct heap)*size);
	}

	if(ret==NULL) {
		fprintf(stderr, "[-]Error in allocating %d bytes for %s type",
			size, type);
		_exit(-1);
	}
}

void dealloc(char *type, void *buf, int size)
{
	if(!strcmp(type, "char"))
		explicit_bzero((char *)buf, sizeof(char)*size);
	else if(!strcmp(type, "struct node"))
		explicit_bzero((struct node *)buf, sizeof(struct node)*size);
	else if(!strcmp(type, "struct heap"))
		explicit_bzero((struct heap *)buf, sizeof(struct heap)*size);

	free(buf);
	buf=NULL;
}
