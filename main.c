#include <stdio.h>

int main() {

    int choice;

    while(1) {

        printf("\n==============================");
        printf("\n BANK MANAGEMENT SYSTEM");
        printf("\n==============================");

        printf("\n1. Create Account");
        printf("\n2. Login");
        printf("\n3. Exit");

        printf("\n\nEnter Choice: ");
        scanf("%d", &choice);

        switch(choice) {

            case 1:
                printf("\nCreate Account Feature Coming Soon...\n");
                break;

            case 2:
                printf("\nLogin Feature Coming Soon...\n");
                break;

            case 3:
                printf("\nThank You!\n");
                return 0;

            default:
                printf("\nInvalid Choice!\n");
        }
    }

    return 0;
}