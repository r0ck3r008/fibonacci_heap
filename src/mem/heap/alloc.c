#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include"alloc.h"

void *heap_alloc(char *type, int size)
{
	void *ret=NULL;

	if(!strcmp(type, "char")) {
		ret=malloc(sizeof(char)*size);
		explicit_bzero(ret, sizeof(char)*size);
	} else if(!strcmp(type, "struct heap_node")) {
		ret=malloc(sizeof(struct heap_node)*size);
		explicit_bzero(ret, sizeof(struct heap_node)*size);
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

void heap_dealloc(char *type, void *buf, int size)
{
	if(!strcmp(type, "char")) {
		free((char *)buf);
	} else if(!strcmp(type, "struct heap")) {
		free((struct heap *)buf);
	} else if(!strcmp(type, "struct heap_node")) {
		free((struct heap_node *)buf);
	}

}
