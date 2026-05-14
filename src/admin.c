#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/admin.h"
#include "../include/utils.h"

void viewAllAccounts() {
    FILE *fp = fopen("data/accounts.txt", "r");
    if (!fp) {
        printf("No accounts found.\n");
        return;
    }

    printf("\n--- All Registered Accounts ---\n");
    printf("%-10s | %-25s | %-12s\n", "Acc No", "Name", "Balance");
    printf("-----------------------------------------------------\n");

    char line[256];
    int accNo, pin;
    char name[50];
    double balance;

    while (fgets(line, sizeof(line), fp)) {
        if (sscanf(line, "%d|%[^|]|%d|%lf", &accNo, name, &pin, &balance) == 4) {
            printf("%-10d | %-25s | %.2f\n", accNo, name, balance);
        }
    }
    fclose(fp);
}

void searchAccount() {
    int searchAcc;
    printf("\nEnter Account Number to Search: ");
    searchAcc = getIntInput();

    FILE *fp = fopen("data/accounts.txt", "r");
    if (!fp) return;

    char line[256];
    int accNo, pin;
    char name[50];
    double balance;
    int found = 0;

    while (fgets(line, sizeof(line), fp)) {
        if (sscanf(line, "%d|%[^|]|%d|%lf", &accNo, name, &pin, &balance) == 4) {
            if (accNo == searchAcc) {
                printf("\n--- Account Found ---\n");
                printf("Account No: %d\nName: %s\nBalance: %.2f\n", accNo, name, balance);
                found = 1;
                break;
            }
        }
    }
    fclose(fp);
    if (!found) printf("Account not found.\n");
}

void deleteAccount() {
    int delAcc;
    printf("\nEnter Account Number to Delete: ");
    delAcc = getIntInput();

    printf("Delete Account? (Y/N): ");
    char confirm[10];
    getStringInput(confirm, sizeof(confirm));
    
    if (confirm[0] != 'Y' && confirm[0] != 'y') {
        printf("Deletion cancelled.\n");
        return;
    }

    FILE *fp = fopen("data/accounts.txt", "r");
    FILE *temp = fopen("data/temp.txt", "w");
    if (!fp || !temp) return;

    char line[256];
    int accNo, pin;
    char name[50];
    double balance;
    int deleted = 0;

    while (fgets(line, sizeof(line), fp)) {
        if (sscanf(line, "%d|%[^|]|%d|%lf", &accNo, name, &pin, &balance) == 4) {
            if (accNo == delAcc) {
                deleted = 1;
            } else {
                fprintf(temp, "%s", line);
            }
        }
    }
    fclose(fp);
    fclose(temp);
    remove("data/accounts.txt");
    rename("data/temp.txt", "data/accounts.txt");

    if (deleted) {
        printf("Account successfully deleted.\n");
        char logMsg[100];
        sprintf(logMsg, "Admin Deleted Account: %d", delAcc);
        logAction(logMsg);
    } else {
        printf("Account not found.\n");
    }
}

void viewLogs() {
    FILE *fp = fopen("data/logs.txt", "r");
    if (!fp) {
        printf("No logs found.\n");
        return;
    }
    printf("\n--- System Logs ---\n");
    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }
    fclose(fp);
}

void adminMenu() {
    printf("\n--- Admin Login ---\n");
    printf("Enter Admin Password: ");
    char pass[50];
    getStringInput(pass, sizeof(pass));
    
    if (strcmp(pass, "admin123") != 0) { // Hardcoded for project simplicity
        printf("Access Denied!\n");
        return;
    }

    int choice;
    do {
        clearScreen();
        printf("\n=== ADMIN PANEL ===\n");
        printf("1. View All Accounts\n");
        printf("2. Search Account\n");
        printf("3. Delete Account\n");
        printf("4. View System Logs\n");
        printf("0. Logout\n");
        printf("Choice: ");
        choice = getIntInput();

        switch (choice) {
            case 1: viewAllAccounts(); pauseScreen(); break;
            case 2: searchAccount(); pauseScreen(); break;
            case 3: deleteAccount(); pauseScreen(); break;
            case 4: viewLogs(); pauseScreen(); break;
            case 0: printf("Admin Logged Out.\n"); break;
            default: printf("Invalid Choice!\n"); pauseScreen();
        }
    } while (choice != 0);
}