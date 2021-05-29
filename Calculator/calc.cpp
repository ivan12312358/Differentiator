#include "../Libraries/calc.h"
#include "../Libraries/files.h"
#include <math.h>
#include <errno.h>

#define COMPARE(func, symb)							\
{													\
	if(!strncmp(symbols + counter, #func, symb))	\
	{												\
		counter += symb;							\
		return func;								\
	}												\
}													\

Calc::Calc (char* filename)
{
	read (&symbols, filename, stdout);
}

Calc::~Calc ()
{
	free(symbols);
};

double Calc::G ()
{
	double result = E ();

	if(symbols[counter] != '\0')
		error = 1;

	return result;	
}

double Calc::E ()
{
	double result = T ();

	while(symbols[counter] == '+' || symbols[counter] == '-')
	{
		char operator_ = symbols[counter++];

		double tmp_res = T ();

		if(operator_ == '+')
			result += tmp_res;
		else 
			result -= tmp_res;
	}

	return result;
}

double Calc::T ()
{
	double result = Q ();

	while(symbols[counter] == '*' || symbols[counter] == '/')
	{
		char operator_ = symbols[counter++];

		double tmp_res = Q ();

		if(operator_ == '*')
			result *= tmp_res;
		else 
			result /= tmp_res;
	}

	return result;
}

double Calc::Q ()
{
	double result = F ();

	while(symbols[counter] == '^')
	{
		counter++;

		result = pow(result, F ());

		if(errno == EDOM || errno == ERANGE)
			perror("Error");
	}

	return result;
}

double Calc::F ()
{
	double result = P ();

	int function = 0;

	while((function = Math_Func ()))
	{
		result = Call_Func (function, P ());

		if(errno == EDOM || errno == ERANGE)
			perror("Error");
	}

	return result;
}

double Calc::P ()
{
	double result = 0;

	if(symbols[counter] == '(')
	{
		counter++;
		result = E ();

		if(symbols[counter++] != ')')
			error = 1;
	}
	else if(symbols[counter] == '-')
	{
		counter++;

		if(symbols[counter] == '(')
		{
			counter++;
			result = -E ();

			if(symbols[counter++] != ')')
				error = 1;
		}
		else
			result = -F ();
	}
	else
		result = N ();

	return result;
}

double Calc::N ()
{
	char digit[128];
	int  size = 0;

	while((counter < 128 && symbols[counter] >= '0' && symbols[counter] <= '9') || symbols[counter] == '.')
		digit[size++] = symbols[counter++];

	digit[size++] = '\0';

	return atof(digit);	
}

double Call_Func(int func, double tmp_res)
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

int Calc::Math_Func ()
{
	COMPARE(LN, 	2);		COMPARE(LG, 	2);		COMPARE(LOG, 	3);
	COMPARE(EXP, 	3);		COMPARE(SIN, 	3);		COMPARE(COS, 	3);
	COMPARE(TAN,    3); 	COMPARE(SQRT,   4); 	COMPARE(CTAN,   4);
	COMPARE(ASIN,   4);		COMPARE(ACOS,   4);		COMPARE(ATAN,   4);
	COMPARE(SINH,   4); 	COMPARE(COSH,   4);		COMPARE(TANH,   4);
	COMPARE(CTANH,  5);		COMPARE(ACTAN,  5); 	COMPARE(ASINH,  5);
	COMPARE(ACOSH,  5); 	COMPARE(ATANH,  5); 	COMPARE(ACTANH, 6);

	return 0;
}