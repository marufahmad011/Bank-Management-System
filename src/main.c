#include <stdio.h>
#include <stdlib.h>
#include "../include/account.h"
#include "../include/transaction.h"
#include "../include/admin.h"
#include "../include/utils.h"

void userMenu(Account *acc) {
    int choice;
    do {
        clearScreen();
        printf("\n=== USER DASHBOARD ===\n");
        printf("Welcome, %s (Acc: %d)\n", acc->name, acc->accNo);
        printf("Balance: %.2f\n", acc->balance);
        printf("----------------------\n");
        printf("1. Deposit\n");
        printf("2. Withdraw\n");
        printf("3. Fund Transfer\n");
        printf("4. Mini Statement\n");
        printf("5. Change PIN\n");
        printf("6. Update Profile\n");
        printf("0. Logout\n");
        printf("Choice: ");
        choice = getIntInput();

        switch (choice) {
            case 1: deposit(acc); pauseScreen(); break;
            case 2: withdraw(acc); pauseScreen(); break;
            case 3: transfer(acc); pauseScreen(); break;
            case 4: miniStatement(acc->accNo); pauseScreen(); break;
            case 5: changePIN(acc); pauseScreen(); break;
            case 6: updateProfile(acc); pauseScreen(); break;
            case 0: printf("Logging out...\n"); pauseScreen(); break;
            default: printf("Invalid choice!\n"); pauseScreen();
        }
    } while (choice != 0);
}

int main() {
    int choice;
    do {
        clearScreen();
        printf("\n==================================\n");
        printf("     BANK MANAGEMENT SYSTEM       \n");
        printf("==================================\n");
        printf("1. Create Account\n");
        printf("2. User Login\n");
        printf("3. Admin Panel\n");
        printf("0. Exit Application\n");
        printf("Choice: ");
        choice = getIntInput();

        switch (choice) {
            case 1:
                createAccount();
                pauseScreen();
                break;
            case 2: {
                Account currentAcc;
                if (loginUser(&currentAcc)) {
                    userMenu(&currentAcc);
                } else {
                    pauseScreen();
                }
                break;
            }
            case 3:
                adminMenu();
                break;
            case 0:
                printf("Exiting... Thank you for using the system.\n");
                break;
            default:
                printf("Invalid Choice! Please try again.\n");
                pauseScreen();
        }
    } while (choice != 0);

    return 0;
}