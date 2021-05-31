#pragma once
#include <stdio.h>


class Stack;

class Node
{
	public:
		char* data  = nullptr;
		Node* left  = nullptr;
		Node* right = nullptr;

		Node (const char* Data, int size);
		Node (const char* Data);
	   ~Node ();
		Node (const Node& node) = delete;
		Node& operator= (Node& node);


		void Graph    ();
		void graph_	  (FILE* f_graph);
		void g_print_ (FILE* f_graph);
		void isconst  (int* variables);

		Node* Copy ();
		Node* Differentiator ();
};
