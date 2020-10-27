#include<stdio.h>
#include<stdlib.h>

# define INIT_STACK_SIZE 200;
typedef struct
{
    void **arr;
    int top;
    int size;
} stack;




/**
 * @brief Initializes stack
 *
 * creates an array of MAX_PARSING_NODES size dynamically
 *
 * @return stack* pointer to structure interface of stack
 */

stack *stack_init() {
  stack *stack_ptr = (stack *)malloc(sizeof(stack));
  if (stack_ptr == NULL) {
    perror("stack init error.. memory not available\n");
  }
  stack_ptr->size = INIT_STACK_SIZE;
  stack_ptr->arr =
      (void **)malloc(sizeof(void *) * (stack_ptr->size));
  if (stack_ptr->arr == NULL) {
    perror("stack array member init error.. memory not available\n");
  }
  stack_ptr->top = 0;
  return stack_ptr;
}




/**
 * @brief Remove the element from stack top
 *
 * @param stack_ptr - pointer to structure interface of stack
 * @return void* - Element removed
 */

void *pop(stack *stack_ptr) {
  if (stack_ptr->top == 0) {
    return NULL;
  }

  stack_ptr->top--;
  return stack_ptr->arr[stack_ptr->top];
}



/**
 * @brief Insert element to stack
 *
 * @param stack_ptr - pointer to structure interface of stack
 * @param node - tree node element to be inserted
 */

void push(stack *stack_ptr, void *node) {
  if (stack_ptr->top == (stack_ptr->size)) {
    stack_ptr->size *= 2;
    void **tmp =
        realloc(stack_ptr->arr, sizeof(void *) * stack_ptr->size);
    if (tmp == NULL) {
      perror("Error in doubling stack's size: realloc failed\n");
    } else {
      stack_ptr->arr = tmp;
    }
  }
  stack_ptr->arr[stack_ptr->top] = node;
  stack_ptr->top++;
}



/**
 * @brief Peek through the stack
 *
 * @param stack_ptr pointer to structure interface of stack
 * @return void* element at top
 */
void *top(stack *stack_ptr) {
  if (stack_ptr->top == 0) {
    return NULL;
  } else {
    return stack_ptr->arr[stack_ptr->top - 1];
  }
}