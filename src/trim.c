#include <stdio.h>
#include <malloc.h>
#include <string.h>

static char * t = NULL;				// trim buffer.
static size_t tlen = 0;				// trim buffer size.

// Trims the string a of length l and returns the len of trimmed string.
size_t triml(char * a, size_t l)
{
	if(l == 0) return 0;
	
	if(l > tlen)					// If string is longer then the current buffer.
	{
		if(t == NULL)
			t = malloc(l*4);		// Reserve extra size in order to call
		else
			t = realloc(t, l*4);	// memory allocation less often.
			
		tlen = l;
	}
	
	memcpy(t, a, l);				// Copy string to internal buffer.
	
	// Count spaces in front of non-spaced string.
	size_t b = 0;
	while(((t[b] == '\r') || (t[b] == '\n') || (t[b] == '\t') || (t[b] == ' ')) && b < l)	b++;
	
	// Count spaces after non-spaced string.
	size_t e = 1;
	while(((t[l-e] == '\r') || (t[l-e] == '\n') || (t[l-e] == '\t') || (t[l-e] == ' ')) && e < l-b)	e++;
	
	l = l - b - e + 1;
	
	if(l) memcpy(a, t + b, l);	//	Move trimmed string to the beginning of argumenr string.

	a[l] = 0;					// Terminate it with \0.

	return l;
}

// Trims the string a and returns the len of trimmed string.
size_t trim(char * a)
{
	return triml(a,strlen(a));
}

// Frees internal buffer.
void freetrim(void)
{
	if(t) free(t);
}
