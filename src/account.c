#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "../include/account.h"

void clearInputBuffer() {

    int c;

    while((c = getchar()) != '\n' && c != EOF);
}

int accountExists(int accNo) {

    FILE *fp;

    struct Account user;

    fp = fopen("data/accounts.txt", "r");

    if(fp == NULL) {
        return 0;
    }

    while(fscanf(fp, "%d|%99[^|]|%d|%f\n",
                 &user.accNo,
                 user.name,
                 &user.pin,
                 &user.balance) != EOF) {

        if(user.accNo == accNo) {

            fclose(fp);
            return 1;
        }
    }

    fclose(fp);

    return 0;
}

void createAccount() {

    FILE *fp;

    struct Account user;

    fp = fopen("data/accounts.txt", "a");

    if(fp == NULL) {

        printf("\nFile Error!\n");
        return;
    }

    printf("\nEnter Account Number: ");
    scanf("%d", &user.accNo);

    if(accountExists(user.accNo)) {

        printf("\nAccount Already Exists!\n");

        fclose(fp);
        return;
    }

    clearInputBuffer();

    printf("Enter Name: ");
    fgets(user.name, sizeof(user.name), stdin);

    user.name[strcspn(user.name, "\n")] = 0;

    printf("Enter 4 Digit PIN: ");
    scanf("%d", &user.pin);

    if(user.pin < 1000 || user.pin > 9999) {

        printf("\nPIN Must Be 4 Digits!\n");

        fclose(fp);
        return;
    }

    printf("Enter Initial Balance: ");

    scanf("%f", &user.balance);

    if(user.balance < 0) {

        printf("\nInvalid Balance!\n");

        fclose(fp);
        return;
    }

    fprintf(fp, "%d|%s|%d|%.2f\n",
            user.accNo,
            user.name,
            user.pin,
            user.balance);

    fclose(fp);

    printf("\n===== ACCOUNT CREATED SUCCESSFULLY =====\n");
}

void login() {

    FILE *fp;

    struct Account user;

    int accNo, pin;
    int found = 0;

    fp = fopen("data/accounts.txt", "r");

    if(fp == NULL) {

        printf("\nNo Account Found!\n");
        return;
    }

    printf("\nEnter Account Number: ");
    scanf("%d", &accNo);

    printf("Enter PIN: ");
    scanf("%d", &pin);

    while(fscanf(fp, "%d|%99[^|]|%d|%f\n",
                 &user.accNo,
                 user.name,
                 &user.pin,
                 &user.balance) != EOF) {

        if(user.accNo == accNo && user.pin == pin) {

            found = 1;

            printf("\n===== LOGIN SUCCESSFUL =====\n");

            printf("Account Number : %d\n", user.accNo);
            printf("Name           : %s\n", user.name);
            printf("Balance        : %.2f\n", user.balance);
        }
    }

    if(found == 0) {

        printf("\nInvalid Account Number or PIN\n");
    }

    fclose(fp);
}

void checkBalance() {

    FILE *fp;

    struct Account user;

    int accNo, pin;
    int found = 0;

    fp = fopen("data/accounts.txt", "r");

    if(fp == NULL) {

        printf("\nNo Data Found!\n");
        return;
    }

    printf("\nEnter Account Number: ");
    scanf("%d", &accNo);

    printf("Enter PIN: ");
    scanf("%d", &pin);

    while(fscanf(fp, "%d|%99[^|]|%d|%f\n",
                 &user.accNo,
                 user.name,
                 &user.pin,
                 &user.balance) != EOF) {

        if(user.accNo == accNo && user.pin == pin) {

            found = 1;

            printf("\n===== ACCOUNT BALANCE =====\n");

            printf("Name    : %s\n", user.name);
            printf("Balance : %.2f\n", user.balance);
        }
    }

    if(found == 0) {

        printf("\nInvalid Account!\n");
    }

    fclose(fp);
}