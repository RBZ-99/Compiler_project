// parser.c
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "grammar_parser.h"


/**
 * @brief inserts a symbol at end of the given rule's list
 *
 * @param ptr_tail - tail pointer to rule's linked list
 * @param sym - symbol to be inserted
 */

symbol get_symbol(char str[]);


int search_exists(char* lexeme)
{
	//printf(" in search exists %s \n",lexeme);
	//enum nonterminal a1 = lexeme;
	
int search_exists(char* lexeme)
{
	

    //non terminals
	if(strcmp(lexeme,"START") == 0) return 0;
	else if(strcmp(lexeme,"MAINPROGRAM") == 0) return 1;
	else if(strcmp(lexeme,"DECLARATIONSTMTS") == 0) return 2;
	else if(strcmp(lexeme,"ASSIGNMENTSTMTS") == 0) return 3;
	else if(strcmp(lexeme,"DECLARATIONSTMT") == 0) return 4;
	else if(strcmp(lexeme,"ASSIGNMENTSTMT") == 0) return 5;
	else if(strcmp(lexeme,"SINGLE_DEC") == 0) return 6;
	else if(strcmp(lexeme,"MULTI_DEC") == 0) return 7;
	else if(strcmp(lexeme,"TYPE") == 0) return 8;
	else if(strcmp(lexeme,"ARRAYTYPE") == 0) return 9;
	else if(strcmp(lexeme,"VARIABLE_NAMES,") == 0) return 10;
	else if(strcmp(lexeme,"RECTANGULAR_ARRAY") == 0) return 11;
	else if(strcmp(lexeme,"JAGGED_ARRAY") == 0) return 12;
	else if(strcmp(lexeme,"RANGES") == 0) return 13;
	else if(strcmp(lexeme,"RANGE") == 0) return 14;
	else if(strcmp(lexeme,"INDEX") == 0) return 15;
	else if(strcmp(lexeme,"DIMJAGGED") == 0) return 16;
	else if(strcmp(lexeme,"MAKEROWS") == 0) return 17;
	else if(strcmp(lexeme,"MAKEROWS2") == 0) return 18;
	else if(strcmp(lexeme,"NUM_LIST") == 0) return 19;
	else if(strcmp(lexeme,"LISTOFNUMLIST") == 0) return 20;
	else if(strcmp(lexeme,"NUMS") == 0) return 21;
	else if(strcmp(lexeme,"ARITHMETICSTATEMENT") == 0) return 22;
	else if(strcmp(lexeme,"LOGICALSTATEMENT") == 0) return 23;
	else if(strcmp(lexeme,"VAR") == 0) return 24;
	else if(strcmp(lexeme,"ARITHMETICOP") == 0) return 25;
	else if(strcmp(lexeme,"INDEX_LIST") == 0) return 26;
	else if(strcmp(lexeme,"ADDSUBOP") == 0) return 27;
	else if(strcmp(lexeme,"TERM") == 0) return 28;
	else if(strcmp(lexeme,"MULTDIVOP") == 0) return 29;
	else if(strcmp(lexeme,"INDEX2") == 0) return 30;
	else if(strcmp(lexeme,"LOGICALOP") == 0) return 31;
	else if(strcmp(lexeme,"LOGICALTERM") == 0) return 32;
	else if(strcmp(lexeme,"LOGICALFACTOR") == 0) return 33;
	
    // tokens
    if(strcmp(lexeme,"ASSIGNOP") == 0) return 0;
	else if(strcmp(lexeme,"SEMICOL") == 0) return 1;
    else if(strcmp(lexeme,"COL") == 0) return 2;
	else if(strcmp(lexeme,"SQBO") == 0) return 3;
	else if(strcmp(lexeme,"SQBC") == 0) return 4;
	else if(strcmp(lexeme,"BO") == 0) return 5;
	else if(strcmp(lexeme,"BC") == 0) return 6;
	else if(strcmp(lexeme,"COMMA") == 0) return 7;
	else if(strcmp(lexeme,"PLUS") == 0) return 8;
	else if(strcmp(lexeme,"MINUS") == 0) return 9;
	else if(strcmp(lexeme,"MUL") == 0) return 10;
	else if(strcmp(lexeme,"DIV") == 0) return 11;
	else if(strcmp(lexeme,"CBO") == 0) return 12;
	else if(strcmp(lexeme,"CBC") == 0) return 13;
	else if(strcmp(lexeme,"PROGRAM") == 0) return 14;
	else if(strcmp(lexeme,"DECLARE") == 0) return 15;
	else if(strcmp(lexeme,"LIST") == 0) return 16;
	else if(strcmp(lexeme,"OF") == 0) return 17;
	else if(strcmp(lexeme,"VARIABLES") == 0) return 18;
	else if(strcmp(lexeme,"ARRAY") == 0) return 19;
	else if(strcmp(lexeme,"SIZE") == 0) return 20;
	else if(strcmp(lexeme,"VALUES") == 0) return 21;
	else if(strcmp(lexeme,"JAGGED_ARRAY") == 0) return 22;
	else if(strcmp(lexeme,"INTEGER") == 0) return 23;
	else if(strcmp(lexeme,"REAL") == 0) return 24;
    else if(strcmp(lexeme,"BOOLEAN") == 0) return 25;
	else if(strcmp(lexeme,"LOGAND") == 0) return 26;
	else if(strcmp(lexeme,"LOGOR") == 0) return 27;
	else if(strcmp(lexeme,"RANGEOP") == 0) return 28;
	else if(strcmp(lexeme,"NUMBER") == 0) return 29;
	else if(strcmp(lexeme,"RNUMBER") == 0) return 30;
	else if(strcmp(lexeme,"VAR_ID") == 0) return 31;
	else if(strcmp(lexeme,"UNKNOWN") == 0) return 32;
	else if(strcmp(lexeme,"VAR_ERR") == 0) return 33;
	else if(strcmp(lexeme,"R1") == 0) return 34;



	else return 10000;
}
}


