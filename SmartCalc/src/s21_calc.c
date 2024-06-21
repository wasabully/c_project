#include "s21_calc.h"

int SmartCalc(const char* str_input, long double* result) {
  if (str_input == NULL) return -1;

  ValueNode* valueStack = NULL;
  OperatorNode* operatorStack = NULL;

  char* str = (char*)str_input;
  int error = validate_math_expression(str);

  if (!error) {
    initializeValueStack(&valueStack, *str);

    error = processExpression(str, &valueStack, &operatorStack);
  }

  if (!error) {
    error = finalizeCalculation(&valueStack, &operatorStack, result);
  }

  if (valueStack && !error) {
    if (valueStack->next != NULL) {
      error = -1;
      *result = 0;
    }
  }

  clear_expression_stacks(&valueStack, &operatorStack);
  return error;
}

void initializeValueStack(ValueNode** valueStack, char initialSymbol) {
  if (initialSymbol == '-' || initialSymbol == '+') {
    pushValueStack(valueStack, 0);
  } else {
    pushValueStack(valueStack, 1);
  }
}

void clear_expression_stacks(ValueNode** ValueNode,
                             OperatorNode** OperatorNode) {
  long double clear;
  while (*ValueNode) popValueStack(ValueNode, &clear);
  while (*OperatorNode) popOperatorStack(OperatorNode);
}

int processExpression(char* str, ValueNode** valueStack,
                      OperatorNode** operatorStack) {
  int error = 0;
  while (*str != '\0' && !error) {
    if (isdigit(*str)) {
      long double num = strtold(str, &str);
      pushValueStack(valueStack, num);
    } else {
      if (*str != ' ') {
        if (*str == '(') {
          pushOperatorStack(operatorStack, *str, 5);
        } else if (*str == ')') {
          while (peekOperatorPrecedence(operatorStack) != 5 && !error) {
            error = calculator(valueStack, operatorStack);
          }
          popOperatorStack(operatorStack);
        } else {
          error = process_math_expression(&str, valueStack, operatorStack);
        }
      }
      str++;
    }
  }
  return error;
}

int finalizeCalculation(ValueNode** valueStack, OperatorNode** operatorStack,
                        long double* result) {
  int error = 0;
  while (*operatorStack && !error) {
    error = calculator(valueStack, operatorStack);
  }
  if (!error) {
    popValueStack(valueStack, result);
  } else {
    *result = 0;
  }
  return error;
}

int calculator(ValueNode** valueStack, OperatorNode** Operator_Node) {
  long double num1 = 0, num2 = 0;
  char oper = popOperatorStack(Operator_Node);
  int error = popValueStack(valueStack, &num2);
  if (strchr("/+-*%^~m", oper)) {
    popValueStack(valueStack, &num1);
  }
  if (strchr("qlL", oper) && num2 < 0) {
    oper = -1;
  }
  if (num2 == 0 && strchr("/%", oper)) {
    oper = -2;
  }
  if (oper > -1) {
    if (oper == '+') {
      pushValueStack(valueStack, num1 + num2);
    } else if (oper == '-' || oper == '~') {
      pushValueStack(valueStack, num1 - num2);
    } else if (oper == '*') {
      pushValueStack(valueStack, num1 * num2);
    } else if (oper == '/') {
      pushValueStack(valueStack, num1 / num2);
    } else if (oper == '%' || oper == 'm') {
      pushValueStack(valueStack, fmodl(num1, num2));
    } else if (oper == '^') {
      pushValueStack(valueStack, powl(num1, num2));
    } else if (oper == 's') {
      pushValueStack(valueStack, sinl(num2));
    } else if (oper == 'c') {
      pushValueStack(valueStack, cosl(num2));
    } else if (oper == 't') {
      pushValueStack(valueStack, tanl(num2));
    } else if (oper == 'S') {
      pushValueStack(valueStack, asinl(num2));
    } else if (oper == 'C') {
      pushValueStack(valueStack, acosl(num2));
    } else if (oper == 'T') {
      pushValueStack(valueStack, atanl(num2));
    } else if (oper == 'l') {
      pushValueStack(valueStack, logl(num2));
    } else if (oper == 'L') {
      pushValueStack(valueStack, log10l(num2));
    } else if (oper == 'q') {
      pushValueStack(valueStack, sqrtl(num2));
    }
  } else {
    error = oper;
  }
  return error;
}

