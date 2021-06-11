enum functions 
{
	SIN = 1, COS,	TAN,
	CTAN,	ASIN,	ACOS,
	ATAN,	ACTAN,	SINH, 
	COSH,	TANH,	CTANH,
	ASINH,	ACOSH,	ATANH,
	ACTANH, EXP,	LN,
	LG,		LOG,	SQRT
};


class Node;

class Calc
{
	public:
		char* symbols = nullptr;
		int   counter = 0;
		int   error   = 0;

		Calc(char* filename);
	   ~Calc();

		Node* GetG();
		Node* GetE();
		Node* GetT();
		Node* GetQ();
		Node* GetF();
		Node* GetP();
		Node* GetN();
		int Is_Num_Alpha();
};

void* Math_Func (char* symbols, int is_string);
double Call_Func(long func, double tmp_res);
void Create_Expession(char** str, int str_cnt);