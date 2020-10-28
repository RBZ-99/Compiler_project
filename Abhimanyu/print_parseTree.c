#define MAX_LEXEME_LEN 100
#include "lexer.h"

void print_parse_tree(tree_node *root) {
	if (root == NULL)
		return;
    print_node(root);
	
    if (root->leftmost_child)
		print_parse_tree(root->leftmost_child);
	

	if (root->leftmost_child)
  	{
		tree_node *temp = root->leftmost_child->sibling;

		while (temp != NULL) 
		{
			print_parse_tree(temp);
			temp = temp->sibling;
		}
  	}
}
void print_node(tree_node *node) 
{
	char *s = (char *)calloc(MAX_LEXEME_LEN, sizeof(char));
	for (int i = 0; i < MAX_LEXEME_LEN; i++) 
	{
		s[i] = '\0';
	}

	if(node == NULL)
		return;

	bool is_terminal = (node->sym).is_terminal;

	if (is_terminal == true){
        pretty_print(node->sym.t);
        pretty_print("Terminal");
        pretty_print("-----");
        if((node->token).name==NUMBER)
        {
			snprintf(s, MAX_LEXEME_LEN, "%d", (node->token).data.num);
			pretty_print(s);            
        }
        else if((node->token).name==RNUMBER)
        {
			snprintf(s, MAX_LEXEME_LEN, "%f", (node->token).data.rnum);
			pretty_print(s);
        }
        else
        {
			snprintf(s, MAX_LEXEME_LEN, "%s", (node->token).data.str);
			pretty_print(s);           
        }        
        snprintf(s, MAX_LEXEME_LEN, "%d", (node->token).line_no);
		pretty_print(s);
        pretty_print("-----");
        pretty_print()//Depth
        printf("\n\n")
	} 
	else 
	{
        pretty_print(node->sym.nt);
		pretty_print("Non Terminal");
		pretty_print();//Type Expression
		pretty_print("----");
		pretty_print("----");
        pretty_print()//Grammar rule
        pretty_print()//Depth
        printf("\n\n")
	}
}
void pretty_print(char *s) {
	int column_size = 66;
    int len, left_margin;

	len = strlen(s);
	left_margin = (column_size - len) / 2;

	for (int i = 0; i < left_margin; i++)
	{
		printf(" ");
	}

	printf("%s", s);
	
	int right_margin = left_margin;
	
	if (len % 2 == 1)
		right_margin++;
	for (int i = 0; i < right_margin; i++) 
	{
		printf(" ");
	}
	
	printf("|");
}
