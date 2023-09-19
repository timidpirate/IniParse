#include <stdio.h>
#include <string.h>

char a[1024];

char expected[] = "Multiline value with intermediate string.\n\nAnd another paragraph and finishing.";

int test()
{
	FILE * f = fopen("./option.few-lines-with-empty-in-between", "r");
	fread(a, 1, 1024, f);
	fclose(f);

	if(strcmp(a,expected) != 0) return 1;
	
	return 0;
}

void fail_message()
{
	printf("Option value expected is '%s', but actual is '%s'.", expected, a);
}
