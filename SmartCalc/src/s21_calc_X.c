#include "s21_calc.h"

int SmartCalc_X(const char* input_str, long double* result, long double x) {
  if (input_str == NULL) return -1;

  ValueNode* valueStack = NULL;
  OperatorNode* operatorStack = NULL;

  char* str = (char*)input_str;
  int error = validate_math_expression(str);

  if (*str == '-' || *str == '+') {
    initializeValueStack(&valueStack, *str);
  } else {
    initializeValueStack(&valueStack, 1);
  }
  while (*str != '\0' && !error) {
    if (isdigit(*str)) {
      long double num = strtold(str, &str);
      pushValueStack(&valueStack, num);
    } else {
      if (*str == '(') {
        pushOperatorStack(&operatorStack, *str, 5);
      } else if (*str == ')') {
        while (peekOperatorPrecedence(&operatorStack) != 5 && !error) {
          error = calculator(&valueStack, &operatorStack);
        }
        popOperatorStack(&operatorStack);
      } else if (*str != ' ') {
        if (*str != 'x') {
          error = process_math_expression(&str, &valueStack, &operatorStack);
        } else {
          pushValueStack(&valueStack, x);
        }
      }
      str++;
    }
  }
  if (!error) {
    error = finalizeCalculation(&valueStack, &operatorStack, result);
  }
  if (valueStack) {
    if (valueStack->next != NULL) {
      error = -1;
      *result = 0;
    }
  }
  clear_expression_stacks(&valueStack, &operatorStack);
  return error;
}
