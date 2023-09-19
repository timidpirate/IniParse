#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

extern int test();
extern void fail_message();

int main(int argc, char **argv)
{
	// Get terminal width.
	struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	const size_t width = w.ws_col;
	
	// Write test name.
	printf("Run %s ", argv[1]);

	// Write dotted line if there are extra width.
	size_t len = strlen(argv[1]);
	size_t text_len = sizeof("Run") + len + sizeof("pass") + 1;
	if(width > text_len)
		for(size_t i = 0 ; i < width - text_len ; i++) putchar('.');
	
	// Run test.
	if(test())
	{
		printf("\x1b[31m fail\n\t");
		fail_message();
		printf("\x1b[m\n");
		return 1;
	}

	printf("\x1b[32m pass\x1b[m\n");
	return 0;
}
