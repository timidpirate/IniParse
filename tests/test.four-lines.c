#include <stdio.h>
#include <string.h>

char a[1024];

int test()
{
	FILE * f = fopen("./option.four-lines", "r");
	fgets(a, 1024, f);
	fclose(f);

	if(strcmp(a,"Multiline value with intermediate string and another string and finishing.") != 0) return 1;
	
	return 0;
}

void fail_message()
{
	printf("Option value expected is 'Multiline value with intermediate string and another string and finishing.', but actual is '%s'.", a);
}
