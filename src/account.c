#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/account.h"
#include "../include/utils.h"

// Check if an account number already exists in the database
int isAccountExists(int accNo) {
    FILE *fp = fopen("data/accounts.txt", "r");
    if (!fp) return 0;

    char line[256];
    Account temp;
    while (fgets(line, sizeof(line), fp)) {
        if (sscanf(line, "%d|%[^|]|%d|%lf", &temp.accNo, temp.name, &temp.pin, &temp.balance) == 4) {
            if (temp.accNo == accNo) {
                fclose(fp);
                return 1;
            }
        }
    }
    fclose(fp);
    return 0;
}

// Create a new bank account
void createAccount() {
    Account newAcc;
    printf("\n--- Create New Account ---\n");
    
    printf("Enter Account Number: ");
    newAcc.accNo = getIntInput();

    // Prevent duplicate accounts
    if (isAccountExists(newAcc.accNo)) {
        printf("Error: This Account Number Already Taken!\n");
        return;
    }

    printf("Enter Full Name: ");
    getStringInput(newAcc.name, sizeof(newAcc.name));

    // PIN Validation loop
    do {
        printf("Enter 4-digit PIN: ");
        newAcc.pin = getIntInput();
        if (newAcc.pin < 1000 || newAcc.pin > 9999) {
            printf("Invalid! PIN must be exactly 4 digits.\n");
        }
    } while (newAcc.pin < 1000 || newAcc.pin > 9999);

    // Initial Deposit Validation loop
    do {
        printf("Enter Initial Deposit Amount: ");
        newAcc.balance = getDoubleInput();
        if (newAcc.balance <= 0) {
            printf("Amount must be greater than 0.\n");
        }
    } while (newAcc.balance <= 0);

    // Save to file
    FILE *fp = fopen("data/accounts.txt", "a");
    if (fp) {
        fprintf(fp, "%d|%s|%d|%.2f\n", newAcc.accNo, newAcc.name, newAcc.pin, newAcc.balance);
        fclose(fp);
        printf("\nAccount Created Successfully!\n");
        
        char logMsg[100];
        sprintf(logMsg, "New Account Created: %d", newAcc.accNo);
        logAction(logMsg);
    } else {
        printf("Error saving account data. Make sure the 'data' folder exists.\n");
    }
}

// User login authentication
int loginUser(Account *loggedInAcc) {
    int inputAcc, inputPin;
    printf("\n--- User Login ---\n");
    
    printf("Account Number (Enter 0 to cancel): ");
    inputAcc = getIntInput();
    
    // Feature: Allow user to cancel login
    if (inputAcc == 0) {
        printf("Login cancelled. Returning to menu...\n");
        return 0; 
    }

    printf("PIN: ");
    inputPin = getIntInput();

    FILE *fp = fopen("data/accounts.txt", "r");
    if (!fp) {
        printf("Database error. No accounts found.\n");
        return 0;
    }

    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        if (sscanf(line, "%d|%[^|]|%d|%lf", &loggedInAcc->accNo, loggedInAcc->name, &loggedInAcc->pin, &loggedInAcc->balance) == 4) {
            // Check if credentials match
            if (loggedInAcc->accNo == inputAcc && loggedInAcc->pin == inputPin) {
                fclose(fp);
                char logMsg[100];
                sprintf(logMsg, "Successful Login: %d", inputAcc);
                logAction(logMsg);
                return 1;
            }
        }
    }
    fclose(fp);
    printf("Invalid Account Number or PIN!\n");
    return 0;
}

// Helper function to safely update an account's details in the database
void updateAccountInFile(Account updatedAcc) {
    FILE *fp = fopen("data/accounts.txt", "r");
    FILE *temp = fopen("data/temp.txt", "w");
    if (!fp || !temp) return;

    char line[256];
    Account acc;
    while (fgets(line, sizeof(line), fp)) {
        if (sscanf(line, "%d|%[^|]|%d|%lf", &acc.accNo, acc.name, &acc.pin, &acc.balance) == 4) {
            if (acc.accNo == updatedAcc.accNo) {
                // Write the updated account details
                fprintf(temp, "%d|%s|%d|%.2f\n", updatedAcc.accNo, updatedAcc.name, updatedAcc.pin, updatedAcc.balance);
            } else {
                // Keep the old details for everyone else
                fprintf(temp, "%s", line); 
            }
        }
    }
    fclose(fp);
    fclose(temp);
    
    // Replace old file with the new temp file
    remove("data/accounts.txt");
    rename("data/temp.txt", "data/accounts.txt");
}

// Update Account Holder Name
void updateProfile(Account *acc) {
    printf("\nCurrent Name: %s\n", acc->name);
    printf("Enter New Name: ");
    getStringInput(acc->name, sizeof(acc->name));
    
    updateAccountInFile(*acc);
    printf("Profile Updated Successfully!\n");
    
    char logMsg[100];
    sprintf(logMsg, "Profile updated for Account: %d", acc->accNo);
    logAction(logMsg);
}

// Change Account PIN
void changePIN(Account *acc) {
    int oldPin, newPin;
    printf("\nEnter Old PIN: ");
    oldPin = getIntInput();
    
    if (oldPin != acc->pin) {
        printf("Incorrect Old PIN! Access Denied.\n");
        return;
    }

    do {
        printf("Enter New 4-digit PIN: ");
        newPin = getIntInput();
        if (newPin < 1000 || newPin > 9999) {
            printf("Invalid! PIN must be exactly 4 digits.\n");
        }
    } while (newPin < 1000 || newPin > 9999);

    acc->pin = newPin;
    updateAccountInFile(*acc);
    printf("PIN Changed Successfully!\n");
    
    char logMsg[100];
    sprintf(logMsg, "PIN changed for Account: %d", acc->accNo);
    logAction(logMsg);
}