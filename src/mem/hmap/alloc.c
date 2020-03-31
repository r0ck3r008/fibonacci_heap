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
		((struct hmap_node *)ret)->key=hmap_alloc("char", 64);
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
		explicit_bzero(buf, sizeof(char)*size);
		free((char *)buf);
	} else if(!strcmp(type, "struct hmap_node")) {
		hmap_dealloc("char", ((struct hmap_node *)buf)->key, 64);
		explicit_bzero(buf, sizeof(struct hmap_node)*size);
		free((struct hmap_node *)buf);
	} else if(!strcmp(type, "struct hmap")) {
		explicit_bzero(buf, sizeof(struct hmap)*size);
		free((struct hmap *)buf);
	}

	buf=NULL;
}
