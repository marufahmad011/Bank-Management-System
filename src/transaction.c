#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/transaction.h"
#include "../include/utils.h"

void saveTransaction(int accNo, const char *type, double amount) {
    FILE *fp = fopen("data/transactions.txt", "a");
    if (fp) {
        char timeBuf[50];
        getCurrentTime(timeBuf);
        fprintf(fp, "%d|%s|%.2f|%s\n", accNo, type, amount, timeBuf);
        fclose(fp);
    }
}

void deposit(Account *acc) {
    double amount;
    printf("\n--- Deposit ---\n");
    printf("Enter amount to deposit: ");
    amount = getDoubleInput();

    if (amount <= 0) {
        printf("Invalid amount!\n");
        return;
    }

    acc->balance += amount;
    updateAccountInFile(*acc);
    saveTransaction(acc->accNo, "Deposit", amount);
    printf("Deposit Successful! New Balance: %.2f\n", acc->balance);
}

void withdraw(Account *acc) {
    double amount;
    printf("\n--- Withdraw ---\n");
    printf("Enter amount to withdraw: ");
    amount = getDoubleInput();

    if (amount <= 0) {
        printf("Invalid amount!\n");
        return;
    }

    if (acc->balance < amount) {
        printf("Insufficient balance!\n");
        return;
    }

    acc->balance -= amount;
    updateAccountInFile(*acc);
    saveTransaction(acc->accNo, "Withdrawal", amount);
    printf("Withdrawal Successful! New Balance: %.2f\n", acc->balance);
}

void transfer(Account *acc) {
    int targetAccNo;
    double amount;
    
    printf("\n--- Fund Transfer ---\n");
    printf("Enter Receiver Account Number: ");
    targetAccNo = getIntInput();

    if (targetAccNo == acc->accNo) {
        printf("Cannot transfer to your own account!\n");
        return;
    }

    if (!isAccountExists(targetAccNo)) {
        printf("Receiver Account not found!\n");
        return;
    }

    printf("Enter Amount to Transfer: ");
    amount = getDoubleInput();

    if (amount <= 0 || acc->balance < amount) {
        printf("Invalid amount or insufficient balance!\n");
        return;
    }

    // Process sender
    acc->balance -= amount;
    updateAccountInFile(*acc);
    saveTransaction(acc->accNo, "Transfer_Out", amount);

    // Process receiver
    FILE *fp = fopen("data/accounts.txt", "r");
    Account targetAcc;
    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        if (sscanf(line, "%d|%[^|]|%d|%lf", &targetAcc.accNo, targetAcc.name, &targetAcc.pin, &targetAcc.balance) == 4) {
            if (targetAcc.accNo == targetAccNo) break;
        }
    }
    fclose(fp);

    targetAcc.balance += amount;
    updateAccountInFile(targetAcc);
    saveTransaction(targetAcc.accNo, "Transfer_In", amount);

    printf("Transfer Successful!\n");
}

void miniStatement(int accNo) {
    printf("\n--- Mini Statement (Last 5 Transactions) ---\n");
    FILE *fp = fopen("data/transactions.txt", "r");
    if (!fp) {
        printf("No transactions found.\n");
        return;
    }

    char lines[100][256];
    int count = 0;
    char line[256];
    
    // Read all transactions
    while (fgets(line, sizeof(line), fp)) {
        int tAcc;
        sscanf(line, "%d|", &tAcc);
        if (tAcc == accNo) {
            strcpy(lines[count++], line);
        }
    }
    fclose(fp);

    if (count == 0) {
        printf("No transactions yet.\n");
        return;
    }

    // Print last 5
    int start = (count > 5) ? count - 5 : 0;
    printf("%-15s | %-12s | %-10s\n", "Type", "Amount", "Date/Time");
    printf("-------------------------------------------------\n");
    for (int i = start; i < count; i++) {
        int tAcc;
        char type[20], timeStr[50];
        double amt;
        sscanf(lines[i], "%d|%[^|]|%lf|%[^\n]", &tAcc, type, &amt, timeStr);
        printf("%-15s | %-12.2f | %-10s\n", type, amt, timeStr);
    }
}