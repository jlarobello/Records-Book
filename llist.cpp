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
*  FILE:        llist.cpp
*
*  DESCRIPTION: Contains functions for modifying records database.
*
*
*****************************************************************/

#ifndef _DEBUGMODE
#define _DEBUGMODE 0
#endif
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include "llist.h"
#include "record.h"
using namespace std;

/***********************************************************************
*
* Function name: llist
*
* DESCRIPTION:   Constructor for functions.
*
* Parameters:    none
*
**********************************************************************/

llist::llist()
{
    start = NULL;
    strcpy(filename, "output.txt");
    readfile();
}

/***********************************************************************
*
* Function name: llist
*
* DESCRIPTION:   Constructor for functions with add filename option
*
* Parameters:    fname - name of file to add.
*
**********************************************************************/

llist::llist(char fname[])
{
    start = NULL;
    strcpy(filename, fname);
    readfile();
}

/***********************************************************************
*
* Function name: ~llist
*
* DESCRIPTION:   The deconstructor. Write records to a file and
*                deallocates the records.
*
* Parameters:    none
*
**********************************************************************/

llist::~llist()
{
    writefile();
    cleanup();
}

/*****************************************************************
*
*  Function name: addRecord
*
*  DESCRIPTION:   When called on with the valid arguments, it
*                 will add a record to the database.
*
*  Parameters:    uname(char) - name of the person.
*                 uaddress(char) - address of the person.
*                 uyearofbirth(int) - year of person' birth.
*                 utelno(char) - person' telephone number.
*
*  Return values: returns a int.
*
*****************************************************************/

