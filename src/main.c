/*File for quic command implementation*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>

#include "Utils.h"



int main(int argc, char* argv[]){
	bool start = validity_check(argv[1], argv[2]);
	
	if(start == kFALSE)
		exit(-1);
	
	DIR *src, *dst;
	
	return 0;
}