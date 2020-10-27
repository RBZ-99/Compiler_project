# define GRAMMAR_SIZE 100 // check the final length of grammar which is not 100 atleast now
# define HASHTAG 10000

#include<string.h>
#include "grammar_parser.h"
#include "stackdef.h"
//#include "lexer.h"
#include<stdbool.h>
#include <stdlib.h>

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
    
  } tree_node;

tree_node* create_tree_node();


void add_child(tree_node *parent, tree_node *child) {
  if (parent->rightmost_child == NULL) {
    parent->leftmost_child = child;
    parent->rightmost_child = child;
  } else {
    parent->rightmost_child->sibling = child;
    parent->rightmost_child = child;
  }
  parent->num_child++;
  child->parent = parent;
  child->sibling = NULL;
  
}


void deallocate1(tree_node* node)
{
  //do nothing if passed a non-existent node
    if(node == NULL)
        return;
    //now onto the recursion
    deallocate1(node->leftmost_child);
    deallocate1(node->sibling);
    // KEPP THIS FOR AFTER WARDS num_tree_nodes--;
    free(node);
}



tree_node *parse_input_source_code(tokenStream* streamHead, cell grammar[])
{

  stack *main_stack = stack_init();
  stack *aux_stack = stack_init();
  tree_node *root = create_tree_node();
  /******************************************************************************************************************/

  root->sym.nt = MAINPROGRAM;    // FIRST WORD : HARDCODE THIS

  /******************************************************************************************************************/
  root->sym.is_terminal = false; // THIS MEANS 1st word is not terminal
  push(main_stack, root);        // push start symbol on stack
  tokenStream *tkn = streamHead; // gives the next token

  int present_rule_no = 0; // FOR every new non terminal start with 0 and when backtracking continue with the stored rule_no + 1
  // This is a pointer_to_traverse_grammar

  tree_node *last_popped_nt_node; // USE THIS AHEAD SOMEHWERE

  while (true)
  {
    //num_tree_nodes++;
    tree_node *node = (tree_node *)pop(main_stack);

    if(tkn == NULL)              //    if(tkn.name == NULL)  //HASHTAG) // HASHTAG an ending symbol to mark the end of source code
    {
      if(node != NULL)
        printf(" This is an error: STACK NOT EMPTIED but SOURCE CODE is finished parsing \n");
      
    break;
    }
    if(node == NULL)
    {
        if(tkn == NULL)        //if(tkn.name != NULL)//HASHTAG)
        printf(" This is an error: STACK EMPTIED but still symbols are left in source code \n");
      
    break;
    } // This is when source code ends? but what if just the stack became empty?
    // add a symbol at the end of source code to check if that is what we have reached

    if ((node != NULL) && (node->sym).is_terminal == true)
    {
      /*
      CHECK IF WE REALLY NEED THIS EPSILON
      
      if (node->sym.t == EPSILON)
      {
        node->token.name = EPSILON;
        strncpy(node->token.data.str, "epsilon", MAX_LEXEME_LEN);
        continue;
      }
      */
      if (node->sym.t != tkn->name) // terminal on top of stack does not match
                                   // with lookhead symbol
      {
        // Make a function ot free children nodes : make the pointer of the parent to its chilren as NULL and also update
        // its no of childten count and also free the nodes to save memory
        //TREENODE *popped = pop(main_stack);
        tree_node* popped;
        popped = node;
        
        while (popped->last_popped_nt == NULL)
        {
          popped = pop(main_stack); 
        }
        last_popped_nt_node = popped->last_popped_nt; 
        last_popped_nt_node->rule_no += 1;
        present_rule_no = last_popped_nt_node->rule_no;
        
        deallocate1(last_popped_nt_node->leftmost_child);
        last_popped_nt_node->num_child = 0;

        last_popped_nt_node->leftmost_child = NULL;
        last_popped_nt_node->rightmost_child = NULL;

        push(main_stack,last_popped_nt_node);
        continue;
      }

      if (node->sym.t == tkn->name)
      {

        node->token.line_no = tkn->line_no;// DONT KNOW WHY saving the line_no
        node->token.name = tkn->name; // why???- > TYPE EXPRESSINO K LIYE
        switch(tkn->name)
        {
        case NUMBER:
          node->token.data.num = tkn->data.num;
          break;

        case RNUMBER:
          node->token.data.rnum = tkn->data.rnum;
          break;

        default:
          // node->token.id.str = (char *)malloc(sizeof(MAX_LEXEME_LEN));
          strncpy(node->token.data.str, tkn->data.str, MAX_LEXEME_LEN);
        }

        tkn = tkn->next;
        //pop(main_stack); // AS OF NOW THIS IS REPEATED POP SINCE WE HAVE ALREADY POPPED JUST AFTER WHILE
        continue;
      }
    }
    else
    //if ((node != NULL) && (node->sym).is_terminal == false) // make this one else both are same
    // We are always assuming node is not null
    {
      //node->rule_no = present_rule_no;
      present_rule_no = node->rule_no; // we'll have to intitalize rule_no of every node as 0

      while(grammar[present_rule_no].lhs != node->sym.nt && grammar[present_rule_no].lhs != NULL) 
      {
        present_rule_no++; 
      }
      if(present_rule_no >= GRAMMAR_SIZE) break; // also add a ending condition when it ends normally 
      // GRAMMAR_SIZE : hardcoded size of the grammar

      cell rule = grammar[present_rule_no];
      node->rule_no = present_rule_no;
      rhsnode_ptr rhs_ptr = rule.head;
      tree_node *temp;
      while(rhs_ptr != NULL)
      {
        temp = create_tree_node();
        temp->parent = node;
        temp->sym = rhs_ptr->sym;
        add_child(node, temp);
        push(aux_stack, temp);
        rhs_ptr = rhs_ptr->next;
      }

      temp->last_popped_nt = node;
      temp = (tree_node*)pop(aux_stack);

      while(temp != NULL)
      {
        push(main_stack, temp);
        temp = (tree_node*)pop(aux_stack);
      }

    }
  }
}
    /*
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
       
       // WHEN WOULD WE PUSH THE SELECTED NOTE TO MAIN_STACK???? push(main_stack,node); */


  // TRACK  if we went ahead in the source code? or do we even move ahead
  //in the source code until we get the fully matching non

  


/**
 * @brief Create a tree node object
 *
 * @return pointer to created node
 */

tree_node *create_tree_node() {
  tree_node *node = (tree_node *)malloc(sizeof(tree_node));
  if (node == NULL) {
    perror("tree_node allocation error..\n");
    exit(0);
  }

  node->visited = false;
  node->parent = NULL;
  node->sibling = NULL;
  node->leftmost_child = NULL;
  node->rightmost_child = NULL;

  node->num_child = 0;
  strncpy(node->token.data.str, "", MAX_LEXEME_LEN);

  node->rule_no = 0; // specially done
  node->last_popped_nt = NULL;// specially done
  return node;
}

int main(){
    tokenStreamHead* streamHead = (tokenStreamHead* )malloc(sizeof(tokenStreamHead)); 
    streamHead->head = NULL;
    FILE *f = fopen("sourceCode.txt","rb");
    tokeniseSourceCode(f,streamHead);
    printf("DONE");
    fclose(f);   
    //printTokenStream(streamHead->head);
    cell grammar[5];
    parse_input_source_code(streamHead->head,grammar);
    return 0;
}

