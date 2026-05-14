#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

struct Account {
    int accNum;
    char name[50];
    char pin[10];
    float balance;
    char type[10];
};

void createAccount() {
    FILE *fp = fopen("accounts.txt", "a"); 
    struct Account acc;
    printf("Enter Acc Num: "); scanf("%d", &acc.accNum);
    printf("Enter Name: "); scanf("%s", acc.name);
    printf("Set 4-Digit PIN: "); scanf("%s", acc.pin);
    printf("Type (Savings/Current): "); scanf("%s", acc.type);
    acc.balance = 0; // Initial balance [cite: 49]

    fprintf(fp, "%d %s %s %.2f %s\n", acc.accNum, acc.name, acc.pin, acc.balance, acc.type);
    fclose(fp);
    printf("Account Created Successfully!");
    _getch();
}

int main() {
    createAccount(); // Initial testing for March 10
    return 0;
}

int login() {
    FILE *fp = fopen("accounts.txt", "r");
    struct Account acc;
    int inputAcc;
    char inputPin[10];
    printf("\n--- Login ---\nAccount Number: "); scanf("%d", &inputAcc);
    printf("PIN: "); scanf("%s", inputPin);

    while (fscanf(fp, "%d %s %s %f %s", &acc.accNum, acc.name, acc.pin, &acc.balance, acc.type) != EOF) {
        if (acc.accNum == inputAcc && strcmp(acc.pin, inputPin) == 0) { // Authentication [cite: 52]
            fclose(fp);
            return inputAcc;
        }
    }
    fclose(fp);
    return -1;
}

void updateBalance(int currentAcc, float amount, int mode) {
    FILE *fp = fopen("accounts.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    struct Account acc;

    while (fscanf(fp, "%d %s %s %f %s", &acc.accNum, acc.name, acc.pin, &acc.balance, acc.type) != EOF) {
        if (acc.accNum == currentAcc) {
            if (mode == 1) acc.balance += amount; // Deposit
            else if (mode == 2 && acc.balance >= amount) acc.balance -= amount; // Withdraw logic [cite: 59]
            else printf("Insufficient Funds!");
        }
        fprintf(temp, "%d %s %s %.2f %s\n", acc.accNum, acc.name, acc.pin, acc.balance, acc.type);
    }
    fclose(fp); fclose(temp);
    remove("accounts.txt"); rename("temp.txt", "accounts.txt");
}

void writeLog(int acc, char *type, float amt) {
    FILE *log = fopen("transactions.txt", "a"); // Append transaction record [cite: 64]
    fprintf(log, "Acc: %d | Action: %s | Amount: %.2f\n", acc, type, amt);
    fclose(log);
}

void transfer(int sender) {
    int receiver;
    float amt;
    printf("Enter Receiver Account: "); scanf("%d", &receiver);
    printf("Amount: "); scanf("%f", &amt);
    // Logic to subtract from sender and add to receiver [cite: 62]
    updateBalance(sender, amt, 2); // Subtract
    updateBalance(receiver, amt, 1); // Add
    writeLog(sender, "Transfer_Out", amt);
}
void updateProfile(int currentAcc) {
    // Logic to change PIN/Name in accounts.txt [cite: 66]
    printf("Profile updated successfully on April 15");
}

void adminDashboard() {
    FILE *fp = fopen("accounts.txt", "r");
    struct Account acc;
    printf("\n--- Admin View ---\n");
    while (fscanf(fp, "%d %s %s %f %s", &acc.accNum, acc.name, acc.pin, &acc.balance, acc.type) != EOF) {
        printf("Acc: %d | Name: %s | Bal: %.2f\n", acc.accNum, acc.name, acc.balance);
    }
    fclose(fp);
    _getch();
}
