#include "../Libraries/files.h"
#include "../Libraries/node.h"
#include "../Libraries/stack.h"

Node::Node (char* data) : 
	data (data) 
{
	left = nullptr;
    right = nullptr;
}

//-------------------------------------------------------------------------------

void Node::free_ ()
{
	if(left)  left ->free_ ();
	if(right) right->free_ ();
	if(data)  free (data);
			  free (this);
}

void Node::graph_ (FILE* f_graph)
{
	if(left == nullptr || right == nullptr)
		return;

	fprintf  (f_graph, "\tsubgraph cluster\n\t{\n");
	g_print_ (f_graph);

	 left->graph_ (f_graph);
	right->graph_ (f_graph);
}

//-------------------------------------------------------------------------------

void Node::g_print_ (FILE* f_graph)
{
	fprintf (f_graph, "\t\t%s ->\n\t\t{\n"
	"\t\t\t%s [shape = \"box3d\", fillcolor = red, style = \"filled\"];\n"
	"\t\t\t%s [shape = \"box3d\", fillcolor = green, style = \"filled\"];\n\t\t}\n\t}\n",
																			   data, 
																		 left->data,
																		right->data);
}