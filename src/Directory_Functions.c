/*Source code for Directory operations*/
#include <stdio.h>
#include <stdlib.h>		/*malloc*/
#include <sys/stat.h> 	/*mkdir	*/
#include <dirent.h>
#include <string.h>

#include "Utils.h"		/*for customed functions*/
#include "Directory_Functions.h"

#define MAX_NAME_SIZE 256

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
	d -> dst = opendir(dst);
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

char* path_join(char* dest, const char* path,const char* suffix) {
    sprintf(dest,"%s/%s",path,suffix);
    return dest;
}

void print_dir(DIR* dir, char* path){
	Dirent direnpt;							/*Struct to store info of current directory 		*/
	DIR* inside;							/*Pointer to nested directory, useful for recursion	*/
	
	char temp[MAX_NAME_SIZE];				/*Max path to be stored 							*/

/*-------------------MODIFICATIONS-----------------------------------*/
	while((direnpt = readdir(dir)) != NULL){
        path_join(temp, path, direnpt -> d_name);
        
        printf("%s\n", temp);
     
        if(strcmp(direnpt -> d_name,".") == 0 || strcmp(direnpt -> d_name,"..") == 0)
            continue;
     	
        if(direnpt -> d_type == DT_DIR){
            inside = opendir(direnpt -> d_name);
            
            if(inside != NULL)	
               	print_dir(inside, temp);
            
            closedir(inside);
        }

    }
/*-------------------END OF MODIFICATIONS-----------------------------*/
	return;
}

// if(direnpt -> d_type == DT_DIR && (flag > 2)){
		
// 			printf("%s/\n", direnpt -> d_name);
// 			inside = opendir(direnpt -> d_name);
	 	
// 			if(inside != NULL)
// 				print_dir(inside, direnpt -> d_name);
			
// 			closedir(inside);
// 		}
// 		else{
// 			char temp[MAX_NAME_SIZE];
// 			strcpy(temp, path);
// 			strcat(temp, direnpt -> d_name);
// 			printf("%s\n", temp);
// 			// printf("%s\n", direnpt -> d_name);
// 		}
// 	}