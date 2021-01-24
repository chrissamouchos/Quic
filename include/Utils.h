/*Prototypes of various functions*/

#pragma once

/*Define boolean variables in order to avoid extra "libary include"*/
typedef enum{
	kFALSE = 0,
	kTRUE
}bool;

/*------------ Printing Functions --------------*/

void red();		/*Chane printing color to red 	*/

void green();	/*Chane printing color to green	*/

void cyan();	/*Chane printing color to cyan	*/

void reset();	/*Reset color to default		*/

/*------------- End of Printing Functions ------*/

/*------------- Various Functions --------------*/

bool validity_check(char* input1, char* input2); /*Check if src and dst are different*/

void usage(); /*Print proper input format*/

/*-------------- End of various Functions -----*/

/*-------------- Find size and Time -----------*/
typedef struct statistic{
	float 	time_elapsed;
	int 	dir_size;
	float 	pace;
}statistics;

typedef statistics* Stats;

Stats statistics_create(void);

void statistics_destroy(Stats s);