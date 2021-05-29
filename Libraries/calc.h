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

		double GetG();
		double GetE();
		double GetT();
		double GetQ();
		double GetF();
		double GetP();
		double GetN();
		int Math_Func();
};

double Call_Func(int func, double tmp_res);
void Create_Expession(char** str, int str_cnt);