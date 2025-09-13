#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"employee.h"
#include"salaries.h"

int main()
{
    FILE *fp = fopen("records.txt", "r+");
    if (!fp)
    {
        printf("Couldn't open file!");
        return 0;
    }
    rewind(fp);

    emp staff;
    int recCount = 0;
    while (filescan(fp, &staff))
    {
        recCount++;
    }
    rewind(fp);

    int choice, n;
    printf("1.Filter Data\n2.Add Record\n3.Delete Record\n4.Search Record\n5.Modify Record\n6.Sort Records\n7.Display all records\n8.Get Salary Breakdown\n9.Show Today's Probation Completions\n-1 to EXIT\nEnter option: ");
    while (scanf("%d", &choice) != -1)
    {
        if (choice == -1) break;

        if (choice == 1)
        {
	    rewind(fp);
            int start, end;
            printf("Based on\n1.ID\n2.Designation\n3.Date of Joining\n4.Basic Salary\n5.Probation Period\nEnter choice: ");
            scanf("%d", &n);

            int count = 0;
            switch (n)
            {
                case 1:
                    printf("Enter ID range(ex: 1000-4000): ");
                    scanf("%d-%d", &start, &end);
                    while (filescan(fp, &staff))
                    {
                        if (staff.id >= start && staff.id <= end)
                        {
                            recordPrint(&staff);
                            count++;
                        }
                    }
                    printf("\n%d results found\n", count);
                    break;

                case 2:
                    char string[26];
                    printf("Enter Designation: ");
                    getc(stdin);
                    fgets(string, sizeof(string), stdin);
                    string[strcspn(string, "\n")] = '\0';
                    while (filescan(fp, &staff))
                    {
                        if (strcasecmp(staff.des, string) == 0)
                        {
                            recordPrint(&staff);
                            count++;
                        }
                    }
                    printf("\n%d results found\n", count);
                    break;

                case 3:
                    Date begin, stop;
                    printf("Enter start date: ");
                    scanf("%d-%d-%d", &begin.year, &begin.mon, &begin.day);
                    printf("Enter end date: ");
                    scanf("%d-%d-%d", &stop.year, &stop.mon, &stop.day);
                    while (filescan(fp, &staff))
                    {
                        checkDate(&staff, &begin, &stop);
                        count++;
                    }
                    printf("\n%d results found\n", count);
                    break;

                case 4:
                    printf("Enter basic salary range(ex: 10000-50000): ");
                    scanf("%d-%d", &start, &end);
                    while (filescan(fp, &staff))
                    {
                        if (staff.basic >= start && staff.basic <= end)
                        {
                            recordPrint(&staff);
                            count++;
                        }
                    }
                    printf("\n%d results found\n", count);
                    break;

		 case 5:
		    int pr;
		    printf("Enter number of months on probation(ex: 3,4,6,12,etc.): ");
		    scanf("%d",&pr);
		     while (filescan(fp, &staff))
                    {
                        if (staff.probation==pr)
                        {
                            recordPrint(&staff);
                            count++;
                        }
                    }
                    printf("\n%d results found\n", count);
                    break;

                default:
                    printf("Enter valid choice!\n");
                    break;
            }
        }
        else if (choice == 2)
        {
            fseek(fp, 0, 2);
	do 
	{
    		printf("Enter Employee ID(XXXX): ");
    		scanf("%d", &staff.id);
   	 	getc(stdin);

    		if (idExists(fp, staff.id)) 
		{
        		printf("ID already exists! Please enter a different ID.\n");
    		} 
		else 
		{
        		break;
    		}
	}
       	while (1);
            printf("Enter Employee Name: ");
            getstring(staff.name, sizeof(staff.name));
            printf("Enter Designation: ");
            getstring(staff.des, sizeof(staff.des));
            printf("Enter Date of Joining(YYYY-MM-DD): ");
            scanf("%d-%d-%d", &staff.date.year, &staff.date.mon, &staff.date.day);
            printf("Enter Basic Salary(XXXXXX): ");
            scanf("%lf", &staff.basic);
	    printf("Enter number of months on Probation: ");
            scanf("%d", &staff.probation);
            int written = filePrint(fp, &staff);
            if (written < 0)
            {
                perror("Couldn't add record to the file!\n");
            }
            else
            {
                printf("Record added successfully!\n");
                recCount++;
            }
        }
        else if (choice == 3)
        {
            FILE *ftemp = fopen("temp.txt", "w");
            if (!fp || !ftemp)
            {
                printf("File error!\n");
                return 1;
            }
            rewind(fp);
            int input_id;
            printf("Enter ID to delete record: ");
            scanf("%d", &input_id);
            int found = 0;
            while (filescan(fp, &staff))
            {
                if (staff.id == input_id)
                {
                    recordPrint(&staff);
                    int yn;
                    printf("Do you want to delete this record? Press 1 to proceed, 0 to exit: ");
                    scanf("%d", &yn);
                    if (yn == 1)
                    {
                        found = 1;
                        continue;
                    }
                    else
                    {
                        found = 2;
                    }
                }
                filePrint(ftemp, &staff);
            }
            fclose(ftemp);
            if (found == 1)
            {
                remove("records.txt");
                rename("temp.txt", "records.txt");
                printf("Record deleted successfully.\n");
		recCount--;
		fclose(fp);
		fp = fopen("records.txt", "r+");
		rewind(fp);
		
            }
            else if (found == 2)
            {
                printf("Record not deleted.\n");
            }
            else
            {
                remove("temp.txt");
                printf("Record with ID %d not found.\n", input_id);
            }
        }
        else if (choice == 4)
        {
            rewind(fp);
            int input_id;
            printf("Enter ID: ");
            scanf("%d", &input_id);
            int found = 0;
            while (filescan(fp, &staff))
            {
                if (staff.id == input_id)
                {
                    found = 1;
                    recordPrint(&staff);
                }
            }
            if (found == 0)
            {
                printf("Record with ID %d not found.\n", input_id);
            }
        }
        else if (choice == 5)
        {
            FILE *ftemp = fopen("temp.txt", "w");
            if (!fp || !ftemp)
            {
                printf("File error!\n");
                return 1;
            }
            rewind(fp);
            int input_id;
            printf("Enter ID to modify record: ");
            scanf("%d", &input_id);
            int found = 0;
            while (filescan(fp, &staff))
            {
                if (staff.id == input_id)
                {
                    recordPrint(&staff);
                    found = 1;
                    int x = menu();
                    switch (x)
                    {
                        case 1:
                            printf("Enter new Name: ");
                            getstring(staff.name, sizeof(staff.name));
                            break;
                        case 2:
                            printf("Enter new Designation: ");
                            getstring(staff.des, sizeof(staff.des));
                            break;
                        case 3:
                            printf("Enter new Date of Joining(YYYY-MM-DD): ");
                            scanf("%d-%d-%d", &staff.date.year, &staff.date.mon, &staff.date.day);
                            break;
                        case 4:
                            printf("Enter new Basic Salary(XXXXXX): ");
                            scanf("%lf", &staff.basic);
                            break;
			case 5:
			    printf("Enter new probation period: ");
			    scanf("%d",&staff.probation);
			    break;
                        default:
                            printf("Enter valid choice!\n");
                            break;
                    }
                }
                filePrint(ftemp, &staff);
            }
            fclose(ftemp);
            if (found)
            {
                remove("records.txt");
                rename("temp.txt", "records.txt");
                printf("Record updated successfully.\n");
		fclose(fp);
		fp = fopen("records.txt", "r+");
		rewind(fp);
            }
            else
            {
                remove("temp.txt");
                printf("Record with ID %d not found.\n", input_id);
            }
        }
        else if (choice == 6)
        {
            emp array[recCount];
            fillArray(fp, &staff, array);
            printf("Based on\n1.ID\n2.Name\n3.Date of Joining\n4.Basic Salary\n5.Probation Period\nEnter choice: ");
            scanf("%d", &n);
            switch (n)
            {
                case 1:
                    sortID(array, recCount);
                    break;
                case 2:
                    sortAlpha(array, recCount);
                    break;
                case 3:
                    sortDate(array, recCount);
                    break;
                case 4:
                    sortSal(array, recCount);
                    break;
		case 5:
		    sortPro(array,recCount);
                default:
                    printf("Enter valid choice!\n");
                    break;
            }
            for (int i = 0; i < recCount && n > 0 && n < 5; i++)
            {
                recordPrint(&array[i]);
            }
        }
        else if (choice == 7)
        {
            rewind(fp);
            while (filescan(fp, &staff))
            {
                recordPrint(&staff);
            }
        }
	else if(choice==8)
	{
	    rewind(fp);
	    int input_id;
            printf("Enter ID to get salary breakdown report: ");
            scanf("%d", &input_id);
            int found = 0;
            while (filescan(fp, &staff))
            {
		    if(staff.id==input_id)
		    {
			found=1;
			salaryreport(&staff);			    
		    }
	    }
	    if (found == 0)
            {
                printf("Record with ID %d not found.\n", input_id);
            }

	}
	else if(choice==9)
	{
	    rewind(fp);
	    int count=0;
            while (filescan(fp, &staff))
            {
		    if(probationEnd(&staff)==1)
		    {
			    recordPrint(&staff);
			    count++;
		    }                
            }

	    printf("%d results found\n",count);
		
	}
        else
        {
            printf("Enter valid choice!\n");
        }
        printf("\n1.Filter Data\n2.Add Record\n3.Delete Record\n4.Search Record\n5.Modify Record\n6.Sort Records\n7.Display all records\n8.Get Salary Breakdown\n9.Show Today's Probation Completions\n-1 to EXIT\nEnter option: ");
    }

    fclose(fp);
    return 0;

}
