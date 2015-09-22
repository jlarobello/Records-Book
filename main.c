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
 *  FILE:  	 main.c
 *
 *  DESCRIPTION: Driver file for hw3 which will take user input for
 *               modifying records database.
 *
 *****************************************************************/

#include <stdio.h>
#include "record.h"
int debugmode = 0;

/* Prototypes */
void getfield(char[]);

int main(int argc, char *argv[])
{
    struct record* start = NULL;
    int i, arg1, arg2, arg3, yearofbirth, userInputLength, console = 1;
    char validCmd[68] = "Valid Arguments: \"debug\" (for debug mode)\n";
    char validCmd2[500] = "Valid Commands:\n add - add a new record \n printRec - prints a record using name as the key \n modify - modifies a record using name as the key \n printAll - Prints all information in the database \n delete - delete an existing record using name as the key\n cleanup - deletes all records in the database\n help - list of commands\n quit - exit the program\n";
    char userInput[1000], argv3[5], name[25], address[80], telno[15], yob[5], confirm[2];
    readfile(&start, "sampleOutput.txt");
    if(argv[1] != NULL)
    {
        arg1 = strcmp(argv[1], "debug");
        if(arg1 == 0)
        {
            debugmode = 1;
            
        }
        else
        {
            console = 0;
            printf("Invalid argument!\n%s", validCmd);
        }
        if(argv[2] != NULL)
        {
	    printf("There can only be one argument!\n%s", validCmd);
	    console = 0;
        }
    }
    if(console == 1)
    {
        printf("Welcome to the records database! Type \"help\" for a list of commands\n\n");
    }
    while(console == 1)
    {
        printf("USER: "); 
        fgets(userInput, 10, stdin); 
        userInput[strlen(userInput)-1] = '\0';
        printf("\n");
        if(strcmp(userInput, "help") == 0)
        {
            printf("%s", validCmd2);
        }
        else if(strcmp(userInput, "quit") == 0) 
        {
            console = 0;
        }
        else if(strcmp(userInput, "add") == 0) 
        {
            memset(&name, 0, sizeof(name));
            memset(&address, 0, sizeof(address));
            memset(&yob, 0, sizeof(yob));
            memset(&telno, 0, sizeof(telno));
            printf("Adding new record...\n");
            printf("Name: ");
            fgets(name, 25, stdin);
            name[strlen(name)-1] = '\0';
            getfield(address);
            printf("Year of birth: ");
            fgets(yob, 5, stdin);
            sscanf(yob, "%d", &yearofbirth);
            while((i = getchar()) != '\n' && i != EOF)
            {
            }
            printf("Telephone Number: ");
            fgets(telno, 15, stdin); 
            telno[strlen(telno)-1] = '\0';
            printf("\n");
            addRecord(&start, name, address, yearofbirth, telno);
        }
        else if(strcmp(userInput, "printRec") == 0) 
        {
            printf("Specify name to look for\n");
            printf("Name: ");
            fgets(name, 25, stdin);
            name[strlen(name)-1] = '\0';
            printRecord(start, name);
        }
        else if(strcmp(userInput, "modify") == 0)
        {
            printf("Specify person to modify\n");
            printf("Name: ");
            fgets(name, 25, stdin);
            name[strlen(name)-1] = '\0';
            memset(&address, 0, sizeof(address));
            getfield(address);
            printf("Telephone number: ");
            fgets(telno, 15, stdin);
            telno[strlen(telno)-1] = '\0';
            printf("\n");
            modifyRecord(start, name, address, telno);
        }
        else if(strcmp(userInput, "printAll") == 0) 
        {
            printAllRecords(start);
        }
        else if(strcmp(userInput, "delete") == 0)
        {
            printf("Specify person to delete\n");
            printf("Name: ");
            fgets(name, 25, stdin);
            name[strlen(name)-1] = '\0';
            deleteRecord(&start, name);
        }
        else if(strcmp(userInput, "cleanup") == 0)
        {
            printf("Deleting all records...\n");
            cleanup(&start);
        }
        else
        {
            printf("Invalid command!\n%s", validCmd2);
        }
    }
    writefile(start, "sampleOutput.txt");
    return 0;
}

/*****************************************************************
 *
 *  Function name: getfield
 *
 *  DESCRIPTION:   Gets the address from user input.
 *
 *  Parameters:    out - outputs person' address to an array. 
 *
 *  Return values: returns void.
 *
 *****************************************************************/

void getfield(char out[])
{
    int count = 0;
    char temp[80];
    printf("Address (hit enter twice when finished): ");
     
    while(count < 1)
    {
        fgets(temp, 80, stdin); 
        out[strlen(out)-1] = ' ';
        if(strcmp(temp, "\n") == 0)
        {
            count++;
        }
        else
        {
            strcat(out, temp);
            count = 0;
        }
    }
    out[strlen(out)-1] = '\0';
}
