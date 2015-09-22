/*******************************************************************************
 *
 * Name: Jonathan Robello
 *
 * Homework: Project2 
 *
 * Instructor: Ravi Narayan
 *
 * Date: June 28, 2015
 *
 * File: record.h
 *
 * Description: Contains information of a person for
 *              for a records database.
 *
 ******************************************************************************/

#ifndef RECORD_H_
#define RECORD_H_

struct record{
	char name[25];
	char address[80];
	int yearofbirth;
	char telno[15];
	struct record* next;
};

#endif /* RECORD_H_ */
