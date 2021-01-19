#pragma once

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

bool validity_check(char* input1, char* input2);