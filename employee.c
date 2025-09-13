#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"employee.h"
#include"salaries.h"

int filescan(FILE *fp,emp *employee)
{
        int result=fscanf(fp,"%d %30[^\t] %25[^\t] %d-%d-%d %lf %d", &employee->id, employee->name, employee->des, &employee->date.year, &employee->date.mon, &employee->date.day, &employee->basic,&employee->probation);

        if(result!=8) return 0;

        employee->name[30] = '\0';
        employee->des[25] = '\0';
        for (int i = 29; i >= 0 && employee->name[i] == ' '; i--) employee->name[i] = '\0';
        for (int i = 24; i >= 0 && employee->des[i] == ' '; i--) employee->des[i] = '\0';

        int i = 0;
        while (employee->des[i] == ' ') i++;
        if (i > 0) memmove(employee->des, employee->des + i, strlen(employee->des + i) + 1);

        return 1;
}

void recordPrint(emp *staff)
{
        printf("%-8d%-30s%-25s%04d-%02d-%02d%15.0lf%8d\n",staff->id,staff->name,staff->des,staff->date.year,staff->date.mon,staff->date.day,staff->basic,staff->probation);
}

void checkDate(emp *staff,Date *start,Date *end)
{
        if((staff->date.year)>(start->year) && (staff->date.year)<(end->year))
        {
                recordPrint(staff);
        }
        else if((staff->date.year)>(start->year) && (staff->date.year)==(end->year))
        {
                if((staff->date.mon)<(end->mon))
                {
                        recordPrint(staff);
                }
                else if((staff->date.mon)==(end->mon))
                {
                        if((staff->date.day)<=(end->day))
                        {
                                recordPrint(staff);
                        }
                }
                else
                {
                }
        }
        else if((staff->date.year)==(start->year) && (staff->date.year)<(end->year))
        {
                if((staff->date.mon)>(start->mon))
                {
                        recordPrint(staff);
                }
                else if((staff->date.mon)==(start->mon))
                {
                        if((staff->date.day)>=(start->day))
                        {
                                recordPrint(staff);
                        }
                }
                else
                {
                }
        }
        else
        {
        }
}

void getstring(char str[], int size)
{
        fgets(str, size, stdin);
        size_t len = strlen(str);
        if (len > 0 && str[len - 1] == '\n')
        {
                str[len - 1] = '\0';
        }
        return;
}

int filePrint(FILE *fp,emp *staff)
{
        int written=fprintf(fp,"%-8d%-30s%-25s%04d-%02d-%02d%15.0lf%8d\n",staff->id,staff->name,staff->des,staff->date.year,staff->date.mon,staff->date.day,staff->basic,staff->probation);

        return written;

}

int menu()
{
        int choice;
        printf("Update\n1.Name\n2.Designation\n3.Date of Joining\n4.Salary\n5.Probation Period\nEnter choice:");
        scanf("%d",&choice);
        getc(stdin);

        return choice;
}

void fillArray(FILE *fp, emp *staff, emp array[])
{
        rewind(fp);
        int i=0;
        while(filescan(fp,staff))
        {
                array[i]=(*staff);
                i++;
        }
}

void sortID(emp array[],int count)
{
        for(int j=0;j<count;j++)
        {
                int k=j;
                while(k>0 && array[k].id<array[k-1].id)
                {
                        emp temp = array[k];
                        array[k]=array[k-1];
                        array[k-1]=temp;
                        k--;
                }
        }
}

void sortSal(emp array[],int count)
{
        for(int j=0;j<count;j++)
        {
                int k=j;
                while(k>0 && array[k].basic<array[k-1].basic)
                {
                        emp temp = array[k];
                        array[k]=array[k-1];
                        array[k-1]=temp;
                        k--;
                }
        }
}

void sortDate(emp array[],int count)
{
        for(int j=0;j<count;j++)
        {
                int k=j;
                while(k>0 && array[k].date.day<array[k-1].date.day)
                {
                        emp temp = array[k];
                        array[k]=array[k-1];
                        array[k-1]=temp;
                        k--;
                }
        }

        for(int j=0;j<count;j++)
        {
                int k=j;
                while(k>0 && array[k].date.mon<array[k-1].date.mon)
                {
                        emp temp = array[k];
                        array[k]=array[k-1];
                        array[k-1]=temp;
                        k--;
                }
        }

        for(int j=0;j<count;j++)
        {
                int k=j;
                while(k>0 && array[k].date.year<array[k-1].date.year)
                {
                        emp temp = array[k];
                        array[k]=array[k-1];
                        array[k-1]=temp;
                        k--;
                }
        }

}

void sortAlpha(emp array[], int count)
{
        for (int j = 1; j < count; j++)
        {
                int k = j;
                while (k > 0 && strcasecmp(array[k].name, array[k - 1].name) < 0)
                {
                        emp temp = array[k];
                        array[k] = array[k - 1];
                        array[k - 1] = temp;
                        k--;
                }
        }
}

void sortPro(emp array[], int count)
{
	for(int j=0;j<count;j++)
        {
                int k=j;
                while(k>0 && array[k].probation<array[k-1].probation)
                {
                        emp temp = array[k];
                        array[k]=array[k-1];
                        array[k-1]=temp;
                        k--;
                }
        }
}

void salaryreport(emp *staff)
{
	printf("------------------------------------------------------------\nEmployee ID     :%d\nName            :%s\nDesignation     :%s\nDate of Joining :%04d-%02d-%02d\nProbation Period:%d Months\n"
		,staff->id,staff->name,staff->des,staff->date.year,staff->date.mon,staff->date.day,staff->probation);
	printf("--- Earnings --\nBasic Salary	         :%.2lf\nDearness Allowance(DA)   :%.2lf\nHouse Rent Allowance(HRA):%.2lf\nGross Salary		 :%.2lf\n\n--- Deductions ---\nTax Deducted at Source(TDS) :%.2lf\nNational Pension Scheme(NPS):%.2lf\nGroup Insurance(GI)	    :%.2lf\nTotal Deductions	    :%.2lf\n\n--- Net Salary ---\nNet Salary:%.2lf\n------------------------------------------------------------\n"
		,staff->basic,da(staff),hra(staff),gross(staff),tds(staff),nps(staff),gi(staff),deductions(staff),netsal(staff));

}
int idExists(FILE *fp, int id)
{
    emp temp;
    rewind(fp);  // Always start from top
    while (filescan(fp, &temp))
    {
        if (temp.id == id)
            return 1; // Found
    }
    return 0; // Not found
}

int probationEnd(emp *staff)
{
	struct tm pr_end = {0};	

	pr_end.tm_year = staff->date.year - 1900;
	pr_end.tm_mon= staff->date.mon -1 + staff->probation;
	pr_end.tm_mday = staff->date.day;

	mktime(&pr_end);

	time_t now = time(NULL);
	struct tm *today = localtime(&now);

	//printf("Today's Date is %4d-%2d-%2d\n",today->tm_year+1900,today->tm_mon+1,today->tm_mday);

	if(pr_end.tm_year == today->tm_year && pr_end.tm_mon  == today->tm_mon && pr_end.tm_mday == today->tm_mday)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
