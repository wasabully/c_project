#include "s21_stack.h"

void pushValueStack(ValueNode **topValue, long double value) {
  ValueNode *newValueNode = (ValueNode *)malloc(sizeof(ValueNode));
  if (newValueNode) {
    newValueNode->value = value;
    newValueNode->next = NULL;

    if (*topValue == NULL) {
      *topValue = newValueNode;
    } else {
      newValueNode->next = *topValue;
      *topValue = newValueNode;
    }
  }
}

void pushOperatorStack(OperatorNode **topOperator, char symbol,
                       int precedence) {
  OperatorNode *newOperatorNode = (OperatorNode *)malloc(sizeof(OperatorNode));
  newOperatorNode->symbol = symbol;
  newOperatorNode->precedence = precedence;
  newOperatorNode->next = *topOperator;
  *topOperator = newOperatorNode;
}

int popValueStack(ValueNode **topValue, long double *value) {
  int error = 0;
  if (topValue) {
    if (*topValue) {
      ValueNode *tmp = *topValue;
      *topValue = (*topValue)->next;
      *value = tmp->value;
      free(tmp);
    } else
      error = -1;
  } else
    error = -1;
  return error;
}

int popOperatorStack(OperatorNode **topValue) {
  if (*topValue == NULL) {
    return '\0';
  }
  OperatorNode *temp = *topValue;
  *topValue = (*topValue)->next;
  char poppedSymbol = temp->symbol;
  free(temp);
  return poppedSymbol;
}

int peekOperatorPrecedence(OperatorNode **topValue) {
  if (*topValue == NULL) {
    return -1;
  }
  int precedence = (*topValue)->precedence;
  return precedence;
}