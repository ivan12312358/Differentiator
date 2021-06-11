#include "../Libraries/files.h"
#include "../Libraries/node.h"
#include "../Libraries/calc.h"
#include "../Libraries/differentiator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>

Node* Node::Differentiator ()
{
	if(isdigit(data[0]))
	{
		return new Node ("0");
	}
	else if(isalpha(data[0]) && !Math_Func(data, 0))
	{
		return new Node ("1");
	}
	else if(!strcmp(data, "+"))
	{
		return dL + dR;
	}
	else if(!strcmp(data, "-"))
	{
		return dL - dR;
	}
	else if(!strcmp(data, "*"))
	{
		return *(dL * cR) + *(cL * dR);
	}
	else if(!strcmp(data, "/"))
	{
		return *(*(dL * cR) - *(cL * dR)) / *(cR * cR);		
	}
	else if(!strcmp(data, "^"))
	{
		int var_l = 1, var_r = 1;
		left->isconst(&var_l), right->isconst(&var_r);

		if(var_l && var_r) 													//левое и правое поддерево константные
		{
			return new Node ("0");
		}
		else if(!var_l && !var_r) 											//левое и правое поддерево неконстантные
		{
			Node* node  = new Node ("LN");
			node->left  = &cL;
			node->right = new Node ("");

			return cH * *(*(dR * *node) + *(*(cR * dL) / cL));		//	(f(x)^g(x))'  = f(x)^g(x)*(g'(x)*ln(f(x)) + g(x)*f'(x)/f(x))
		}
		else if(var_l) 														//левое поддерево константное
		{
			Node* node  = new Node ("LN");
			node->left  = &cL;
			node->right = new Node ("");

			return *(cH * *node) * dR;										// (const^f(x))' = const^f(x)*LN(const)*f'(x);
		}
		else if(var_r) 														// правое поддерево константное
		{
			Node* node  = new Node ("1");											
			return *(*(cL ^ *(cR - *node)) * cR) * dL;						// (f(x)^const)'  = f(x)^(const - 1)*const*f'(x) 
		}
	}
	else
	{
 		for (int i = 0; i < 3; i++)
		{
			if (!strcmp(mass[i], data))
				return funcs[i] (left);
		}	
	}

	return nullptr;
}

//-------------------------------------------------------------------------------

void Node::isconst(int* variables)
{
	if(isalpha(data[0]) && !(long)Math_Func(data, 0))
		*variables = 0;

	if(*variables && left)   left->isconst(variables);
	if(*variables && right) right->isconst(variables);
}

//-------------------------------------------------------------------------------

Node* Node::Copy()
{
	Node* c_node = new Node (data);
	
	if(left)  c_node->left  =  left->Copy();
	if(right) c_node->right = right->Copy();

	return c_node;
}

//-------------------------------------------------------------------------------

Node* operator * (Node& L, Node& R)
{
 	Node* node  = new Node ("*");
	node->left  = &L;
	node->right = &R;

	return node;
}

//-------------------------------------------------------------------------------

Node* operator + (Node& L, Node& R)
{
	Node* node  = new Node ("+");
	node->left  = &L;
	node->right = &R;

	return node;
}

//-------------------------------------------------------------------------------

Node* operator - (Node& L, Node& R)
{
 	Node* node  = new Node ("-");
	node->left  = &L;
	node->right = &R;

	return node;
}

//-------------------------------------------------------------------------------

Node* operator / (Node& L, Node& R)
{
 	Node* node  = new Node ("/");
	node->left  = &L;
	node->right = &R;

	return node;
}

//-------------------------------------------------------------------------------

Node* operator ^ (Node& L, Node& R)
{
 	Node* node  = new Node ("^");
	node->left  = &L;
	node->right = &R;

	return node;
}

//-------------------------------------------------------------------------------

void Simplifying_Expr (Node** head)
{
	int const_red = 1, identity_elem = 1;

	while(const_red || identity_elem)
	{
		const_red = 0; identity_elem = 0;
		(*head)->Const_Reduction (&const_red);
		(*head) = (*head)->Identity_Elem   (&identity_elem);
	}
}

