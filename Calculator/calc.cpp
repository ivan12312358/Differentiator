#include "../Libraries/calc.h"
#include "../Libraries/files.h"
#include "../Libraries/node.h"
#include <math.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>

#define COMPARE(func, symb)							\
{													\
	if(!strncmp(symbols + counter, #func, symb))	\
		return #func;								\
}

Calc::Calc (char* filename)
{
	char* sym = nullptr;
	int   sym_cnt = read (&sym, filename);

	char** str = (char**)calloc(sym_cnt, sizeof(char*));
	int str_cnt = split(str, sym);

	symbols = (char*)calloc(sym_cnt, sizeof(char*));

	sprintf(symbols, "%s", str[str_cnt - 1]);

	free(sym);
	free(str);
}

Calc::~Calc ()
{
	error   = 0;
	counter = 0;
	free(symbols);
};

Node* Calc::GetG ()
{
//	printf("GetG: %s\n", symbols + counter);

	Node* result = GetE ();

	if(symbols[counter] != '\0')
		error = 1;

	return result;	
}

Node* Calc::GetE ()
{
//	printf("GetE: %s\n", symbols + counter);

	Node* result = GetT ();

	while(symbols[counter] == '+' || symbols[counter] == '-')
	{
		Node* operator_ = new Node (symbols + counter, 1);
		counter++;

		operator_->left  = result;
		operator_->right = GetT ();
		result = operator_;
	}

	return result;
}

Node* Calc::GetT ()
{
//	printf("GetT: %s\n", symbols + counter);

	Node* result = GetQ ();

	while(symbols[counter] == '*' || symbols[counter] == '/')
	{
 		Node* operator_ = new Node (symbols + counter, 1);
		counter++;

		operator_->left  = result;
		operator_->right = GetQ ();
		result = operator_;
	}

	return result;
}

Node* Calc::GetQ ()
{
//	printf("GetQ: %s\n", symbols + counter);

	Node* result = GetF ();

	while(symbols[counter] == '^')
	{
 		Node* operator_ = new Node (symbols + counter, 1);
		counter++;

		operator_->left  = result;
		operator_->right = GetQ ();
		result = operator_;
 	}

	return result;
}

Node* Calc::GetF ()
{
//	printf("GetF: %s\n", symbols + counter);

	Node* result = GetP ();

	const char* function = nullptr;

	while((function = Math_Func ()))
	{
		counter += strlen(function);
 		Node* operator_ = new Node ((char*)function, strlen(function));
		operator_->left  = GetP ();
		operator_->right  = result;
		result = operator_;
	}

	return result;
}

Node* Calc::GetP ()
{
//	printf("GetP: %s\n", symbols + counter);

	Node* result = nullptr;

	if(symbols[counter] == '(')
	{
		counter++;
		result = GetE ();

		if(symbols[counter++] != ')')
			error = 1;
	}
	else if(symbols[counter] == '-')
	{
		Node* operator_ = new Node (symbols + counter, 1);
		
		result = new Node ((char*)"0", 1);

		counter++;

		if(symbols[counter] == '(')
		{
			operator_->left  = GetE ();

			if(symbols[counter++] != ')')
				error = 1;
		}
		else operator_->left  = GetF ();

		operator_->right = result;
		result = operator_;
	}
	else
		result = GetN ();

	return result;
}

Node* Calc::GetN ()
{
//	printf("GetN: %s\n", symbols + counter);

	char digit[128];
	int  size = 0;

	while(Is_Num_Alpha())
		digit[size++] = symbols[counter++];

	digit[size++] = '\0';

	return new Node (digit);
}

int Calc::Is_Num_Alpha()
{
	if(counter > 128 || Math_Func()) return 0;

	if(isdigit(symbols[counter]))
		return 1;

	if(isalpha(symbols[counter]))
		return 1;

	if(symbols[counter] == '.')
		return 1;

	return 0;
}

const char* Calc::Math_Func ()
{
	COMPARE(LN, 	2);		COMPARE(LG, 	2);		COMPARE(LOG, 	3);
	COMPARE(EXP, 	3);		COMPARE(SIN, 	3);		COMPARE(COS, 	3);
	COMPARE(TAN,    3); 	COMPARE(SQRT,   4); 	COMPARE(CTAN,   4);
	COMPARE(ASIN,   4);		COMPARE(ACOS,   4);		COMPARE(ATAN,   4);
	COMPARE(SINH,   4); 	COMPARE(COSH,   4);		COMPARE(TANH,   4);
	COMPARE(CTANH,  5);		COMPARE(ACTAN,  5); 	COMPARE(ASINH,  5);
	COMPARE(ACOSH,  5); 	COMPARE(ATANH,  5); 	COMPARE(ACTANH, 6);

	return nullptr;
}

double Call_Func (int func, double tmp_res)
{
	switch(func)
	{
		case(LN):		return log(tmp_res);		case(EXP):		return exp(tmp_res);
		case(SIN):		return sin(tmp_res);		case(COS):		return cos(tmp_res);
		case(TAN):		return tan(tmp_res);		case(LOG):		return log2(tmp_res);
		case(ASIN):		return asin(tmp_res);		case(ACOS):		return acos(tmp_res);
		case(ATAN):		return atan(tmp_res);		case(SINH):		return sinh(tmp_res);
		case(COSH):		return cosh(tmp_res);		case(TANH):		return tanh(tmp_res);
		case(SQRT):		return sqrt(tmp_res);		case(LG):		return log10(tmp_res);
		case(ACOSH):	return acosh(tmp_res);		case(ATANH):	return atanh(tmp_res);
		case(ASINH):	return asinh(tmp_res);		case(CTAN):		return 1/tan(tmp_res);
		case(CTANH):	return 1/tanh(tmp_res);		case(ACTAN):	return 1/atan(tmp_res);	
		case(ACTANH):	return 1/atanh(tmp_res);	default:		return -3.14271;
	}
}
