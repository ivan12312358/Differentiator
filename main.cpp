#include "./Libraries/calc.h"
#include "./Libraries/node.h"
#include "./Libraries/files.h"


int main(int argc, char* argv[])
{
	if(argc < 2)	
	{
		printf("Type name of file in startup parametrs with expression.\n");
		return 1;
	}

	Calc calc(argv[1]);

	Node* head = calc.GetG ();

	head->Graph();

	Node* diff = head->Differentiator();

	diff->Graph();

	delete diff;
	delete head;

	return 0;
}
