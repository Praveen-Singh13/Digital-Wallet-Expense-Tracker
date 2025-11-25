
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


void addTransaction()
{
    struct transaction_details newTransaction;
    printf("Enter transaction type (income/expense): ");
    strcnpy(newTransaction.type, 50, stdin);
    printf("Enter amount: ");
    scanf("%f", &newTransaction.amount);
    printf("Enter category: ");
    strcnpy(newTransaction.category, 50, stdin);
    printf("Enter date (DD MM YYYY): ");
    scanf("%d %d %d", &newTransaction.t.day, &newTransaction.t.month, &newTransaction.t.year);
    printf("Enter time (HH MM): ");
    scanf("%d %d", &newTransaction.t.hour, &newTransaction.t.minute);
    printf("Enter merchant: ");
    strcnpy(newTransaction.merchant, 50, stdin);
    //store the newTransaction in the TransactionList
    
    static int transactionCount = 0;
    list = realloc(list, sizeof(struct transaction_details) * (transactionCount + 1));
    list[transactionCount] = newTransaction;
    transactionCount++;
    printf("Transaction added successfully!\n");
}

void calculateBalance()
{
    //calculate and return the balance
    float balance = 0.0;
    for(int i = 0; i < sizeof(list)/sizeof(list[0]); i++)
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
    for(int i = 0; i < sizeof(list)/sizeof(list[0]); i++)
    {
        printf("Type: %s, Amount: %.2f, Category: %s, Date: %02d/%02d/%04d, Time: %02d:%02d, Merchant: %s\n",
               list[i].type, list[i].amount, list[i].category,
               list[i].t.day, list[i].t.month, list[i].t.year,
               list[i].t.hour, list[i].t.minute,
               list[i].merchant);
    }
}