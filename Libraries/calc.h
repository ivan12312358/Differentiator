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
		double P();
		double N();
};
