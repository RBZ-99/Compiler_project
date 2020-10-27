typedef enum {
  #include "tokens.txt"
} token_name;

typedef struct TokenStream{
  token_name name;
  int tag; // 0 -string, 1 - number 2 - Real number
  union Data {
    char str[21];
    int num;
    double rnum;
  } data;
  int line_no;
  struct TokenStream* next;
} tokenStream;

typedef struct TokenStreamHead{
  int count;
  tokenStream* head;
} tokenStreamHead;