int llist::addRecord(char uname[], char uaddress[], int uyearofbirth, char utelno[])
{
    int index = 0;
    struct record **newStart = &start;
    struct record *newRec = NULL;
    struct record *temp = *newStart;
    if (_DEBUGMODE == 1)
    {
        cout << "addRecord Function\nName: " << uname << "\nAddress: " << uaddress << "\nYob: " << uyearofbirth << "\nTelno: " << utelno << "\n" << endl;
	}
    if (temp == NULL)
    {
        temp = new record();
        temp->next = NULL;
        strcpy(temp->name, uname);
        strcpy(temp->address, uaddress);
        temp->yearofbirth = uyearofbirth;
        strcpy(temp->telno, utelno);
        start = temp;
        index++;
	}
    else if (temp->next == NULL)
    {
        newRec = new record();
        newRec->next = NULL;
        temp->next = newRec;
        strcpy(newRec->name, uname);
        strcpy(newRec->address, uaddress);
        newRec->yearofbirth = uyearofbirth;
        strcpy(newRec->telno, utelno);
    }
    else
    {
        while (temp->next != NULL)
        {
            temp = temp->next;
            index++;
            if (temp->next == NULL)
            {
                newRec = new record();
                newRec->next = NULL;
                temp->next = newRec;
                strcpy(newRec->name, uname);
                strcpy(newRec->address, uaddress);
                newRec->yearofbirth = uyearofbirth;
                strcpy(newRec->telno, utelno);
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
*  Parameters:    name - name of person to search.
*
*  Return values: return a int.
*
*****************************************************************/

int llist::printRecord(char uname[])
{
    int index = 0;
    struct record *temp = start;
    if (_DEBUGMODE == 1)
    {
        cout << "\nprintRecord Function\n" << "Name: " << uname << "\n" << endl;
    }
    while (temp != NULL)
    {
        index++;
        if (strcmp(uname, temp->name) == 0)
        {
            cout << "Printing Record...\n" << endl;
            cout << "Name: " << temp->name << endl;
            cout << "Address: " << temp->address << endl;
            cout << "Yob: " << temp->yearofbirth << endl;
            cout << "Telno: " << temp->telno << "\n" << endl;
        }
        temp = temp->next;
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
 *  Parameters:    uname - name of person to search.
 *                 uaddress - address of the person.
 *                 utelno - telephone number of the person.
 *
 *  Return values: returns a int.
 *
 *****************************************************************/

int llist::modifyRecord(char uname[], char uaddress[], char utelno[])
{
    int index = 0;
    struct record *temp = start;
    if (_DEBUGMODE == 1)
    {
        cout << "\nmodifyRecord Function\n" << "Name: " << uname << "\nAddress: " << uaddress << "\nTelno: " << utelno << "\n" << endl;
    }
    while (temp != NULL)
    {
        index++;
        if (strcmp(uname, temp->name) == 0)
        {
            memset(&temp->address[0], 0, strlen(temp->address));
            memset(&temp->telno[0], 0, strlen(temp->telno));
            strcpy(temp->address, uaddress);
            strcpy(temp->telno, utelno);
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
*  Parameters:    None
*
*  Return values: returns void.
*
*****************************************************************/

void llist::printAll()
{
    struct record *temp = start;
    cout << "Printing all records...\n" << endl;
    while (temp != NULL)
    {
        cout << "Name: " << temp->name << endl;
        cout << "Address: " << temp->address << endl;
        cout << "Yob: " << temp->yearofbirth << endl;
        cout << "Telno: " << temp->telno << "\n" << endl;
        temp = temp->next;
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

int llist::deleteRecord(char uname[])
{
    int index = 0;
    struct record **newStart = &start;
    struct record *temp1 = *newStart;
    struct record *temp2 = NULL;
    if (_DEBUGMODE == 1)
    {
        cout << "\ndeleteRecord Function\n" << "name: " << uname << "\n" << endl;
    }
    while (temp1 != NULL)
    {
        if (strcmp(temp1->name, uname) == 0)
        {
            if (strcmp((*newStart)->name, uname) == 0)
            {
                temp2 = (*newStart)->next;
                free(*newStart);
                *newStart = temp2;
                temp1 = *newStart;
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
 * Parameters:    None
 *
 * Return values: return void.
 *
 ********************************************************************/

void llist::cleanup()
{
    string input;
    struct record **newStart = &start;
    struct record *temp1 = *newStart;
    struct record *temp2 = NULL;
    while (temp1 != NULL)
    {
        temp2 = (*newStart)->next;
        free(*newStart);
        *newStart = temp2;
        temp1 = *newStart;
    }
}

/**********************************************************************
 *
 * Function name: readfile
 *
 * DESCRIPTION:   Reads a file for commands
 *
 * Parameters:    None
 *
 * Return values: returns an int
 *
 **********************************************************************/

int llist::readfile()
{
    int count = 0, yob, returnVal = 0;
    string input;
    char name[25], address[80], telno[15];
    ifstream read(filename);
    if (_DEBUGMODE == 1)
    {
        cout << "readfile Function\nFilename: " << filename << "\n" << endl;
    }
    if (read.is_open())
    {
        while (getline(read,input))
        {
            if (count == 0)
            {
                strcpy(name, input.c_str());
                count++;
            }
            else if (count == 1)
            {
                strcpy(address, input.c_str());
                count++;
            }
            else if (count == 2)
            {
                yob = atoi(input.c_str());
                count++;
            }
            else if (count == 3)
            {
                strcpy(telno, input.c_str());
                addRecord(name, address, yob, telno);
                count = 0;
            }
        }
    }
    else
    {
        cout << "Cannot open " << filename << " or file doesn't exist." << endl;
        returnVal = 1;
    }
    read.close();
    return returnVal;
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
 * Return values: returns an int
 *
 **********************************************************************/

int llist::writefile()
{
    struct record *temp = start;
    ofstream write(filename);
    if (_DEBUGMODE == 1)
    {
    cout << "writeFile Function\nFilename: " << filename << endl;
    }
    while (temp != NULL)
    {
        if (write.is_open())
        {
            write << temp->name << "\n";
            write << temp->address << "\n";
            write << temp->yearofbirth << "\n";
            write << temp->telno << "\n";
            temp = temp->next;
        }
    }
    write.close();
    return 0;
}

/***********************************************************************
 *
 * Function name: reverse
 *
 * DESCRIPTION:   Reverses the linked list
 *
 * Parameters:    
 *
 * Return values: returns void
 *
 **********************************************************************/

void llist::reverse()
{
    reverse(start);
}

/***********************************************************************
 *
 * Function name: reverse
 *
 * DESCRIPTION:   Helper function for the reverse functions.
 *
 * Parameters:    record - a record
 *
 * Return values: returns a pointer to a record
 *
 **********************************************************************/

record * llist::reverse(record * rec)
{
    record * head = rec;
    record * last;
    if (head == NULL)
    {
        head = NULL;
    }
    else if (head->next == NULL)
    {
        start = head;
        head = rec;
    }
    else
    {
        last = reverse(head->next);
        last->next = head;
        head = rec;
        head->next = NULL;
    }
    return head;
}

/***********************************************************************
 *
 * Function name: operator <<
 *
 * DESCRIPTION:   Overloads << operator to print records in the database.
 *
 * Parameters:    os - the ostream
 *                list - reference to a llist class.
 *
 * Return values: return a ostream reference.
 *
 **********************************************************************/

ostream& operator<<(ostream& os, const llist& list)
{
    struct record *temp = list.start;
    cout << "Printing all records...\n" << endl;
    while (temp != NULL)
    {
        os << "Name: " << temp->name << endl;
        os << "Address: " << temp->address << endl;
        os << "Yob: " << temp->yearofbirth << endl;
        os << "Telno: " << temp->telno << "\n" << endl;
        temp = temp->next;
    }
    return os;
}

/***********************************************************************
 *
 * Function name: operator =
 *
 * DESCRIPTION:   Overload = operator to copy the contents of llist to
 *                another llist.
 *
 * Parameters:    list - reference to a llist to make copy of.
 *
 * Return values: return a llist reference.
 *
 **********************************************************************/

llist& llist::operator=(const llist& list)
{
    struct record *temp = list.start;
    cleanup();
    while (temp != NULL)
    {
        addRecord(temp->name, temp->address, temp->yearofbirth, temp->telno);
        temp = temp->next;
    }
    return *this;
}

