#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "../../Common/Trim/src/trim.h"

int main( int argc, char ** argv )
{
	if(argc == 1)
	{
		printf("Error! No arguments.\n\nUsage:\n\tiniparse <ini-file>\n");
		return -1;
	}
	
	FILE * f = NULL;
	char * buf, * option, * value;

	f = fopen(argv[1], "r");

	if(f == NULL)
	{
		printf("Error! Cannot open file \"%s\".\n", argv[1]);
		return -2;
	}
	
	// Get the size of input ini-file.
	fseek(f, 0L, SEEK_END);
	size_t size = ftell(f);
	if(size < 0)
	{
		printf("Error! Input file size is %ld.\n", size);
		fclose(f);
		return -3;
	}
	rewind(f);
	
	// Initially allocate of buffers (size is the size of input file).
	buf = malloc(size);
	if(buf == NULL) { printf("Error! Cannot allocate buf size=%zu.\n", size); fclose(f); return -1; }
	option = malloc(size);
	if(option == NULL) { printf("Error! Cannot allocate option size=%zu.\n", size); free(buf); fclose(f); return -1; }
	value  = malloc(size);
	if(value == NULL) { printf("Error! Cannot allocate value size=%zu.\n", size); free(buf); free(option); fclose(f); return -1; }
	
	// Read ini-file line by line.
	while(fgets(buf,size,f) != NULL)
	{
		char * es = strstr(buf, "=");				// Look for '=' symbol in the line.
		
		if(es != NULL)								// If '=' is present, then it is option line.
		{
			*es = 0;								//	Cut the string into two strings at place of '='.
			
			strcpy(option, buf);					//	 Left piece is the option name.
			triml(option, es-buf);

			char * multi = strstr(es + 1, "[{");	// Check if multiline value.
			if(multi == NULL)                       // If single line value...
			{	
				strcpy(value, es + 1);				// then right piece of string is value.
				trim(value);
			}
			else                                    // if multiline value...
			{
				size_t l, par = 0;
				char * v = value;
				strcpy(v, multi + 2);				// Right piece from [{ is the first line of value.
				trim(v);
				l = strlen(v);
				v = v + l;
				
				// Read the multiline value line by line until "}]" is encountered.
				while((fgets(buf,size,f) != NULL) && ((multi = strstr(buf, "}]")) == NULL))
				{
					trim(buf);
					
					if(strlen(buf) == 0)	// Empty line means next paragraph ahead.
					{
						par = 1;			// Set new paragraph mark.
						continue;
					}
					
					if(par == 1)			// If it were new paragraph...
					{
						*v = '\n';			// then add empty line to value,
						v++;
						*v = '\n';
						v++;
						par = 0;    		// and drop paragraph mark.
					}
					else            		// If there were no new paragraph...
					{                       // say, just newline,
						*v = ' ';			// then add one whitespace.
						v++;
					}
					
					strcpy(v,buf);
					l = strlen(buf);		// Copy the line into option value.
					v = v + l;
				}

				*multi = 0;					// Cut the string at place of "}]".
				trim(buf);
				*v = ' ';
				v++;
				strcpy(v,buf);
			}
			
			if(strlen(value))
			{
				// Write option value to option file. ----------------------
				FILE * of = fopen(option, "w");

				if(of == NULL)
				{
					printf("Cannot create option file '%s'.\n", option);
					return -1;
				}
			
				fprintf(of, "%s", value);
			
				fclose(of);	// ---------------------------------------------
			}
		}
	}
	
	free(value);		
	free(option);		
	free(buf);
	fclose(f);
}
