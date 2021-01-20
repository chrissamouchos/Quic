/*Source code for Directory operations*/
#include <stdio.h>
#include <stdlib.h>		/*malloc*/
#include <sys/stat.h> 	/*mkdir	*/
#include <dirent.h>

#include "Utils.h"		/*for customed functions*/

#include "Directory_Functions.h"

Pdir dir_index_create(void){
	Pdir d = malloc(sizeof(dir_index));	/*Allocate needed struct memory	*/
	
	d -> src = NULL;					/*Initialize					*/
	d -> dst = NULL;					/*Pointers to NULL 				*/
	
	return d;							/*return pointer to struct 		*/
}

void dir_index_destroy(Pdir dirs){
	free(dirs);							/*free struct allocated memory 	*/
}

Pdir open_or_create_directories(char* src, char* dst){
	
	Pdir d = dir_index_create();				/*Create struct to store DIR* 	*/
	
	if((d -> src = opendir(src)) == NULL){		/*Open source directory 		*/
		red();
		printf("Cannot open Src directory\n");	/*Print upon failure 			*/
		reset();
		return NULL;
	}
	
	if((d -> dst = opendir(dst)) == NULL){		/*Open destination directory 		*/
		red();
		printf("Cannot open Dst directory\n");	/*If dst does not exist create it 	*/
		reset();

		green();
		printf("Creating directory...\n");
		reset();

		if(mkdir(dst, MODE) == -1){
			perror("Error directory Creating");	/*Print upon failure 				*/
			return NULL;
		}
	}
	return d;									/*Return pointer to struct with stored	/
												/ pointers to dst and src respectively */
}

void close_directories(Pdir d){
	
	if((closedir(d -> src)) == -1){
		red();
		perror("Error: Cannot close src directory"); /*Print upon failure 			*/
		reset();
	}

	if(closedir(d -> dst) == -1){
		red();
		perror("Error: Cannot close dst directory"); /*Print upon failure 			*/
		reset();
	}

	dir_index_destroy(d);	/*Free meemory of struct */
}

void print_dir(DIR* dir){
	
}