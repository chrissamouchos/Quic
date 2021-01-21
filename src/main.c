/*File for quic command implementation*/
#include <stdio.h>
#include <stdlib.h>		/*exit*/
#include <unistd.h>

#include "Utils.h"
#include "Directory_Functions.h"


int main(int argc, char* argv[]){
	bool start = validity_check(argv[1], argv[2]);	/*Check validity of given arguments*/
	
	if(start == kFALSE)								/*If src == dst, stop execution!*/
		exit(-1);
	
	Pdir d = open_or_create_directories(argv[1], argv[2]);	
	int counter = 0;
	counter = print_dir(d -> src, ".", counter);
	printf("\n\nthere are %d files/directories in the hierarchy\n", counter);
	close_directories(d);
	return 0;
}