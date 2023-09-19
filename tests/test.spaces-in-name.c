#include <stdio.h>
#include <string.h>

char a[1024];

int test()
{
	FILE * f = fopen("./option.with spaces in name", "r");
	fgets(a, 1024, f);
	fclose(f);

	if(strcmp(a,"value for option with spaces in name") != 0) return 1;
	
	return 0;
}

void fail_message()
{
	printf("Option value expected is 'value for option with spaces in name', but actual is '%s'.", a);
}
