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
	float 	time_elapsed;	/*Store time elapsed since start copying*/
	int 	dir_size;		/*Store memory size of directory 		*/
	float 	pace;			/*Store ratio 							*/
	int 	counter;		/*copied files*/
}statistics;

typedef statistics* Stats;									 /*Pointer to statistics 	*/

statistics add_to_current(statistics final, statistics cur); /*final += cur 			*/