int validate_math_expression(const char* str) {
  int error = 0;
  int flag = 0;
  char oper = 0;
  if (!strchr("sctalf(-+x", *str) && !isdigit(*str)) {
    error = -1;
  }
  while (*str && !error) {
    if (*str != ' ') {
      if (*str == '(') {
        flag++;
      }
      if (*str == ')') {
        flag--;
      }
      if (*str != ' ' && *str != '(' && *str != ')' && *str != 's' &&
          *str != 'i' && *str != 'n' && *str != 'c' && *str != 'o' &&
          *str != 'q' && *str != 'r' && *str != 't' && *str != 'a' &&
          *str != 'l' && *str != 'm' && *str != 'd' && *str != 'g' &&
          *str != '.' && *str != '-' && *str != '+' && *str != 'x' &&
          *str != '/' && *str != '*' && *str != '%' && *str != '^' &&
          !isdigit(*str)) {
        error = -1;
      }
      if (strchr("/*^m)", *str) && strchr("+-(/*m^", oper)) {
        error = -1;
      }
      if (strchr("*", *str) && strchr("(", oper)) {
        error = -1;
      }
      oper = *str;
    }
    str++;
  }
  if (!strchr(")x", *(str - 1)) && !isdigit(*(str - 1))) {
    error = -1;
  }
  if (flag != 0) {
    error = -1;
  }
  return error;
}

int process_math_expression(char** str, ValueNode** ValueNode,
                            OperatorNode** OperatorNode) {
  int error = 0;
  char operator_found = '0';
  char* prov_symbol = *str - 1;
  while (*prov_symbol == ' ') {
    prov_symbol--;
  }

  if ((**str == '-' || **str == '+') && (strchr("+-/*%(d", *prov_symbol))) {
    handleUnaryOperator(str, ValueNode, &operator_found);
  } else {
    determine_arithmetic_operator(str, &operator_found);
  }

  if (str != NULL && operator_found != 0 && operator_found != '!') {
    int priority = 0, current_priority = 0, step = 0;
    current_priority = peekOperatorPrecedence(OperatorNode);
    determine_operator_priority(operator_found, &priority, &step);

    while (current_priority >= priority && current_priority != 5 &&
           current_priority != -1 && !error && priority != 6 &&
           (current_priority != 3 || priority != 3)) {
      error = calculator(ValueNode, OperatorNode);
      current_priority = peekOperatorPrecedence(OperatorNode);
    }

    if (!error) {
      pushOperatorStack(OperatorNode, operator_found, priority);
      *str += step;
    }
  } else if (operator_found != '!')
    error = -1;

  return error;
}

void handleUnaryOperator(char** str, ValueNode** ValueNode,
                         char* operator_found) {
  if (**str == '-') {
    pushValueStack(ValueNode, 0);
    *operator_found = '~';
  } else {
    *operator_found = '!';
  }
}

void determine_operator_priority(char operator_found, int* priority,
                                 int* step) {
  *priority = -1;
  *step = 0;
  if (strchr("+-", operator_found))
    *priority = 0;
  else if (strchr("*/", operator_found))
    *priority = 1;
  else if (strchr("%m", operator_found)) {
    *priority = 2;
    if (operator_found == 'm') *step = 2;
  } else if (strchr("sctSCTlLq", operator_found)) {
    *priority = 4;
    if (strchr("sctL", operator_found)) {
      *step = 2;
    } else if (strchr("SCTq", operator_found)) {
      *step = 3;
    } else if (strchr("l", operator_found)) {
      *step = 1;
    }
  } else if (strchr("^", operator_found))
    *priority = 3;
  else if (strchr("~", operator_found))
    *priority = 6;
}

void determine_arithmetic_operator(char** str, char* operator_found) {
  if (str != NULL) {
    int num = 3;
    if (strchr("+", **str))
      *operator_found = '+';
    else if (strchr("-", **str))
      *operator_found = '-';
    else if (strchr("*", **str))
      *operator_found = '*';
    else if (strchr("/", **str))
      *operator_found = '/';
    else if (strchr("%", **str))
      *operator_found = '%';
    else if (strchr("^", **str))
      *operator_found = '^';
    else if (!strncmp(*str, "ln(", num))
      *operator_found = 'l';
    else if (!strncmp(*str, "mod", num))
      *operator_found = 'm';
    else if (!strncmp(*str, "sin(", num++))
      *operator_found = 's';
    else if (!strncmp(*str, "cos(", num))
      *operator_found = 'c';
    else if (!strncmp(*str, "tan(", num))
      *operator_found = 't';
    else if (!strncmp(*str, "log(", num))
      *operator_found = 'L';
    else if (!strncmp(*str, "asin(", num++))
      *operator_found = 'S';
    else if (!strncmp(*str, "acos(", num))
      *operator_found = 'C';
    else if (!strncmp(*str, "atan(", num))
      *operator_found = 'T';
    else if (!strncmp(*str, "sqrt(", num))
      *operator_found = 'q';
    else
      *operator_found = 0;
  }
}