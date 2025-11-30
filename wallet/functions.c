
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
struct transaction_details *list = NULL; // Dynamic array to hold transactions

static int Count = 0; //no. of transactions

struct transaction_details newTransaction;//to hold new transaction

static float balance = 0.0;

//-------------------Fuctions---------------------------------//

void clearBuffer()
{
    while(getchar() != '\n');
}

//-------------------File handling functions-------------------//

void saveToFile() {
    FILE *fp = fopen("transactions.txt","w");
    if (!fp) {
        printf("File not opened!!\n");
        return;
    }
    for (int i = 0; i <Count; i++) {
        fprintf(fp, "%s %.2f %s %d %d %d %d %d %s\n",list[i].type,list[i].amount,list[i].category,list[i].t.day,list[i].t.month, list[i].t.year,list[i].t.hour,list[i].t.minute,list[i].merchant);
    }
    fclose(fp);
}


void loadFromFile() {
    FILE *fp = fopen("transactions.txt","r");
    if (!fp) {
        return; // No file yet
    }
    while (!feof(fp)) {
        struct transaction_details temp;
        if (fscanf(fp,"%s %f %s %d %d %d %d %d %s",temp.type, &temp.amount, temp.category, &temp.t.day,&temp.t.month, &temp.t.year, &temp.t.hour, &temp.t.minute,temp.merchant)==9)
        {
            list = realloc(list, sizeof(struct transaction_details) * (Count + 1));
            list[Count] = temp;
            Count++;
        }
    }

    fclose(fp);
}

//-------------------Required functions-------------------//

int addTransaction()
{

    printf("Enter transaction type (income/expense):\n");
    
    fgets(newTransaction.type, 50, stdin);

    newTransaction.type[strcspn(newTransaction.type, "\n")] = 0;

    printf("Enter amount:\n ");

    scanf("%f", &newTransaction.amount);

     if(newTransaction.amount>balance&&strcmp(newTransaction.type, "expense") == 0)
    {
        printf("Warning: Insufficient balance for this expense.\n");

        printf("Transaction not Valid.\n");
        return 0;
    }

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
     list = realloc(list, sizeof(struct transaction_details) * (Count + 1));
     list[Count] = newTransaction;
     Count++;
     saveToFile();
     printf("Transaction completed!!\n");
}

void calculateBalance()
{
    //calculate and display balance
    for(int i = 0; i < Count; i++)
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

void viewTransactions()
{
    printf("Transactions:\n");

    for(int i = 0; i < Count; i++)
    {
        printf("Type: %s, Amount: %.2f, Category: %s, Date: %d/%d/%d, Time: %d:%d, Merchant: %s\n",
            list[i].type, list[i].amount, list[i].category,
            list[i].t.day, list[i].t.month, list[i].t.year,
            list[i].t.hour, list[i].t.minute,
            list[i].merchant);
    }
   
}

void generateReport()
{
    //generate monthly reports
    int month, year;
    printf("Enter month and year for the montly report(MM YYYY):\n");
    scanf("%d%d", &month, &year);

    float total_income = 0.0;
    float total_expense = 0.0;
    printf("Transactions for %d %d:\n",month,year);
    for(int i = 0; i < Count; i++)
    {
        if(list[i].t.month == month && list[i].t.year == year)
        {
            printf("Type: %s, Amount: %.2f, Category: %s, Date: %02d/%02d/%04d, Time: %02d:%02d, Merchant: %s\n",
                list[i].type, list[i].amount, list[i].category,
                list[i].t.day, list[i].t.month, list[i].t.year,
                list[i].t.hour, list[i].t.minute,
                list[i].merchant);
            if(strcmp(list[i].type,"income")== 0)
            {
                total_income += list[i].amount;
            }
            else if(strcmp(list[i].type,"expense")== 0)
            {
                total_expense += list[i].amount;
            }
        }
    }
    printf("Monthly Income: %.2f\n", total_income);
    printf("Monthly Expenses: %.2f\n", total_expense);
    printf("Monthly Savings: %.2f\n", total_income - total_expense);
    
    //alert if expenses exceed 75% of income
    if(total_expense > (0.75 * total_income))
    {
        printf("Alert!\n Your monthly limit has been reached!!\n");
    }
    
}
