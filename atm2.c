#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

// node structure for implementing a queue
typedef struct node {
    char stmt[50];
    struct node* link;
} node;

node *head = NULL;

int balance = 0;

// Bank function prototypes
void pinGeneration(void);

// ATM function prototypes
int checkPin(void);
void showBalance(void);
void depositMoney(void);
void withdrawMoney(void);
void saveHistory(char *);
void removeHistory(void);
void showHistory(void);

int main(void) {
    int choice1, choice2, choice3;
    int pinValid = 0;

    while (1) {
        printf("\n\nATM System\n======================\n");
        printf("1. Generate PIN\n2. Use ATM\n3. Exit\n");
        printf("\nYour choice: ");
        scanf("%d", &choice1);

        switch (choice1) {
            case 1: while (1) {
                        printf("\n\nGenerate PIN\n============\n");
                        printf("\n1. Generate PIN\n2. Exit\n");
                        printf("\nEnter choice: ");
                        scanf("%d", &choice2);

                        switch (choice2) {
                            case 1: pinGeneration();
                                    break;
                            case 2: printf("\nPIN generated successfully\n");
                                    exit(EXIT_SUCCESS);
                                    break;
                            default: printf("\nInvalid choice...Try again...\n");
                                     break;
                        }
                    }

            case 2: pinValid = checkPin();

                    if (pinValid) {
                        printf("\nValid PIN\n");
                    } else {
                        printf("\nInvalid PIN.Please generate a PIN if you don't have one.\n");
                        exit(EXIT_FAILURE);
                    }

                    // On valid PIN entry by user, the ATM Menu is presented to the user
                    while(pinValid) {
                        printf("\nATM System Menu\n===============\n\n");
                        printf("1. Check Balance\n2. Deposit\n3. Withdraw\n4. View transaction history\n5. Quit\n\n");

                        printf("Enter choice: ");
                        scanf("%d", &choice3);

                        switch(choice3) {
                            case 1: showBalance();
                                    break;
                            case 2: depositMoney();
                                    break;
                            case 3: withdrawMoney();
                                    break;
                            case 4: showHistory();
                                    break;
                            case 5: printf("\nThank you for using the ATM\n");
                                    exit(EXIT_SUCCESS);
                            default: printf("\nInvalid option entered!\n");
                                     break;
                        }
                    }

            case 3: exit(EXIT_SUCCESS);
                    break;

            default: printf("\nInvalid choice...Try again...\n");
                     break;
        }
    }
    return 0;
}

int checkPin(void) {
    FILE *fp;
    char pin[8];
    char keyPin[8] = "";
    int pinValid = 0;

    printf("\n\nEnter the PIN: \n");
    scanf("%s", keyPin);

    fp = fopen("pin.txt", "r");
    if (NULL == fp) {
        printf("\nFile cannot be opened\n");
        exit(EXIT_FAILURE);
    }

    while (fgets(pin, sizeof(pin), fp) != NULL) {
        if (strstr(pin, keyPin)) {
            pinValid = 1;
        }
    }
    fclose(fp);

    return pinValid;
}

void pinGeneration() {
    FILE *fp;

    // Generate a random 4 digit number
    srand(time(NULL));
    int generatedPin = 1000+rand()%9000;

    printf("\nYour generated PIN: %d\n", generatedPin);

    fp = fopen("pin.txt", "a");
    if (NULL == fp) {
        printf("\nCannot open file!");
        exit(EXIT_FAILURE);
    }

    fprintf(fp, "%d\n", generatedPin);
    fclose(fp);

    return;
}

void showBalance(void) {
    printf("\nYour current balance is Rs.%d\n", balance);
    return;
}

void depositMoney(void) {
    int depositAmount;
    char depositStmt[50] = ""; // initialize string when declared

    printf("\nEnter amount to deposit: ");
    scanf("%d", &depositAmount);

    if (depositAmount > 0) {
        balance += depositAmount;
        printf("\nRs.%d deposited\n", depositAmount);

        snprintf(depositStmt, sizeof(depositStmt), "Rs.%d deposited\n", depositAmount);
        saveHistory(depositStmt);
    } else {
        printf("\nInvalid amount entered\n.");
    }
    return;
}

void withdrawMoney() {
    int withdrawAmount;
    char withdrawStmt[50] = "";

    printf("\nEnter amount to withdraw: ");
    scanf("%d", &withdrawAmount);

    if (withdrawAmount > 0) {
        if (withdrawAmount > balance) {
            printf("\nCannot withdraw. Balance Rs.%d\n", balance);
        } else {
            balance -= withdrawAmount;
            printf("\nRs.%d withdrawn\n", withdrawAmount);

            // saving formatted string in withdrawStmt character array
            snprintf(withdrawStmt, sizeof(withdrawStmt), "Rs.%d withdrawn\n", withdrawAmount);
            saveHistory(withdrawStmt);

        }
    } else {
        printf("\nInvalid amount entered\n.");
    }
    return;
}

void saveHistory(char *str) {
    static int count = 0;
    node *temp;
    temp = (node *)malloc(sizeof(node));

    strcpy(temp->stmt, str);
    temp->link = NULL;

    if (NULL == head) {
        head = temp;
        count++;
    } else {
        if (10 == count) {
            removeHistory();
            count--;
        }
        node *p;
        p = head;
        while (NULL != p->link) {
            p = p->link;
        }
        p->link = temp;
        count++;
    }
    return;
}

void removeHistory() {
    node *temp;
    temp = head;
    head = head->link;
    temp->link = NULL;
    free(temp);
    return;
}

void showHistory() {
    node *temp;
    temp = head;

    if (temp == NULL) {
        printf("\nNo transaction history...\n");
    } else {
        printf("\nTransaction History\n-------------------\n\n");
        while (temp != NULL) {
            printf("%s\n", temp->stmt);
            temp = temp->link;
        }
    }
    return;
}
