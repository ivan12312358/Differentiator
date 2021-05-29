#include "../Libraries/files.h"
#include "../Libraries/tree.h"
#include "../Libraries/node.h"

//-------------------------------------------------------------------------------

Tree::Tree()
{
	head_ = (Node*) calloc (1, sizeof(Node));
}

//-------------------------------------------------------------------------------

Tree::~Tree ()
{
	assert (head_);

	head_->free_ ();

	printf ("Bye!\n");
}

void Tree::Graph ()
{
	if(head_->data == nullptr)
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
			"\t\t%s [fillcolor = royalblue, style = \"rounded,filled\", shape = diamond]\n",
			buf, head_->data);

	if(head_->right && head_->left)
	{
		head_->g_print_		 (f_graph);
		head_->left ->graph_ (f_graph);
		head_->right->graph_ (f_graph);
	}
	else
		fprintf (f_graph, "\t}\n");

	fprintf (f_graph, "\tlabel = \"This is Akinator base\";\n}\n");

	fclose  (f_graph);

	sprintf (filename, "dot -Tpng %s.dot -o %s.png", buf, buf);
	system  (filename);
}

//-------------------------------------------------------------------------------
