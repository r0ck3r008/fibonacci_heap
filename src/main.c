#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<errno.h>

#include"mem/mem.h"

void setup(FILE **in_f, FILE **out_f, int argc, char **argv)
{
	struct stat buf;
	if(stat(argv[1], &buf)!=0) {
		fprintf (stderr, "Unable to find input file!\n");
		_exit(-1);
	}

	if(argc==3) {
		explicit_bzero(&buf, sizeof(struct stat));
		if(stat(argv[2], &buf)!=0) {
			fprintf(stdout, "Overwriting %s as output file!\n",
				argv[3]);
		}
		if((*out_f=fopen(argv[3], "w"))==NULL) {
			fprintf(stderr, "Error in opening %s for writing: %s\n",
				argv[3], strerror(errno));
			_exit(-1);
		}
	} else {
		*out_f=stdout;
	}

	if((*in_f=fopen(argv[1], "r"))==NULL) {
		fprintf(stderr, "Error in opening %s: %s\n",
			argv[2], strerror(errno));
		_exit(-1);
	}
}

void process_file(FILE *in_f, FILE *out_f)
{
	char *line=NULL;
	size_t size=0;
	struct hmap *test_hmap=NULL;
	while(1) {
		int stat=getline(&line, &size, in_f);
		if(stat==-1)
			break;
		if(line[0]=='#') {
			char *line1=line+sizeof(char);
			char *hash=strtok(line1, " ");
			int value=strtol(strtok(NULL, " "), NULL, 10);
			if(test_hmap==NULL)
				test_hmap=hmap_init(hash, value);
			else
				hmap_update(test_hmap, hash, value);
		}
		else if(!strcmp(line, "stop") || !strcmp(line, "STOP")) {
			break;
		} else {
			int n=strtol(line, NULL, 10);
			for(int i=0; i<n; i++) {
				struct hmap_node *max=hmap_remove_max(
								test_hmap);
				fprintf(out_f, "%s", max->key);
				if(i!=n-1)
					fprintf(out_f, ",");
				else
					fprintf(out_f, "\n");
//				hmap_dealloc("struct hmap_node", max, 1);
			}
		}

		free(line);
		line=NULL;
	}

	free(line);
//	hmap_de_init(test_hmap);
}

int main(int argc, char **argv)
{
	if(argc<2) {
		fprintf(stderr, "Usage: ./hashtagcounter <ip_file_name> [op_file_name]\n");
		_exit(-1);
	}

	FILE *in_f, *out_f;
	setup(&in_f, &out_f, argc, argv);

	process_file(in_f, out_f);

	fclose(in_f);
	fclose(out_f);
}
