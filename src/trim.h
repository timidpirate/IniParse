#ifndef TRIM
#define TRIM

// Trims the string a and returns the len of trimmed string.
extern size_t trim(char * a);

// Trims the string a of length l and returns the len of trimmed string.
extern size_t triml(char * a, size_t l);

// Frees trim internal buffer.
extern void freetrim(void);

#endif
