#include "../Libraries/node.h"
#include "../Libraries/calc.h"
#include "../Libraries/differentiator.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>



Node* Node::Differentiator ()
{
	if(isdigit(data[0]))
	{
		return new Node ("0");
	}
	else if(isalpha(data[0]) && !Math_Func(data))
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

//		printf("%d %d\n", var_r, var_l);

		if(var_l && var_r) 													//левое и правое поддерево константные
		{
			return new Node ("0");
		}
		else if(!var_l && !var_r) 											//левое и правое поддерево неконстантные
		{
			Node* node  = new Node ("LN");
			node->left  = &cR;
			node->right = new Node ("");

			return cH * *(*(dL * *(ln(right))) + *(*(cL * dR) / cR));		//	(f(x)^g(x))'  = f(x)^g(x)*(f'(x)*ln(g(x)) + f(x)*g'(x)/g(x))
		}
		else if(var_l) 														//левое поддерево константное
		{
			Node* node  = new Node ("LN");
			node->left  = &cL;
			node->right = new Node ("");

//			printf("%s\n", node->left->data);

			return *(cH * *node) * dR;										//	(const^f(x))' = const^f(x)*LN(const)*f'(x);
		}
		else if(var_r) 														//правое поддерево константное
		{
			printf("loh");
			Node* node  = new Node ("1");											
			return *(*(cL ^ *(cR - *node)) * cR) * dL;						// (f(x)^const)'  = f(x)^(const - 1)*const*f'(x) 
		}
	}
	else
	{
		for (int i = 0; i < 21; i++)
		{
			if (strcmp (mass[i], data) == 0)
				return funcs[i](left);
		}
		
	}

	return nullptr;
}
//-------------------------------------------------------------------------------

void Node::isconst(int* variables)
{
	if(isalpha(data[0]) && !Math_Func(data))
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

//Node* exp  (Node* F_node);      
Node* ln (Node* F_node)
{
	return dF / cF;
}
/* Node* lg (Node* node);
Node* log  (Node* node);     
Node* sqrt (Node* node);    
Node* sin (Node* node);
Node* cos  (Node* node);      
Node* tan (Node* node);     
Node* ctan (Node* node);
Node* asin  (Node* node);     
Node* acos (Node* node);     
Node* atan (Node* node);
Node* actan  (Node* node);    
Node* sinh (Node* node);     
Node* cosh (Node* node);
Node* tanh  (Node* node);     
Node* ctanh (Node* node);    
Node* asinh (Node* node);
Node* acosh  (Node* node);    
Node* atanh (Node* node);    
Node* actanh (Node* node); */