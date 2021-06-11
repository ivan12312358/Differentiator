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
		Node ();
	   ~Node ();
		Node (const Node& node) = delete;
		Node& operator= (Node& node);


		int isoperator ();
		void Graph    	();
		void graph_	  	(FILE* f_graph);
		void g_print_ 	(FILE* f_graph);
		void isconst  	(int* variables);
		void Const_Reduction  (int* change);
		void Tex		(char* f_func);
		void Tex_Create (FILE* f_tex);
		void Tex_Open	(char* func, char* out_file);

		Node* Identity_Elem (int* change);
		Node* Delete_Elem	(const char* neutral_elem);
		Node* Copy ();
		Node* Differentiator ();
};

void Simplifying_Expr (Node** head);
