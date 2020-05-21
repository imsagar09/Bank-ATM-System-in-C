#include<stdio.h>
#include<stdlib.h>

#define PIN 1234
#define MAX_ATTEMPTS 3

// Global variable
int balance = 1500;

// Function prototypes
void showBalance();
void depositMoney();
void withdrawMoney();

int main(void) {
    unsigned int pin; // PIN cannot be a negative number
    int attemptCount = 0, choice, pinValid = 0;

    printf("\n______ Welcome to ATM ______\n\n");

    while(attemptCount < MAX_ATTEMPTS) {
        printf("\nEnter PIN: ");
        scanf("%d", &pin);

        /*
          Check if pin number entered by user is valid or not
        */
        if (pin != PIN) {
            attemptCount++;
            printf("Invalid PIN. (%d attempts left)\n", (MAX_ATTEMPTS-attemptCount));

            /*
              If user has not entered the valid PIN even in the last attempt,
              then exit ATM system
            */
            if (attemptCount == MAX_ATTEMPTS) {
                printf("\nSystem locked\n");
                exit(EXIT_FAILURE); // exits program
            }
        } else {
            printf("\nValid PIN\n");
            pinValid = 1;
            break;
        }
    }

    // On valid PIN entry by user, the ATM Menu is presented to the user
    while(pinValid) {
        printf("\nATM System Menu\n===============\n\n");
        printf("1. Check Balance\n2. Deposit\n3. Withdraw\n4. Quit\n\n");

        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: showBalance();
                    break;
            case 2: depositMoney();
                    break;
            case 3: withdrawMoney();
                    break;
            case 4: printf("\nThank you for using the ATM\n");
                    exit(EXIT_SUCCESS);
            default: printf("\nInvalid option entered!\n");
                     break;
        }
    }

    return 0;
}

void showBalance() {
    printf("\nshowBalance() :: function definition yet to be implemented.\n");
}

void depositMoney() {
    printf("\ndepositMoney() :: function definition yet to be implemented.\n");
}

void withdrawMoney() {
    printf("\nwithdrawMoney() :: function definition yet to be implemented.\n");
}
