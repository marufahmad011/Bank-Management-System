#include <stdio.h>

int main() {

    int choice;

    while(1) {

        printf("\n===== BANK MANAGEMENT SYSTEM =====\n");

        printf("1. Create Account\n");
        printf("2. Login\n");
        printf("3. Exit\n");

        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch(choice) {

            case 1:
                printf("Create Account Selected\n");
                break;

            case 2:
                printf("Login Selected\n");
                break;

            case 3:
                printf("Thank You\n");
                return 0;

            default:
                printf("Invalid Choice\n");
        }
    }

    return 0;
}