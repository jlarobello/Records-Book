/*****************************************************************
*
*  NAME:        Jonathan Robello
*
*  HOMEWORK:    Project 2
*
*  CLASS:       ICS 212
*
*  INSTRUCTOR:  Ravi Narayan
*
*  DATE:        June, 28 2015
*
*  FILE:  	 driver.cpp
*
*  DESCRIPTION: Driver file for project2 which will take user input for
*               modifying records database.
*
*****************************************************************/

#ifndef _DEBUGMODE
#define _DEBUGMODE 0
#endif
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "llist.h"
#include "record.h"
using namespace std;

/* Prototypes */
void getfield(char[]);
void getyob(int&);

int main(int argc, char *argv[])
{
    llist * list;
    int yearofbirth = 0, console = 1;
    //char validCmd[68] = "Valid Arguments: \"debug\" (for debug mode)\n";
    char validCmd2[500] = "Valid Commands:\n add - add a new record \n printRec - prints a record using name as the key \n modify - modifies a record using name as the key \n printAll - Prints all information in the database \n delete - delete an existing record using name as the key\n reverse - reverses the list\n help - list of commands\n quit - exit the program\n";
    char userInput[1000], name[25], address[80], telno[15];
    list = new llist();
    if (_DEBUGMODE == 1)
    {
        strcat(validCmd2, " copyTest - to test copy constructor \n");
    }
    if (console == 1)
    {
        cout << "Welcome to the records database! Type \"help\" for a list of commands\n" << endl;
        memset(&name, 0, sizeof(name));
    }
    while (console == 1)
    {
        cout << "Command: " << flush;
        cin.getline(userInput, sizeof(userInput));
		cout << "\n" << endl;
		if (strcmp(userInput, "help") == 0)
        {
            cout << validCmd2 << endl;
        }
        else if (strcmp(userInput, "quit") == 0)
        {
            console = 0;
        }
        else if (strcmp(userInput, "add") == 0)
        {
            memset(&address, 0, sizeof(address));
            cout << "Adding new record..." << endl;
            cout << "Name: " << flush;
            cin.getline(name, sizeof(name));
            getfield(address);
            getyob(yearofbirth);
            cout << "Telephone Number: " << flush;
            cin.getline(telno, sizeof(telno));
            cout << endl;
            list->addRecord(name, address, yearofbirth, telno);
        }
        else if (strcmp(userInput, "printRec") == 0)
        {
            cout << "Specify name to look for." << endl;
            cout << "Name: " << flush;
            cin.getline(name, sizeof(name));
            list->printRecord(name);
        }
        else if (strcmp(userInput, "modify") == 0)
        {
            cout << "Specify person to modify." << endl;
            cout << "Name: " << flush;
            cin.getline(name, sizeof(name));
            memset(&address, 0, sizeof(address));
            getfield(address);
            cout << "Telephone number: " << flush;
            cin.getline(telno, sizeof(telno));
            cout << endl;
            list->modifyRecord(name, address, telno);
        }
        else if (strcmp(userInput, "printAll") == 0)
        {
            cout << *list << endl;
        }
        else if (strcmp(userInput, "delete") == 0)
        {
            cout << "Specify person to delete." << endl;
            cout << "Name: " << flush;
            cin.getline(name, sizeof(name));
            list->deleteRecord(name);
        }
        else if (strcmp(userInput, "reverse") == 0)
        {
            cout << "Reversing the list...\n" << endl;
            list->reverse();
        }
        else if (strcmp(userInput, "copyTest") == 0 && _DEBUGMODE == 1)
        {
            //Test my overloaded assignment operator.
            llist *list2 = new llist("output2.txt"), list3("output3.txt");
            list3 = *list2 = *list;
            cout << "Printing list2\n" << endl;
            list2->printAll();
            cout << "Printing list3\n" << endl;
            cout << list3 << endl;
            delete(list2);
        }
        else
        {
            cout << "Invalid command!\n\n" << validCmd2 << "\n" << endl;
        }
        cin.clear();
    }
    delete(list);
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
    int count = -1;
    char temp[80];
    cout << "Address (hit enter twice when finished): " << flush;
    while (count < 1)
	{
        cin.getline(temp, sizeof(temp));
        if (temp[0] == '\0')
        {
            count++;
        }
        else
        {
            strcat(out, temp);
            count = 0;
        }
        out[strlen(out)] = ' ';
    }
}

/*****************************************************************
*
* Function name: getyob
*
* DESCRIPTION:   Gets the year of birth from user input. Only
*                numbers allowed.
*
* Parameters:    yearofbirth - changes year of birth.
*
* Return values: returns void.
*
*****************************************************************/

void getyob(int &yob)
{
    cout << "Year of birth: " << flush;
    char temp[80], *end;
    cin.getline(temp, sizeof(temp));
    yob = (int)strtol(temp, &end, 10);
}

