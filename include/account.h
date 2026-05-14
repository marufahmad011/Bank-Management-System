#ifndef ACCOUNT_H
#define ACCOUNT_H

typedef struct {
    int accNo;
    char name[50];
    int pin;
    double balance;
} Account;

int isAccountExists(int accNo);
void createAccount();
int loginUser(Account *loggedInAcc);
void updateProfile(Account *acc);
void changePIN(Account *acc);
void updateAccountInFile(Account updatedAcc);

#endif