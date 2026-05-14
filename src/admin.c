#include<stdio.h>

#include "../include/account.h"
#include "../include/admin.h"

void adminPanel() {

    FILE *fp;

    struct Account user;

    fp = fopen("data/accounts.txt", "r");

    if(fp == NULL) {

        printf("\nNo Accounts Found!\n");
        return;
    }

    printf("\n===== ALL ACCOUNTS =====\n\n");

    while(fscanf(fp, "%d|%99[^|]|%d|%f\n",
                 &user.accNo,
                 user.name,
                 &user.pin,
                 &user.balance) != EOF) {

        printf("Account No : %d\n", user.accNo);
        printf("Name       : %s\n", user.name);
        printf("Balance    : %.2f\n", user.balance);

        printf("--------------------------\n");
    }

    fclose(fp);
}