//-------------------------------------------------------------------------------

int Node::isoperator()
{
	if(isdigit(data[0]) || (long)Math_Func(data, 0))
		return 0;

	if((strlen(data) == 1) && !isalpha(data[0])) 		//operator === + - * / ^
		return data[0];

	return 0;
}

//-------------------------------------------------------------------------------

Node* Node::Delete_Elem(const char* neutral_elem)
{
	Node* tmp = nullptr;

	if(left && !strcmp(left->data, neutral_elem))
	{
		tmp   = right;
		right = nullptr;
	}
	else if(right && !strcmp(right->data, neutral_elem))
	{
		tmp  = left;
		left = nullptr;
	}

	return tmp;
}

//-------------------------------------------------------------------------------

Node* Node::Identity_Elem (int* change)
{
	Node* tmp = nullptr;

	switch(data[0])
	{
		case '+':
		{
			tmp = Delete_Elem("0");
			break;
		}
		case '-':
		{
			if(right && !strcmp(right->data, "0"))
			{
				tmp   = left;
				left  = nullptr;
			}	
			break;
		}
		case '*':
		{
			tmp = Delete_Elem("1");

			if(!tmp)
			{
				bool l =  left && !strcmp(left->data, "0");
				bool r = right && !strcmp(right->data, "0");
			
				if(l || r)	tmp = new Node("0");
			}

			break;
		}
		case '/':
		{
			if(right && !strcmp(right->data, "1"))
			{
				tmp   = left;
				left  = nullptr;	
			}
			else if(left && !strcmp(left->data, "0"))
				tmp = new Node("0");

			break;
		}
		case '^':
		{
			if(right && !strcmp(right->data, "1"))
			{
				tmp   = left;
				left  = nullptr;	
			}
			else if(left && !strcmp(left->data, "0"))
				tmp = new Node("0");
			else if(right && !strcmp(right->data, "0"))
				tmp = new Node("1");
			else if(left && !strcmp(left->data, "1"))
				tmp = new Node("0");
		}
	}

	if(tmp)
	{
		*change = 1;
		delete this;
		return tmp;
	}

	if (left)  left  =  left->Identity_Elem (change);
	if (right) right = right->Identity_Elem (change);

	return this;
}

//-------------------------------------------------------------------------------

void Node::Const_Reduction (int* change)
{
	if(isoperator())
	{
		if(isdigit(left->data[0]) && (isdigit(right->data[0]) || right->data[0] == '\0'))
		{
			double result = 0;
			double l_value = atof(left->data);
			double r_value = atof(right->data);

			switch (isoperator())
			{
				case('+'):
					result = l_value + r_value;
					break;
				
				case('-'):
					result = l_value - r_value;
					break;
				case('*'):
					result = l_value * r_value;
					break;

				case('/'):
					result = l_value / r_value;
					break;

				case('^'):
					result = pow (l_value, r_value);
					break;
			}

			delete  left;	left = nullptr;
			delete right;  right = nullptr;
			free (data);

			data = (char*) calloc (DIGIT, sizeof(char));

			sprintf(data, "%lg", result);

			*change = 1;
		}
	}

	if (left)   left->Const_Reduction (change);
	if (right) right->Const_Reduction (change);
}

//-------------------------------------------------------------------------------

void Node::Tex(char* f_func)
{
	char out_file[40] = "";

	Tex_Open (f_func, out_file);

	FILE* f_tex = fopen(out_file, "a+");
	assert(f_tex);

	char* symbols = nullptr;
	int size = read(&symbols, f_func);

	brackets(symbols, size);

	char l_data[256] = "";

	str_tolower(l_data, symbols, size);

 	fprintf (f_tex, " (%s) = ", l_data);

	Tex_Create (f_tex);

 	fprintf (f_tex, "$$\n\\end{document}");

	fclose(f_tex);

	char compile[100] = ""; 
	sprintf (compile, "pdflatex -output-directory ./Out_File %s", out_file);
	system  (compile);

	free(symbols);
}

