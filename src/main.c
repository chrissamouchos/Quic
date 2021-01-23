/*File for quic command implementation*/
#include <stdio.h>
#include <stdlib.h>		/*exit*/
#include <unistd.h>

#include "Utils.h"
#include "Directory_Functions.h"


int main(int argc, char* argv[]){
	int v, d, l, c; 		/*getopt*/
	v = d = l = kFALSE;
	
	bool start = validity_check(argv[1], argv[2]);	/*Check validity of given arguments*/
	
	/* -------------Get Options of Command line--------------*/
	while( (c = getopt(argc,argv,"vdl")) != -1) {
		switch(c) {
			case 'v':
				v = kTRUE;
				break;
			case 'd':
				d = kTRUE;
				break;
			case 'l':
				l =kTRUE;
				break;
			case '?':
				return 1;
		}
	}

	if(start == kFALSE)								/*If src == dst, stop execution!*/
		exit(-1);
	
	Pdir dirs = open_or_create_directories(argv[1], argv[2]);	
	// if(v == k)
	int counter = 0;
	counter = print_dir(dirs -> src, argv[1]);
	printf("\n\nthere are %d files/directories in the hierarchy\n", counter);
	
	cyan();
	printf("\nRewinding Src directory pointer...\n");
	rewinddir(dirs -> src);
	reset();

	deep_copy(dirs -> src, argv[1], argv[2]);
	counter = print_dir(dirs -> dst, argv[1]);
	printf("\n\nCopied %d files/directories in the hierarchy\n", counter);
	
	close_directories(dirs);
	return 0;
}