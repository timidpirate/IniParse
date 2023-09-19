#include <stdio.h>
#include <unistd.h>

int test()
{
	if(access("option.empty", F_OK) == 0)	return 1;	// File should not be generated for empty option.

	return 0;
}

void fail_message()
{
	printf("File should not be generated for empty option, but it exists.");
}