//-------------------------------------------------------------------------------

void Node::Tex_Open (char* func, char* out_file)
{
	if(data == nullptr)
	{
		printf ("Tree is empty\n");
		return;
	}

	printf ("Making Tex...\n");
	printf ("Where to save your Tex file? Type name of file\n");

	int SIZE  = 32;
	char buf[SIZE] = "";

	fgets(buf, SIZE, stdin);
	buf[strlen (buf) - 1] = '\0';

	sprintf(out_file, "./Out_File/%s.tex", buf);

	char copy[128] = "";
	sprintf(copy, "cp -f ./Tex/header.txt %s", out_file);
	system (copy);
}

//-------------------------------------------------------------------------------

void Node::Tex_Create(FILE* f_tex)
{
	if(Math_Func(data, 0))
	{
		char l_data[256] = "";
		str_tolower(l_data, data, strlen(data));
		fprintf(f_tex, "%s(", l_data);
	}
	else if(data[0] == '/')
		fprintf(f_tex, " \\frac{");


	if(left)   left->Tex_Create(f_tex);

	if(!Math_Func(data, 0))
	{
		if(data[0] == '*')
			fprintf(f_tex, " \\cdot ");
		else if(data[0] == '/')
			fprintf(f_tex, "}{");
		else
			fprintf(f_tex, "%s", data);
	}

	if(right && right->isoperator())
	{
		switch(data[0])
		{
			case '*':
			case '/':
				if(right->data[0] == '+' || right->data[0] == '-')
					fprintf(f_tex, "(");
				break;
			case '^':
				fprintf(f_tex, "{");
				break;
		}		
	}

	if(right) right->Tex_Create(f_tex);

	if(Math_Func(data, 0))
		fprintf(f_tex, ")");
	else if(data[0] == '/')
		fprintf(f_tex, " }");

	if(right && right->isoperator())
	{
		switch(data[0])
		{
			case '*':
			case '/':
				if(right->data[0] == '+' || right->data[0] == '-')
					fprintf(f_tex, ")");
				break;
			case '^':
				fprintf(f_tex, "}");
				break;
		}		
	}
}

//-------------------------------------------------------------------------------

void brackets(char* symbols, int size)
{
	for(int i = 0; i < size; i++)
	{
		if(symbols[i] == '^')
		{
			int j = i + 1;

			if(symbols[j] == '(')
			{	
				symbols[j]  = '{';

				while(j < size && symbols[j] != ')')
					j++;
				
				symbols[j] =  '}';
			}
		}
	}
}

//-------------------------------------------------------------------------------

void str_tolower(char* l_data, char* data, int size)
{
	for(int i = 0; i < size; i++)
		l_data[i] = tolower(data[i]);
}

//-------------------------------------------------------------------------------

Node* ln (Node* F_node)
{
	return dF / cF;
}

Node* exp (Node* F_node)
{
	return cF * dF;
}

Node* sin (Node* F_node)
{
 	Node* node  = new Node ("COS");
	node->left  = &cF;
	node->right = new Node ("");

	return *node * dF;
}

Node* cos (Node* F_node)
{
 	Node* node  = new Node ("SIN");
	node->left  = &cF;
	node->right = new Node ("");

	Node* sign = new Node ("0");

	return *(*sign - *node) * dF;
}

/*
Node* lg   	 (Node* F_node)
Node* log    (Node* F_node)
Node* sqrt   (Node* F_node)
Node* tan    (Node* F_node)
Node* ctan   (Node* F_node)
Node* asin   (Node* F_node)
Node* acos   (Node* F_node)
Node* atan   (Node* F_node)
Node* actan  (Node* F_node)
Node* sinh   (Node* F_node)
Node* cosh   (Node* F_node)
Node* tanh   (Node* F_node)
Node* ctanh  (Node* F_node)
Node* asinh  (Node* F_node)
Node* acosh  (Node* F_node)
Node* atanh  (Node* F_node)
Node* actanh (Node* F_node)
*/
