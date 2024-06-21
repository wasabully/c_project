#ifndef S21_CALC_H
#define S21_CALC_H

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "s21_stack.h"

/* ---------------- Declaration of global functions ---------------- */
int SmartCalc(const char* str_input, long double* result);
void initializeValueStack(ValueNode** valueStack, char initialSymbol);
void clear_expression_stacks(ValueNode** ValueNode,
                             OperatorNode** OperatorNode);
int processExpression(char* str, ValueNode** valueStack,
                      OperatorNode** operatorStack);
int finalizeCalculation(ValueNode** valueStack, OperatorNode** operatorStack,
                        long double* result);
int calculator(ValueNode** valueStack, OperatorNode** Operator_Node);
int validate_math_expression(const char* str);
void handleUnaryOperator(char** str, ValueNode** ValueNode,
                         char* operator_found);
int process_math_expression(char** str, ValueNode** ValueNode,
                            OperatorNode** OperatorNode);
void determine_operator_priority(char arith_oper, int* priority, int* step);
void determine_arithmetic_operator(char** str, char* arith_oper);

/* ----------------   X    ---------------- */
int SmartCalc_X(const char* input_str, long double* result, long double x);

/* ---------------- Credit ---------------- */
double calculateAnnuityPayment(double principal, double annualInterestRate,
                               int numberOfPayments);
double calculateDifferentialPayment(double principal, double annualInterestRate,
                                    int numberOfPayments);
double calculateTotalPayments(double principal, double annualInterestRate,
                              int numberOfPayments);

#endif