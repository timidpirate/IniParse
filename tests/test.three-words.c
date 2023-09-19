#include <stdio.h>
#include <string.h>

char a[1024];

int test()
{
	FILE * f = fopen("./option.three-words", "r");
	fgets(a, 1024, f);
	fclose(f);

	if(strcmp(a,"value with spaces") != 0) return 1;
	
	return 0;
}

void fail_message()
{
	printf("Option value expected is 'value with spaces', but actual is '%s'.", a);
}
