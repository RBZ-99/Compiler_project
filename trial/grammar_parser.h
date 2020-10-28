#ifndef GRAMMARPARSER_H
#define GRAMMARPARSER_H

#include<stdbool.h>
#include<stdio.h>

#include "lexer.h"
#define RHS_MAX_LENGTH 1000
#define NUM_OF_RULES 99

#define MAX_LEXEME_LEN 100

typedef enum
{
    #include "nonTerminals.txt"
} nonterminal;



typedef struct{
    union
    {
        token_name t;
        nonterminal nt;
    };
    bool is_terminal;
} symbol;


typedef struct rhsnode
{
    symbol* sym;
    struct rhsnode *next;
} rhsnode;

typedef struct rhsnode *rhsnode_ptr;

typedef struct
{
    nonterminal lhs;
    rhsnode_ptr head;
    rhsnode_ptr tail;
} cell;

cell grammar[NUM_OF_RULES];
symbol* get_symbol(char str[]);
int search_exists(char* lexeme);
void insert_at_end(rhsnode_ptr *ptr_tail, symbol* sym);
void grammar_fill(FILE *fptr, cell grammar[]);

#endif
