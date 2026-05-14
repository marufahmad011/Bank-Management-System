#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for Account Data [cite: 78]
struct Account {
    int accNum;
    char name[50];
    float balance;
    char pin[10];
};

// Function Prototypes [cite: 80]
void menu();
void createAccount();
void deposit();
void withdraw();

int main() {
    menu();
    return 0;
}

void menu() {
    int choice;
    while (1) {
        printf("\n--- BANK MANAGEMENT SYSTEM ---");
        printf("\n1. Create Account\n2. Deposit\n3. Withdraw\n4. Exit\nChoice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createAccount(); break;
            case 2: deposit(); break;
            case 3: withdraw(); break;
            case 4: exit(0);
            default: printf("Invalid choice!");
        }
    }
}

// Feature: Account Creation [cite: 48]
void createAccount() {
    FILE *fp = fopen("accounts.txt", "a"); // File Handling [cite: 35]
    struct Account acc;

    printf("Enter Account Number: ");
    scanf("%d", &acc.accNum);
    printf("Enter Name: ");
    scanf("%s", acc.name);
    printf("Enter PIN: ");
    scanf("%s", acc.pin);
    acc.balance = 0; // Initial balance [cite: 49]

    fprintf(fp, "%d %s %s %.2f\n", acc.accNum, acc.name, acc.pin, acc.balance);
    fclose(fp);
    printf("Account Created Successfully!");
}

// Feature: Cash Deposit [cite: 55]
void deposit() {
    FILE *fp = fopen("accounts.txt", "r");
    FILE *temp = fopen("temp.txt", "w"); // Use temp file to update [cite: 66]
    struct Account acc;
    int targetAcc;
    float amount;
    int found = 0;

    printf("Enter Account Number: ");
    scanf("%d", &targetAcc);
    printf("Enter Amount to Deposit: ");
    scanf("%f", &amount);

    while (fscanf(fp, "%d %s %s %f", &acc.accNum, acc.name, acc.pin, &acc.balance) != EOF) {
        if (acc.accNum == targetAcc) {
            acc.balance += amount; // Logic for deposit [cite: 56]
            found = 1;
        }
        fprintf(temp, "%d %s %s %.2f\n", acc.accNum, acc.name, acc.pin, acc.balance);
    }

    fclose(fp);
    fclose(temp);
    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (found) printf("Deposit Successful!");
    else printf("Account Not Found.");
}

// Feature: Cash Withdrawal [cite: 58]
void withdraw() {
    FILE *fp = fopen("accounts.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    struct Account acc;
    int targetAcc;
    float amount;
    int found = 0;

    printf("Enter Account Number: ");
    scanf("%d", &targetAcc);
    printf("Enter Amount to Withdraw: ");
    scanf("%f", &amount);

    while (fscanf(fp, "%d %s %s %f", &acc.accNum, acc.name, acc.pin, &acc.balance) != EOF) {
        if (acc.accNum == targetAcc) {
            if (acc.balance >= amount) { // Logic: Check enough money [cite: 59]
                acc.balance -= amount;
                found = 1;
            } else {
                printf("Insufficient Balance!");
            }
        }
        fprintf(temp, "%d %s %s %.2f\n", acc.accNum, acc.name, acc.pin, acc.balance);
    }

    fclose(fp);
    fclose(temp);
    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (found) printf("Withdrawal Successful!");
}