void insert_at_end(rhsnode_ptr *ptr_tail, symbol sym) {

  rhsnode_ptr node = (rhsnode_ptr)malloc(sizeof(rhsnode));

  if (node == NULL) {
	perror("insertion at end failed\n");
	exit(1);
  }
  node->sym = sym;
  node->next = NULL;

  if (*ptr_tail != NULL) {
	(*ptr_tail)->next = node;
  }
  *ptr_tail = node;
}





/**
 * @brief Constructs an array of linked list to represent grammar
 *
 * @param fptr
 */
void grammar_fill(FILE *fptr) {

  int rule_num = 0;
  char buffer[RHS_MAX_LENGTH];

  while (fgets(buffer, sizeof(buffer), fptr) != NULL) {
	char *sym_read;
	int i;

	sym_read = strtok(buffer, " \n");
	for (i = 0; sym_read != NULL; i++) {
	  if (i == 0) // LHS of a production
	  {
		grammar[rule_num].lhs = get_symbol(sym_read).nt;
		printf(" in grammar_fill %d \n",grammar[rule_num].lhs);
		grammar[rule_num].head = NULL;
		grammar[rule_num].tail = NULL;
	  } else {
		symbol sym = get_symbol(sym_read);
		insert_at_end(&(grammar[rule_num].tail), sym);
		if (grammar[rule_num].head == NULL) {
		  grammar[rule_num].head = grammar[rule_num].tail;
		}
	  }
	  sym_read = strtok(NULL, " \n");
	}
	rule_num++;
  }
}


symbol get_symbol(char str[]) {
  symbol sym;
  if ((str[0] >= 'A') && (str[0] <= 'Z')) {
	sym.is_terminal = false;
	
	sym.nt = search_exists(str);
  } 
  // LOWER CASE TO UPPER CASE
  else {

	sym.is_terminal = true;
	//int length = strlen(str);
	char tmp[100];
	strcpy(tmp, str);
	for (int i = 0; i < strlen(tmp); i++) {
	  tmp[i] = toupper(tmp[i]);
	}
	sym.t = search_exists(tmp);
  }
  return sym;
}