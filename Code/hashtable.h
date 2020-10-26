#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
//#include "hashtableDef.h"

#define PRIME 119
#define HASH_SIZE 67
#define MAX_LEXEME_LEN 100
#define KEY_NOT_FOUND -1

typedef struct {
		char lexeme[MAX_LEXEME_LEN];
		void *value;
		bool present;
} hash_element;

typedef hash_element hash_table[HASH_SIZE];

typedef struct symbol_table_wrapper{
	hash_table table;
	int level_num;
	struct symbol_table_wrapper *parent_table;
	struct symbol_table_wrapper *leftmost_child_table;
	struct symbol_table_wrapper *rightmost_child_table;
	struct symbol_table_wrapper *sibling_table;
}st_wrapper;

int fast_mod_exp(int a, int b, int m);

//void init_hash_table(hash_table);

int hash(char *str);

//void hash_insert(hash_table table, char *lexeme, int value);

int search_hash_table(hash_table table, char *lexeme);
hash_table terminal_table;
hash_table non_terminal_table;
//void hash_insert_ptr_val(hash_table table, char *lexeme, void *value_ptr);

//void* search_hash_table_ptr_val(hash_table table, char *lexeme);

//bool key_present_in_table(hash_table table, char *lexeme);

#endif