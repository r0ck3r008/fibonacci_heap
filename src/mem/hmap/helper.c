#include"helper.h"

int hash_it(char *key)
{
	int sum=0;
	while(*key!='\0') {
		sum+=*(int *)key;
		key+=sizeof(char);
	}

	return sum%MAX_SIZE;
}
