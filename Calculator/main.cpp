#include "../Libraries/calc.h"
#include "../Libraries/node.h"
#include "../Libraries/files.h"


int main(int argc, char* argv[])
{
	Calc calc(argv[1]);

	Node* head = calc.GetG ();

	head->Graph ();

	head->Differentiator();

	delete head;

	return 0;
}