/*****************************************************************
 *
 *  NAME:        Jonathan Robello
 *
 *  HOMEWORK:    3
 *
 *  CLASS:       ICS 212
 * 
 *  INSTRUCTOR:  Ravi Narayan
 *
 *  DATE:        June, 13 2015
 *
 *  FILE:  	 record_functions.c
 *
 *  DESCRIPTION: Contains functions for modifying records database.
 *
 *
 *****************************************************************/

#include <stdio.h>
#include "record.h"
extern int debugmode;

/* Prototypes */
int addRecord(struct record**, char[], char[], int, char[]);
int printRecord(struct record*, char[]);
int modifyRecord(struct record*, char[], char[], char[]);
void printAllRecords(struct record*);
int deleteRecord(struct record**, char[]);
void cleanup(struct record**);
int readfile(struct record**, char[]);
void writefile(struct record*, char[]);

/*****************************************************************
 *
 *  Function name: addRecord
 *
 *  DESCRIPTION:   When called on with the valid arguments, it
 *                 will add a record to the database.
 *
 *  Parameters:    start(struct record**) - the first record of the
 *                 database.
 *                 name(char) - name of the person.
 *                 address(char) - address of the person.
 *                 yearofbirth(int) - year of person' birth.
 *                 telno(char) - person' telephone number.
 *
 *  Return values: returns a int.
 *
 *****************************************************************/

int addRecord(struct record** start, char uname[], char uaddress[], int uyearofbirth, char utelno[])
{
    int index = 0;
    struct record *newRec = NULL;
    struct record *temp = *start;
    if(debugmode == 1)
    {
        printf("name: %s\naddress: %s\nyob: %d\ntelno: %s\n", uname, uaddress, uyearofbirth, utelno);
    }
    if(temp == NULL)
    {
        temp = (struct record*)malloc(sizeof(struct record));
        temp->next = NULL;
        strncpy(temp->name, uname, 25);
        strncpy(temp->address, uaddress, 80);
        temp->yearofbirth = uyearofbirth;
        strncpy(temp->telno, utelno, 15);
        *start = temp;
        index++;
    }
    else if(temp->next == NULL)
    {
        newRec = (struct record*)malloc(sizeof(struct record));
        newRec->next = NULL;
        temp->next = newRec;
        strncpy(newRec->name, uname, 25);
        strncpy(newRec->address, uaddress, 80);
        newRec->yearofbirth = uyearofbirth;
        strncpy(newRec->telno, utelno, 15);
    }
    else
    {
        while(temp->next != NULL)
        {
            temp = temp->next;
            index++;
            if(temp->next == NULL)
            {
                newRec = (struct record*)malloc(sizeof(struct record));  
                newRec->next = NULL;
                temp->next = newRec;
                strncpy(newRec->name, uname, 25);
                strncpy(newRec->address, uaddress, 80);
                newRec->yearofbirth = uyearofbirth;
                strncpy(newRec->telno, utelno, 15);
                break;
            }
        }
    }
    return index;
}

/*****************************************************************
 *
 *  Function name: printRecord
 *
 *  DESCRIPTION:   Prints the record of the person using name as
 *                 the key.
 *
 *  Parameters:    start - the start of the record database to
 *                 search.
 *                 name - name of person to search.
 *
 *  Return values: return a int.
 *
 *****************************************************************/

int printRecord(struct record* start, char uname[])
{
    int index = 0, count = 0;
    struct record * temp = start;
    if(debugmode == 1)
    {
        printf("name: %s\n", uname);
    }
    while(temp != NULL)
    {
        index++;
        if(strcmp(uname, temp->name) == 0)
        {
            printf("Printing Record....\n\n");
            printf("Name: %s\n", temp->name);
            printf("Address: %s\n", temp->address);
            printf("yob: %d\n", temp->yearofbirth);
            printf("telno: %s\n\n", temp->telno);
            count++;
        }
        temp = temp->next;
    }    
    if(count == 0)
    {
        printf("\"%s\" is not in list\n", uname);
    }
    return index;
}

/*****************************************************************
 *
 *  Function name: modifyRecord
 *
 *  DESCRIPTION:   Modify a record in the database using name as
 *                 the key.
 *
 *  Parameters:    start - the start of the record database to
 *                 search.
 *                 uname - name of person to search.
 *                 uaddress - address of the person.
 *                 utelno - telephone number of the person.
 *
 *  Return values: returns a int.
 *
 *****************************************************************/

int modifyRecord(struct record* start, char uname[], char uaddress[], char utelno[])
{
    int index = 0;
    struct record *temp = start;
    if(debugmode == 1)
    {
        printf("name: %s\naddress: %s\ntelno: %s\n", uname, uaddress, utelno);
    }
    
    while(temp != NULL)
    {
       index++;
       if(strcmp(uname, temp->name) == 0)
       {
           memset(&temp->address[0], 0, strlen(temp->address));
           memset(&temp->telno[0], 0, strlen(temp->telno));
           strncpy(temp->address, uaddress, 80); 
           strncpy(temp->telno, utelno, 15);
       }
       temp = temp->next;
    }
    return index; 
}

