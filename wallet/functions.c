
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
struct transaction_details newTransaction;
static float balance = 0.0;



void clearBuffer()
{
    while(getchar() != '\n');
}
void saveToFile() {
    FILE *fp = fopen("transactions.txt", "w");
    if (!fp) {
        printf("Error opening file for writing!\n");
        return;
    }

    for (int i = 0; i < transactionCount; i++) {
        fprintf(fp, "%s %.2f %s %d %d %d %d %d %s\n",
                list[i].type,
                list[i].amount,
                list[i].category,
                list[i].t.day,
                list[i].t.month,
                list[i].t.year,
                list[i].t.hour,
                list[i].t.minute,
                list[i].merchant);
    }

    fclose(fp);
}

void loadFromFile() {
    FILE *fp = fopen("transactions.txt", "r");
    if (!fp) {
        return; // No file yet
    }

    while (!feof(fp)) {
        struct transaction_details temp;

        if (fscanf(fp, "%s %f %s %d %d %d %d %d %s",
                   temp.type,
                   &temp.amount,
                   temp.category,
                   &temp.t.day,
                   &temp.t.month,
                   &temp.t.year,
                   &temp.t.hour,
                   &temp.t.minute,
                   temp.merchant) == 9)
        {
            list = realloc(list, sizeof(struct transaction_details) * (transactionCount + 1));
            list[transactionCount] = temp;
            transactionCount++;
        }
    }

    fclose(fp);
}


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
    
    
    list = realloc(list, sizeof(struct transaction_details) * (transactionCount + 1));
    list[transactionCount] = newTransaction;
    transactionCount++;
    saveToFile();
    printf("Transaction added successfully!\n");
}

void calculateBalance()
{
    //calculate and display balance

    
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

    void viewTransactions()
    {
    printf("Transactions:\n");

    for(int i = 0; i < transactionCount; i++)
    {
        printf("Type: %s, Amount: %.2f, Category: %s, Date: %02d/%02d/%04d, Time: %02d:%02d, Merchant: %s\n",
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
    printf("Enter month and year for the report (MM YYYY):\n");
    scanf("%d %d", &month, &year);

    float totalIncome = 0.0;
    float totalExpense = 0.0;
    printf("Transactions for %02d/%04d:\n", month, year);
    for(int i = 0; i < transactionCount; i++)
    {
        if(list[i].t.month == month && list[i].t.year == year)
        {
            printf("Type: %s, Amount: %.2f, Category: %s, Date: %02d/%02d/%04d, Time: %02d:%02d, Merchant: %s\n",
                   list[i].type, list[i].amount, list[i].category,
                   list[i].t.day, list[i].t.month, list[i].t.year,
                   list[i].t.hour, list[i].t.minute,
                   list[i].merchant);
            if(strcmp(list[i].type, "income") == 0)
            {
                totalIncome += list[i].amount;
            }
            else if(strcmp(list[i].type, "expense") == 0)
            {
                totalExpense += list[i].amount;
            }
        }
    }
    printf("Total Income: %.2f\n", totalIncome);
    printf("Total Expense: %.2f\n", totalExpense);
    printf("Net Savings: %.2f\n", totalIncome - totalExpense);
    
    //alert if expenses exceed 75% of income
    if(totalExpense > (0.75 * totalIncome))
    {
        printf("Alert: Your expenses exceeded your income this month!\n");
    }
    
}
