#ifndef PARSER_H
#define PARSER_H

#define RHS_MAX_LENGTH 100
#define NUM_OF_RULES 99

typedef enum
{
    #include "non_terminals.txt"
} nonterminal;

typedef enum {
#include "tokens.txt"
} token_name;


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
    symbol sym;
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
symbol get_symbol(char str[]);

#endif