#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* ---------------- Declaration of global functions ---------------- */
typedef struct ValueNode {
  long double value;
  struct ValueNode* next;
} ValueNode;

typedef struct OperatorNode {
  char symbol;
  int precedence;
  struct OperatorNode* next;
} OperatorNode;

void pushValueStack(ValueNode** topValue, long double value);
int popValueStack(ValueNode** topValue, long double* value);
void pushOperatorStack(OperatorNode** topOperator, char symbol, int precedence);
int popOperatorStack(OperatorNode** topOperator);
int peekOperatorPrecedence(OperatorNode** topOperator);