#include<stdio.h>
#include<stdlib.h>

#include "../include/account.h"
#include "../include/transaction.h"
#include "../include/admin.h"

int main() {

    int choice;

    while(1) {

        printf("\n");
        printf("===== BANK MANAGEMENT SYSTEM =====\n");

        printf("1. Create Account\n");
        printf("2. Login\n");
        printf("3. Check Balance\n");
        printf("4. Deposit\n");
        printf("5. Withdraw\n");
        printf("6. Admin Panel\n");
        printf("7. Exit\n");

        printf("\nEnter Choice: ");
        scanf("%d", &choice);

        switch(choice) {

            case 1:
                createAccount();
                break;

            case 2:
                login();
                break;

            case 3:
                checkBalance();
                break;

            case 4:
                deposit();
                break;

            case 5:
                withdrawMoney();
                break;

            case 6:
                adminPanel();
                break;

            case 7:
                printf("\nThank You!\n");
                exit(0);

            default:
                printf("\nInvalid Choice!\n");
        }
    }

    return 0;
}