/*****************************************************************
 *
 *  Function name: printAllRecords
 *
 *  DESCRIPTION:   print all info in database.
 *
 *  Parameters:    head - the start of the record database to
 *                 print.
 *
 *  Return values: returns void.
 *
 *****************************************************************/

void printAllRecords(struct record* start)
{
    int count = 0;
    struct record * temp = start;
    printf("Printing all records...\n\n");
    while(temp != NULL)
    {
        printf("Name: %s\n", temp->name);
        printf("Address: %s\n", temp->address);
        printf("yob: %d\n", temp->yearofbirth);
        printf("telno: %s\n\n", temp->telno);
        temp = temp->next;
        count++;
    }
    if(count == 0)
    {
        printf("No Records to print...\n");
    }
}

/*****************************************************************
 *
 *  Function name: deleteRecord
 *
 *  DESCRIPTION:   Deletes a existing record using name as the
 *                 key.
 *
 *  Parameters:    start - the start of the record database to
 *                 search.
 *                 name - the name in record to delete.
 *
 *  Return values: returns a int.
 *
 *****************************************************************/

int deleteRecord(struct record** start, char uname[])
{
    int index = 0;
    struct record *temp1 = *start;
    struct record *temp2 = NULL;
    if(debugmode == 1)
    {
        printf("name: %s\n", uname);
    }
    while(temp1 != NULL)
    {
        if(strcmp(temp1->name, uname) == 0)
        {
            if(strcmp((*start)->name, uname) == 0)
            {
                temp2 = (*start)->next;
                free(*start);
                *start = temp2;
                temp1 = *start;
                index++;
            }
            else
            {
                temp2->next = temp1->next;
                free(temp1);
                temp1 = temp2->next;
                index++;
            }
        } 
        else
        {
            temp2 = temp1;
            temp1 = temp1->next;
            index++;
        }
    }    
    return index;
}

/********************************************************************
 *
 * Function name: cleanup
 *
 * DESCRIPTION:   Deletes all existing records.
 *
 * Parameters:    start - start of the record database.
 *
 * Return values: return void.
 *
 ********************************************************************/
 
void cleanup(struct record** start)
{
    struct record *temp1 = *start;
    struct record *temp2 = NULL;
    while(temp1 != NULL)
    {
        temp2 = (*start)->next;
        free(*start);
        *start = temp2;
        temp1 = *start;
    }
}

/**********************************************************************
 *
 * Function name: readfile
 *
 * DESCRIPTION:   Reads a file for commands
 *
 * Parameters:    start - start of the database.
 *                fname - name of txt file with commands.
 *
 * Return values: returns an int
 *
 **********************************************************************/
 
int readfile(struct record** start, char fname[])
{
    int count = 0, i, yob;
    struct record *temp = *start;
    char name[25], address[80], telno[15], input[300];
    FILE * read = fopen(fname, "r");
    if(debugmode == 1)
    {
        printf("Filename: %s\n", fname);
    }
    if(read == NULL)
    {
        printf("Cannot open %s or file doesn't exist\n", fname);
        return 1;
    }
    else
    {    
        while(fgets(input, sizeof(input), read) != NULL)
        {
            if(count == 0)
            {
                strncpy(name, input, 25);
                name[strlen(name)-1] = '\0';
                count++;
            }
            else if(count == 1)
            {
                strncpy(address, input, 80);
                address[strlen(address)-1] = '\0';
                count++;
            }
            else if(count == 2)
            {
                yob = atoi(input);
                count++;
            }
            else if(count == 3)
            {
                strncpy(telno, input, 15);
                telno[strlen(telno)-1] = '\0';
                addRecord(start, name, address, yob, telno);
                count = 0;
            }
        }
    }
    fclose(read);  
    return 0;  
}

/***********************************************************************
 *
 * Function name: writefile
 *
 * DESCRIPTION:   Writes the output of the program.
 *
 * Parameters:    start - start of the database.
 *                fname - name of txt file to output to.
 *
 * Return values: returns void
 *
 **********************************************************************/

void writefile(struct record* start, char fname[])
{
    struct record *temp = start;
    FILE * write = fopen(fname, "w");
    if(debugmode == 1)
    {
        printf("Filename: %s\n", fname);
    }
    while(temp != NULL)
    {
        fprintf(write, "%s\n", temp->name);
        fprintf(write, "%s\n", temp->address);
        fprintf(write, "%d\n", temp->yearofbirth);
        fprintf(write, "%s\n", temp->telno);
        temp = temp->next; 
    }
    fclose(write);
}
