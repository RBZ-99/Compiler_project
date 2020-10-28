#include<string.h>
#include "grammar_parser.h"
#include "stackdef.h"
//#include "lexer.h"
#include<stdbool.h>
#include <stdlib.h>
#include "typeExpression.h"

typedef struct TREENODE
  {
    struct TREENODE *parent;
    struct TREENODE *sibling;
    struct TREENODE *leftmost_child;
    struct TREENODE *rightmost_child;
    
    struct TREENODE *last_popped_nt;
    int rule_no;

    symbol sym; //simplify this
    tokenStream token;
    int num_child; // make this 0 when emptied
    bool visited;
    int depth;
    union TypeExpression te;

  } tree_node;

tree_node* create_tree_node();
void add_child(tree_node* parent,tree_node* child);
void deallocate1(tree_node* node);
tree_node *parse_input_source_code(tokenStream* streamHead, cell grammar[]);

