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
	} else if(!strcmp(type, "struct node *")) {
		ret=malloc(size*sizeof(struct node *));
		explicit_bzero(ret, size*sizeof(struct node *));
	} else if(!strcmp(type, "struct heap")) {
		ret=malloc(size*sizeof(struct heap));
		explicit_bzero(ret, sizeof(struct heap)*size);
	} else if(!strcmp(type, "struct data")) {
		ret=malloc(size*sizeof(struct data));
		explicit_bzero(ret, size*sizeof(struct data));
	} else if(!strcmp(type, "struct hmap")) {
		ret=malloc(size*sizeof(struct hmap));
		explicit_bzero(ret, sizeof(struct hmap)*size);
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
	} else if(!strcmp(type, "struct node *")) {
		explicit_bzero((struct node **)buf, size*sizeof(struct node *));
	} else if(!strcmp(type, "struct heap")) {
		explicit_bzero((struct heap *)buf, sizeof(struct heap)*size);
	} else if(!strcmp(type, "struct data")) {
		explicit_bzero((struct data *)buf, size*sizeof(struct data));
	} else if(!strcmp(type, "struct hmap")) {
		explicit_bzero((struct hmap *)buf, sizeof(struct hmap)*size);
	}

	free(buf);
	buf=NULL;
}
