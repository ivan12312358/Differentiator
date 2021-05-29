#include "../Libraries/files.h"

const int SIZE = 128;
char buf[SIZE] = "";

//-------------------------------------------------------------------------------

int split (char** str, char* symbols)
{
	char* tmp_sym = symbols;

	symbols = strtok (symbols, "=\n");

	int size = 0;

	while(symbols != NULL)
	{
		str[size++] = symbols;
		symbols     = strtok (nullptr, "=\n");
	}

	symbols = tmp_sym;

	return size;
}

//-------------------------------------------------------------------------------

void print (FILE* f_out, const char* buffer)
{
	fprintf (f_out, "%s\n", buffer);
	fflush  (f_out);
}

//-------------------------------------------------------------------------------

void scan (FILE* fin_)
{
	fgets(buf, SIZE, fin_);
	buf[strlen (buf) - 1] = '\0';
}

//-------------------------------------------------------------------------------

int read (char** symbols, const char* filename)
{
	FILE* base = fopen (filename, "r");

	if(base == nullptr)
	{
		printf ("Couldn't find file\n");
		return 0;
	}

	fseek (base, 0, SEEK_END);
	int size = ftell (base);
	rewind (base);

	if(size > 0)
	{
		*symbols = (char*) calloc (size + 1, sizeof (char));
		fread (*symbols, sizeof (char), size, base);
		(*symbols)[size - 1] = '\0';
	}
	fclose (base);

	return size;
}
