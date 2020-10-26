// parser.c
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "grammar_parser.h"
#include "hashtable.h" 


/**
 * @brief inserts a symbol at end of the given rule's list
 *
 * @param ptr_tail - tail pointer to rule's linked list
 * @param sym - symbol to be inserted
 */

symbol get_symbol(char str[]);


int search_hash_table(hash_table table, char *lexeme);
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
	//sym.nt = search_hash_table(non_terminal_table, str);
	sym.nt = searh_exists(str);
  } 
  // LOWER CASE TO UPPER CASE
  else {

	sym.is_terminal = true;
	char tmp[strlen(str)];
	strcpy(tmp, str);
	for (int i = 0; i < strlen(tmp); i++) {
	  tmp[i] = toupper(tmp[i]);
	}
	//sym.t = search_hash_table(terminal_table, tmp);
	sym.t = searh_exists(tmp);
  }
  return sym;
}