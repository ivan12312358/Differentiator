#include "./Libraries/calc.h"
#include "./Libraries/node.h"
#include "./Libraries/files.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char* argv[])
{
	if(argc < 2)	
	{
		printf("Type name of file in startup parametrs with expression.\n");
		return 1;
	}

	Calc calc (argv[1]);

	Node* head = calc.GetG ();

	Node* diff = head->Differentiator();

	Simplifying_Expr(&diff);

	diff->Tex(argv[1]);

	delete diff;
	delete head;

	return 0;
}
