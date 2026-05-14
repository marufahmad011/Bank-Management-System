#ifndef TRANSACTION_H
#define TRANSACTION_H
#include "account.h"

void deposit(Account *acc);
void withdraw(Account *acc);
void transfer(Account *acc);
void miniStatement(int accNo);
void saveTransaction(int accNo, const char *type, double amount);

#endif