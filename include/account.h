#ifndef ACCOUNT_H
#define ACCOUNT_H

struct Account {

    int accNo;
    char name[100];
    int pin;
    float balance;

};

void createAccount();
void login();
int accountExists(int);
void checkBalance();

#endif