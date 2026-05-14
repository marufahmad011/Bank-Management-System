#include<stdio.h>
#include<stdlib.h>

#include "../include/account.h"
#include "../include/transaction.h"

void deposit() {

    FILE *fp, *temp;

    struct Account user;

    int accNo;
    float amount;

    int found = 0;

    fp = fopen("data/accounts.txt", "r");
    temp = fopen("data/temp.txt", "w");

    printf("\nEnter Account Number: ");
    scanf("%d", &accNo);

    printf("Enter Deposit Amount: ");
    scanf("%f", &amount);

    if(amount <= 0) {

        printf("\nInvalid Amount!\n");
        return;
    }

    while(fscanf(fp, "%d|%99[^|]|%d|%f\n",
                 &user.accNo,
                 user.name,
                 &user.pin,
                 &user.balance) != EOF) {

        if(user.accNo == accNo) {

            found = 1;

            user.balance += amount;

            printf("\nDeposit Successful!\n");
            printf("New Balance: %.2f\n", user.balance);
        }

        fprintf(temp, "%d|%s|%d|%.2f\n",
                user.accNo,
                user.name,
                user.pin,
                user.balance);
    }

    fclose(fp);
    fclose(temp);

    remove("data/accounts.txt");
    rename("data/temp.txt", "data/accounts.txt");

    if(found == 0) {

        printf("\nAccount Not Found!\n");
    }
}

void withdrawMoney() {

    FILE *fp, *temp;

    struct Account user;

    int accNo;
    float amount;

    int found = 0;

    fp = fopen("data/accounts.txt", "r");
    temp = fopen("data/temp.txt", "w");

    printf("\nEnter Account Number: ");
    scanf("%d", &accNo);

    printf("Enter Withdraw Amount: ");
    scanf("%f", &amount);

    while(fscanf(fp, "%d|%99[^|]|%d|%f\n",
                 &user.accNo,
                 user.name,
                 &user.pin,
                 &user.balance) != EOF) {

        if(user.accNo == accNo) {

            found = 1;

            if(amount > user.balance) {

                printf("\nInsufficient Balance!\n");

            } else {

                user.balance -= amount;

                printf("\nWithdraw Successful!\n");
                printf("Remaining Balance: %.2f\n", user.balance);
            }
        }

        fprintf(temp, "%d|%s|%d|%.2f\n",
                user.accNo,
                user.name,
                user.pin,
                user.balance);
    }

    fclose(fp);
    fclose(temp);

    remove("data/accounts.txt");
    rename("data/temp.txt", "data/accounts.txt");

    if(found == 0) {

        printf("\nAccount Not Found!\n");
    }
}