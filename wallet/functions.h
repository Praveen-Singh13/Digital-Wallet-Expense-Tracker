#ifndef FUNCTIONS_H
#define FUNCTIONS_H

extern struct transactions TransactionList;

struct timestamp
{
    int day;
    int month;
    int year;
    int hour;
    int minute;
};
struct transaction_seconds
{
    char type[50];
    float amount;
    char category[50];
    struct timestamp t;
    char merchant[50];
};
struct transactions
{
    struct transaction_seconds *list;
    int count;
};

void addTransaction();
float calculateBalance();
void generateReport();

#endif