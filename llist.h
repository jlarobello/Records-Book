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
*  FILE:  	    llist.h
*
*  DESCRIPTION: Contains the prototypes for the llist class
*
*****************************************************************/

#include "record.h"

class llist
{
private:
    record *start;
    char filename[16];
    int readfile();
    int writefile();
    record * reverse(record *);
    void cleanup();

public:
    llist();
    llist(char[]);
    llist(const llist&);
    ~llist();
    int addRecord(char[], char[], int, char[]);
    int printRecord(char[]);
    int modifyRecord(char[], char[], char[]);
    void printAll();
    int deleteRecord(char[]);
    void reverse();
    friend std::ostream& operator<<(std::ostream&, llist const&);
    llist& operator=(const llist&);
};
