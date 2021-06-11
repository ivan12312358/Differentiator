#define dL *left->Differentiator ()
#define dR *right->Differentiator ()
#define dF *F_node->Differentiator ()
#define cF *F_node->Copy ()
#define cR *right->Copy ()
#define cL *left->Copy ()
#define cH *Copy ()

const size_t DIGIT = 10;

class Node;

Node* operator * (Node& L, Node& R);

Node* operator + (Node& L, Node& R);

Node* operator - (Node& L, Node& R);

Node* operator / (Node& L, Node& R);

Node* operator ^ (Node& L, Node& R);

/* Node* exp  (Node* node);      Node* ln (Node* node);       Node* lg (Node* node);

Node* log  (Node* node);      Node* sqrt (Node* node);     

Node* tan (Node* node);      Node* ctan (Node* node);

Node* asin  (Node* node);     Node* acos (Node* node);     Node* atan (Node* node);

Node* actan  (Node* node);    Node* sinh (Node* node);     Node* cosh (Node* node);

Node* tanh  (Node* node);     Node* ctanh (Node* node);    Node* asinh (Node* node);

Node* acosh  (Node* node);    Node* atanh (Node* node);    Node* actanh (Node* node);
 */

Node* ln (Node* F_node);	Node* sin (Node* node); 	Node* cos  (Node* node);

/* const char* mass[] = {	"EXP",	    "LN",       "LG",
						"LOG",	    "SQRT"      "SIN",
						"COS",	    "TAN",      "CTAN",
						"ASIN",	    "ACOS",     "ATAN",	
						"ACTAN",	"SINH",     "COSH",	
						"TANH",	    "CTANH",    "ASINH", 
						"ACOSH",	"ATANH",    "ACTANH" };

Node* (*funcs[]) (Node*) = {	exp, 	ln, 	lg,
								log,	sqrt,	sin,
								cos,	tan,	ctan,
								asin,	acos,	atan,
								actan,	sinh,	cosh,
								tanh,	ctanh,	asinh,
								acosh,	atanh,	actanh	};

 */

void brackets(char* symbols, int size);
void str_tolower(char* l_data, char* data, int size);

const char* mass[] = {"LN", "SIN", "COS"};

Node* (*funcs[]) (Node*) = {ln, sin, cos};