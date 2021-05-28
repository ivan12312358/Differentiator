#include "../Libraries/calc.h"
#include "../Libraries/files.h"

Calc::Calc (char* filename)
{
	read (&symbols, filename, stdout);
};

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
	double result = P ();

	while(symbols[counter] == '*' || symbols[counter] == '/')
	{
		char operator_ = symbols[counter++];

		double tmp_res = P ();

		if(operator_ == '*')
			result *= tmp_res;
		else 
			result /= tmp_res;
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
	else
		result = N ();

	return result;
}

double Calc::N ()
{
	char digit[128];
	int  size = 0;

	while((symbols[counter] >= '0' && symbols[counter] <= '9') || symbols[counter] == '.')
		digit[size++] = symbols[counter++];

	digit[size++] = '\0';

	return atof(digit);	
}
