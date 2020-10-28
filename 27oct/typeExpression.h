#include<stdio.h>
#include<stdbool.h>

typedef enum ArrayType{prim, rect, jag} arrayType;
typedef enum BindType{static_bind, dynamic_bind, not_applicable} bindType;

typedef struct Range{
    int start;
    int end;
}range;

typedef struct JaggedTE{
    char* type;
    int dim;
    struct Range* r;
    char* elem;
} jaggedTE;

typedef struct RectTE{
    char* type;
    int dim;
    struct Range* r;
    char* elem;
} rectTE;

typedef struct PrimTE{
    char* type;
} primTE;

union TypeExpression{
        primTE pt;
        rectTE rt;
        jaggedTE jt;
        
};

typedef struct TypeExpressionCell{
    char name[21]; //FIELD-1
    arrayType at; //FIELD-2
    bindType bt; //FIELD-3
    union TypeExpression te; //FIELD-4
} typeExpressionCell;

typeExpressionCell typeExpressionTable[100];