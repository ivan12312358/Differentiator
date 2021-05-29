#include "../Libraries/calc.h"
#include <stdio.h>

int main (int argc, char* argv[])
{
	Calc calc(argv[1]);

	double result = calc.GetG ();

	if(calc.error)
		printf ("%s\nWrong expression. Don't use spaces!\n", calc.symbols);
	else
		printf ("Result = %lg\n", result);

	return 0;
}
