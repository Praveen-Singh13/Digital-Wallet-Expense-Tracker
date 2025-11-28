
#include <stdio.h>
#include "functions.h"
#include <stdlib.h>
#include <string.h>

struct timestamp
{
    int day;
    int month;
    int year;
    int hour;
    int minute;
};
struct transaction_details
{
    char type[50];
    float amount;
    char category[50];
    struct timestamp t;
    char merchant[50];
};
struct transaction_details *list = NULL;
static int transactionCount = 0;



void clearBuffer()
{
    while(getchar() != '\n');
}


void addTransaction()
{
    struct transaction_details newTransaction;
    printf("Enter transaction type (income/expense):\n");
    
    fgets(newTransaction.type, 50, stdin);
    newTransaction.type[strcspn(newTransaction.type, "\n")] = 0;

    printf("Enter amount:\n ");
    scanf("%f", &newTransaction.amount);
    clearBuffer();
    printf("Enter category:\n ");
    fgets(newTransaction.category, 50, stdin);
    newTransaction.category[strcspn(newTransaction.category, "\n")] = 0;
    
    printf("Enter date (DD MM YYYY):\n"); 
    
    scanf("%d %d %d", &newTransaction.t.day, &newTransaction.t.month, &newTransaction.t.year);
    
    printf("Enter time (HH MM):\n");
    
    scanf("%d %d", &newTransaction.t.hour, &newTransaction.t.minute);
    clearBuffer();
    printf("Enter merchant:\n");
    fgets(newTransaction.merchant, 50, stdin);
    
    //store the newTransaction in the TransactionList
    
    
    list = realloc(list, sizeof(struct transaction_details) * (transactionCount + 1));
    list[transactionCount] = newTransaction;
    transactionCount++;
    printf("Transaction added successfully!\n");
}

void calculateBalance()
{
    //calculate and return the balance
    float balance = 0.0;
    for(int i = 0; i < transactionCount; i++)
    {
        if(strcmp(list[i].type, "income") == 0)
        {
            balance += list[i].amount;
        }
        else if(strcmp(list[i].type, "expense") == 0)
        {
            balance -= list[i].amount;
        }
    }
    printf("Current Balance: %.2f\n", balance);



}
void generateReport()
{
    //generate and print the report of transactions
    printf("Transaction Report:\n");
    for(int i = 0; i < transactionCount; i++)
    {
        printf("Type: %s, Amount: %.2f, Category: %s, Date: %02d/%02d/%04d, Time: %02d:%02d, Merchant: %s\n",
               list[i].type, list[i].amount, list[i].category,
               list[i].t.day, list[i].t.month, list[i].t.year,
               list[i].t.hour, list[i].t.minute,
               list[i].merchant);
    }
    //monthly analysis can be added here
    
}