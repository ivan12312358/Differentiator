#include "../Libraries/files.h"
#include "../Libraries/node.h"


Node::Node (const char* Data): 
	data (strdup(Data))
{
	left  = nullptr;
    right = nullptr;
}

//-------------------------------------------------------------------------------

Node::Node (const char* Data, int size): 
	data (strndup(Data, size))
{
	left  = nullptr;
	right = nullptr;
}

//-------------------------------------------------------------------------------

Node::~Node ()
{
	delete left;
	delete right;
	free   (data);
}

//-------------------------------------------------------------------------------

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
	fprintf (f_graph, "\t\t\"%p\" ->\n\t\t{\n"
	"\t\t\t\"%p\" [label = \"%s\", shape = \"box3d\", fillcolor = green, style = \"filled\"];\n"
	"\t\t\t\"%p\" [label = \"%s\", shape = \"box3d\", fillcolor = green, style = \"filled\"];\n\t\t}\n\t}\n",
																&data,
																&(left->data),   left->data, 
																&(right->data), right->data);
}

//-------------------------------------------------------------------------------

void Node::Graph ()
{
	if(data == nullptr)
	{
		printf ("Tree is empty\n");
		return;
	}

	printf ("Making graph...\n");
	printf ("Where to save your graph? Type name of file\n");

	int 	 SIZE  = 128;
	char buf[SIZE] = "";

	fgets(buf, SIZE, stdin);
	buf[strlen (buf) - 1] = '\0';

	char filename[512] = "";

	sprintf(filename, "%s.dot", buf);

	FILE*   f_graph = fopen (filename, "w");
	assert (f_graph);

	fprintf (f_graph, "digraph Tree {\n"
			"\tnode [shape = circle, width = 1]\n"
			"\tedge [color = \"blue\"];\n"
			"\tnodesep = 1.5\n"
			"\tbase [label = \"%s.dot\", fillcolor = yellow, style = \"rounded,filled\","
			"shape = doubleoctagon, fontsize = 15]\n\n"

			"\tsubgraph cluster\n\t{\n"
			"\t\tlabel = \"head\";\n"
			"\t\t\"%p\" [label = \"%s\", fillcolor = royalblue, style = \"rounded,filled\", shape = diamond]\n",
			buf, &data, data);

	if(right && left)
	{
		g_print_	  (f_graph);
		left ->graph_ (f_graph);
		right->graph_ (f_graph);
	}
	else
		fprintf (f_graph, "\t}\n");

	fprintf (f_graph, "\tlabel = \"This is Calculator base\";\n}\n");

	fclose  (f_graph);

	sprintf (filename, "dot -Tpng %s.dot -o %s.png", buf, buf);
	system  (filename);
}

//-------------------------------------------------------------------------------

