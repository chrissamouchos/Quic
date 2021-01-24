/*Source code for various functions*/
#include <stdio.h>
#include <string.h>

#include "Utils.h"

/*------------ Printing Functions ------------------*/
void red(){
 	printf("\033[1;31m");
}

void green(){
	printf("\033[1;32m");
}

void cyan(){
	printf("\033[1;36m");
}

void reset(){
 	printf("\033[0m");
}
/*------------- End of Printing Functions ---------*/

bool validity_check(char* input1, char* input2){
	if(strcmp(input1, input2) == 0){
		red();
		printf("Error: Destination and Source are identical\n");
		reset();
		return kFALSE;
	}
	return kTRUE;
}

void usage(){
	red();
	printf("Error: Wrong input\n");

	cyan();
	printf("Proper input: <./quic -v -d -l origindir destdir>\n");
	reset();
}


Stats statistics_create(void){
	Stats s = malloc(sizeof(statistics));

	s -> time_elapsed = 0.0;
	s -> dir_size = 0;
	s -> pace = 0.0;

	return s;
}

void statistics_destory(Stats s){
	free(s);
}