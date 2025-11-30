#include<stdio.h>
#include <stdlib.h>
#include "functions.h"

int main()
{
    loadFromFile();

    int choice;
    while(1)
    {
        printf("\nDigital Wallet and Expense Tracker\n");
    
        printf("1. Add Transaction\n");
        
        printf("2. Update and View Balance\n");

        printf("3. View Transactions\n");
        
       
        
        printf("4. Generate Monthly Report\n");

        printf("5. Exit\n");
    
        printf("Enter your choice: ");

        scanf("%d", &choice);
        clearBuffer();
        switch(choice)
        {
            case 1:
                addTransaction();
                break;
            case 2:
                calculateBalance();
                break;
            case 3:
                generateReport();
                break;
            case 4:
                printf("We are exiting the program.\n");
                return 0;
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
