#include <stdio.h>
#include <string.h>

char a[1024];

int test()
{
	FILE * f = fopen("./option.with-spaces-before-name-and-value1", "r");
	fgets(a, 1024, f);
	fclose(f);

	if(strcmp(a,"value with extra spaces1") != 0) return 1;
	
	return 0;
}

void fail_message()
{
	printf("Option value expected is 'value with extra spaces1', but actual is '%s'.", a);
}
