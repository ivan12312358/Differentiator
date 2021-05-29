double Call_Func(int func, double tmp_res);

enum functions 
{
	SIN = 1, COS,	TAN,
	CTAN,	ASIN,	ACOS,
	ATAN,	ACTAN,	SINH, 
	COSH,	TANH,	CTANH,
	ASINH,	ACOSH,	ATANH,
	ACTANH, EXP,	LN,
	LG,	LOG,	SQRT
};


class Calc
{
	public:
		char* symbols = nullptr;
		int   counter = 0;
		int   error   = 0;

		Calc(char* filename);
		~Calc();

		double G();
		double E();
		double T();
		double Q();
		double F();
		double P();
		double N();
		int Math_Func();
};
