/*File for quic command implementation*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/*--------- My libraries ---------------------*/
#include "Utils.h"
#include "Directory_Functions.h"
/*--------- End of My libraries --------------*/

int main(int argc, char* argv[]){
	int v, d, l, c; 		/*getopt*/
	v = d = l = kFALSE;		/*options pre-defined as false*/
	
	/*--------------------STORE PATHS------------------------*/
	char *source, *destination;	/*pointers to strings*/

	source 		= malloc(strlen(argv[1])*sizeof(char));		/*allocate memory for source path 		*/
	destination = malloc(strlen(argv[1])*sizeof(char));		/*allocate memory for destination PATH 	*/

	strcpy(source, argv[1]);		/*copy from inputs to	*/
	strcpy(destination, argv[2]);	/*allocated space		*/
	
	/*--------------------End of STORING PATHS---------------*/

	bool start = validity_check(source, destination);	/*Check validity of given arguments*/
	
	/* -------------Get Options of Command line--------------*/
	while( (c = getopt(argc,argv,"vdl")) != -1){ /*optional settings*/
		switch(c) {
			case 'v':
				v = kTRUE;	/*if v defined, make true*/
				break;

			case 'd':
				d = kTRUE; /*if d defined, make true*/
				break;

			case 'l':
				l =kTRUE; /*if l defined, make true*/
				break;

			case '?':
				usage(); 	/*wrong format, print proper input 	*/
				return -1;	/*terminate* 						*/
		}
	}

	if(start == kFALSE)			/*If src == dst, stop execution!*/
		exit(-1);
	
	Pdir dirs = open_or_create_directories(source, destination);	/*OPEN DIRECTORIES*/
	statistics s;

	if(v == kTRUE){
		int counter = 0;	/*store entities counted*/
		
		// cyan();
		// printf("Content of source directory\n");
		// reset();
		
		// counter = print_dir(dirs -> src, source);	/*Print content recursively*/
		// printf("\n\nthere are %d files/directories in the hierarchy\n", counter);

		/*Reqind DIR* to source, to start of directory again*/
<<<<<<< HEAD
		// cyan();
		// printf("\nRewinding Src directory pointer...\n");
		// reset();  
		
		// rewinddir(dirs -> src);

		s = update(dirs -> src, source, destination);
		// counter = print_dir(dirs -> dst, source);
		printf("\n\nCopied %d files/directories in the hierarchy\n", s.counter);
		printf("copied %d bytes in %.3f at %.3f bytes/sec\n", s.dir_size, s.time_elapsed, s.dir_size/s.time_elapsed);
	}
	else{

=======
		cyan();
		printf("\nRewinding Src directory pointer...\n");
		reset();  
		
		rewinddir(dirs -> src);	/*Place pointer to start of file/directories list*/

		s = update(dirs -> src, source, destination);
		printf("\n\nCopied %d files/directories in the hierarchy\n", s.counter);
		printf("copied %d bytes in %.3f at %.3f bytes/sec\n", s.dir_size, s.time_elapsed, s.dir_size/s.time_elapsed);
	}
	else{
		s = update(dirs -> src, source, destination);
		printf("\n\nCopied %d files/directories in the hierarchy\n", s.counter);
		printf("copied %d bytes in %.3f at %.3f bytes/sec\n", s.dir_size, s.time_elapsed, s.dir_size/s.time_elapsed);
	}

	if(d == kTRUE){
		red();
		printf("Deletion is to be implemented...\n");
		reset();
>>>>>>> 3d56cefe7c2f34a359dd1d6434299d500692faf8
	}
	
	if(l == kTRUE){
		red();
		printf("Soft/Hard Link handling is to be implemented...\n");
		reset();
	}

	/*---------------- Free allocated memory -------------------*/
	close_directories(dirs);
	free(destination); free(source);
	/*---------------- End of free -----------------------------*/
	
	return 0;
}