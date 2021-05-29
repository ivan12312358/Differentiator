class Stack;
class Node;

class Tree
{
	Node* head_ = nullptr;

	public:
		Tree ();
	   ~Tree ();
		Tree (const Tree& tree) = delete;
		Tree& operator= (Tree& tree);
		void Graph ();
};