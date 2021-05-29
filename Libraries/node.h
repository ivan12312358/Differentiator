#pragma once
#include <stdio.h>


class Stack;

class Node
{
	public:
		char* data  = nullptr;
		Node* left  = nullptr;
		Node* right = nullptr;

		Node (char* data);
		void free_	  ();
		void graph_	  (FILE* f_graph);
		void g_print_ (FILE* f_graph);
		Node (const Node& node) = delete;
		Node& operator= (Node& node);
};
