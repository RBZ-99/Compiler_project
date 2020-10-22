#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grammar_parser.h"
#include "hashtable.h"

void grammar_fill(FILE *fptr);
int main()
{
	printf("Here \n");
FILE *fptr = fopen("grammar.txt", "r");
				if (fptr == NULL) {
					perror("fopen");
				}
				grammar_fill(fptr);
				for(int i=0;i < 100;i++)
				{
					printf("It is %u \n",grammar[i].lhs);
				}
}
