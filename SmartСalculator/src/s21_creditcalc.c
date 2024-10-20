#include "s21_calc.h"

double calculateAnnuityPayment(double principal, double annualInterestRate,
                               int numberOfPayments) {
  double monthlyInterestRate = annualInterestRate / 100 / 12;
  double discountFactor =
      (pow(1 + monthlyInterestRate, numberOfPayments) - 1) /
      (monthlyInterestRate * pow(1 + monthlyInterestRate, numberOfPayments));
  double monthlyPayment = principal / discountFactor;
  return monthlyPayment;
}

double calculateDifferentialPayment(double principal, double annualInterestRate,
                                    int numberOfPayments) {
  double monthlyInterestRate = annualInterestRate / 100 / 12;
  double monthlyPayment =
      principal / numberOfPayments + (principal * monthlyInterestRate);
  return monthlyPayment;
}

double calculateTotalPayments(double principal, double annualInterestRate,
                              int numberOfPayments) {
  double totalPayments = 0;
  double remainingPrincipal = principal;
  double monthlyInterestRate = annualInterestRate / 100 / 12;

  for (int month = 1; month <= numberOfPayments; ++month) {
    double monthlyPayment =
        principal / numberOfPayments + remainingPrincipal * monthlyInterestRate;
    totalPayments += monthlyPayment;
    remainingPrincipal -= principal / numberOfPayments;
  }

  return totalPayments;
}