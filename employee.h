#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct {
    int year;
    int mon;
    int day;
} Date;

typedef struct {
    int id;
    char name[31];
    char des[26];
    Date date;
    double basic;
    int probation; 
} emp;

// Function declarations
int filescan(FILE *fp, emp *employee);
void recordPrint(emp *staff);
void checkDate(emp *staff, Date *start, Date *end);
void getstring(char str[], int size);
int filePrint(FILE *fp, emp *staff);
int menu();
void fillArray(FILE *fp, emp *staff, emp array[]);
void sortID(emp array[], int count);
void sortSal(emp array[], int count);
void sortDate(emp array[], int count);
void sortAlpha(emp array[], int count);
void sortPro(emp array[], int count);
void salaryreport(emp *staff);
int idExists(FILE *fp, int id);
int probationEnd(emp *staff);
#endif

