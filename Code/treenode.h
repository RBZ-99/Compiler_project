tree_node *parse_input_source_code(FILE *source) {

  stack *main_stack = stack_init();
  stack *aux_stack = stack_init();
  tree_node *root = create_tree_node();
  root->sym.nt = MAINPROGRAM; // FIRST WORD
  root->sym.is_terminal = false; // THIS MEANS 1st word is not terminal
  push(main_stack, root); // push start symbol on stack
  TOKEN tkn = get_next_token(source);

  int present_rule_no = 0; // FOR every new non terminal start with 0 and when backtracking continue with the stored rule_no + 1
  // This is a pointer_to_traverse_grammar
  
  tree_node *last_popped_nt_node; // USE THIS AHEAD SOMEHWERE

  while(true):
    num_tree_nodes++;
	  tree_node *node = (tree_node *)pop(main_stack);
    if ((node != NULL) && (node->sym).is_terminal == true) 
    {
	    /*

      CHECK IF WE REALLY NEED THIS EPSILON

      */
     
     if (node->sym.t == EPSILON) 
      {
		    node->token.name = EPSILON;
		    strncpy(node->token.id.str, "epsilon", MAX_LEXEME_LEN);
		  continue;
	    } 

      if (node->sym.t != tkn.name) // terminal on top of stack does not match
								   // with lookhead symbol
	    {
        TREENODE* popped = pop(aux_stack);
        while(popped->last_popped_nt == NULL)
        {
          popped = pop(aux_stack);
        }
        last_popped_nt_node = popped->last_popped_nt;
        pop(aux_stack);
        last_popped_nt_node->rule_no +=1;
        present_rule_no = last_popped_nt_node->rule_no;

      }

      if(grammar[present_rule_no].lhs == node.token)
      {

       // push(aux_stack,node);
        cell rule = grammar[rule_no];
	      rhsnode_ptr rhs_ptr = rule.head;
        while (rhs_ptr != NULL) 
        {
	        tree_node *temp = create_tree_node();
	        temp->parent = node;
	        temp->sym = rhs_ptr->sym;
	        add_child(node, temp);
	        push(aux_stack, temp);
	        rhs_ptr = rhs_ptr->next;
	    }

      tree_node *temp = (tree_node *)pop(aux_stack);
      temp.last_popped_nt= node;
      node->rule_no = present_rule_no;

    	while (temp != NULL) 
      {
	      push(main_stack, temp);
	      temp = (tree_node *)pop(aux_stack);
      }
       
       // WHEN WOULD WE PUSH THE SELECTED NOTE TO MAIN_STACK???? push(main_stack,node);
       continue;
      }




        // TRACK  if we went ahead in the source code? or do we even move ahead 
        //in the source code until we get the fully matching non
      
      









typedef struct TREENODE
{
	struct TREENODE *parent;
	struct TREENODE *sibling;
  struct TREENODE *leftmost_child;
  struct TREENODE *rightmost_child;
  struct TREENODE *last_popped_nt;
  int rule_no;
  

  struct TREENODE *node_inh;
  struct TREENODE *node_syn;
  st_wrapper *scope_sym_tab;
  type *encl_fun_type_ptr;
  symbol sym;
  TOKEN token;
  int num_child;
  bool visited;
  void *extra_args;
  struct{
    struct{
      char *true_label;
      char *false_label;
    }boolean;
    char *next_label;
    char *cnstrct_code_begin;
  }label;
  char *addr;
  struct{
    int start;
    int end;
  }line_nums;

} tree_node;
