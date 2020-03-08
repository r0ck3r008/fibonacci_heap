#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<errno.h>

#include"mem/mem.h"

int sanitize(int argc, char **argv)
{
	if(argc!=2) {
		fprintf(stderr, "Usage: ./hashtagcounter <file_name>\n");
		return 0;
	}

	struct stat buf;
	if(stat(argv[1], &buf)) {
		fprintf(stderr, "[-]Stat error for %s: %s\n",
			argv[1], strerror(errno));
		return 0;
	}

	return 1;
}

int io(FILE *f)
{
	struct heap *io_heap=NULL;
	struct hmap *io_hmap=init_hmap();
	char *buf;

	while(!feof(f)) {
		buf=alloc("char", 128);
		fgets(buf, 128*sizeof(char), f);
		if(buf[0]=='#') {
			//insert new or fetch existing hash node addr
			struct node *addr=get_addr(io_hmap, buf);
			if(addr==NULL) {
				addr=insert_hmap(io_hmap, buf, 1);
			} else {
				inc_key(io_heap, addr->payload, addr->val,
					((addr->val)+1));
			}
		} else {
			int n_tags=strtol(buf, NULL, 10);
			int flag=0;
			for(int i=0; i<n_tags; i++) {
				struct node *max=remove_max(io_heap);
				if(max==NULL) {
					fprintf(stderr, "[-]Error in removing max, continuing!\n");
					flag=1;
					break;
				}
				printf("Tag: %s\tFrequency: %d\n",
					(char *)max->payload, max->val);
			}
			if(flag)
				continue;
		}
	}

	de_init_hmap(io_hmap);
	if(io_heap!=NULL)
		de_init_heap(io_heap);
/*	if(buf!=NULL)
		dealloc(buf, "char", 128);*/
}

int main(int argc, char **argv)
{
	if(!sanitize(argc, argv)) {
		_exit(-1);
	}

	FILE *f=NULL;
	if((f=fopen(argv[1], "r"))==NULL) {
		fprintf(stderr, "[-]Error in opening file!\n");
		_exit(-1);
	}

	int stat=io(f);

	fclose(f);
	_exit(stat);
}
