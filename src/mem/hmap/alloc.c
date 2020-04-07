#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include"alloc.h"

void *hmap_alloc(char *type, int size)
{
	void *ret=NULL;

	if(!strcmp(type, "char")) {
		ret=malloc(sizeof(char)*size);
		explicit_bzero(ret, sizeof(char)*size);
	} else if(!strcmp(type, "struct hmap_node")) {
		ret=malloc(sizeof(struct hmap_node)*size);
		explicit_bzero(ret, sizeof(struct hmap_node)*size);
	} else if(!strcmp(type, "struct hmap")) {
		ret=malloc(sizeof(struct hmap)*size);
		explicit_bzero(ret, sizeof(struct hmap)*size);
	}

	if(ret==NULL) {
		fprintf(stderr, "Error in allocating %d bytes for %s type!\n",
			size, type);
		_exit(-1);
	}

	return ret;
}

void hmap_dealloc(char *type, void *buf, int size)
{
	if(!strcmp(type, "char")) {
		free((char *)buf);
	} else if(!strcmp(type, "struct hmap_node")) {
		free((struct hmap_node *)buf);
	} else if(!strcmp(type, "struct hmap")) {
		free((struct hmap *)buf);
	}
}
