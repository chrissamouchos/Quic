/*Source code for Directory operations*/
#include <stdio.h>		/*printf*/
#include <stdlib.h>		/*malloc*/
#include <sys/stat.h> 	/*mkdir	*/
#include <dirent.h>		/*struct*/
#include <string.h>		/*strcmp*/
#include <fcntl.h>		/*open, close, read, write*/
#include <unistd.h>

#include "Utils.h"					/*for customed functions*/
#include "Directory_Functions.h"	/*prototypes 			*/

#define MAX_NAME_SIZE	256
#define BUFFER_SIZE		4096
#define PERMS 			0644

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

char* path_join(char* dest, const char* path,const char* suffix){
    sprintf(dest,"%s/%s",path,suffix);								/*Combine previous path with current suffix to new string*/
    return dest;
}

int print_dir(DIR* dir, char* path){
	Dirent direnpt;							/*Struct to store info of current directory 		*/
	DIR* inside;							/*Pointer to nested directory, useful for recursion	*/
	
	int counter = 0;
	char temp[MAX_NAME_SIZE];				/*Max path to be stored 							*/

/*-------------------MODIFICATIONS-----------------------------------*/
	while( (direnpt = readdir(dir) ) != NULL){
        path_join(temp, path, direnpt -> d_name);	/*add current file to traversed path*/
     
        if(strcmp(direnpt -> d_name,".") == 0 || strcmp(direnpt -> d_name,"..") == 0)	/*ingore . and ..*/
            continue;
     	
        printf("%s\n", temp);						/*print file 			*/
        counter++;									/*count printed file 	*/
        
        if((direnpt -> d_type) == DT_DIR){			/*file is directory 	*/
            inside = opendir(temp);					/*open found directory 	*/
            
            if(inside != NULL)								/*If directory is empty just close it 			*/
               counter += print_dir(inside, temp);			/*recursively call print and add found files 	*/
          
            closedir(inside);	/*Close any found directory*/
        }
    }
/*-------------------END OF MODIFICATIONS-----------------------------*/
	return counter;				/*return the number of files/directories found*/
}

void deep_copy(DIR* src, char* src_path, char* dst_path){

	Dirent s_dir;	/*Pointer to source Directory 		*/
	DIR* s_inside;	/*Pointer to source nested directory*/

	DIR* dst;		/*Pointer to destination Directory 	*/

	int src_fd;		/*new file indicator 				*/
	
	char s_temp[MAX_NAME_SIZE];				/*Max path to be stored in src*/
	char d_temp[MAX_NAME_SIZE];				/*Max path to be stored in src*/
	
	while( (s_dir = readdir(src)) != NULL){

		path_join(s_temp, src_path, s_dir -> d_name);	/*add current file to traversed path*/
		path_join(d_temp, dst_path, s_dir -> d_name);	/*add current file to traversed path in !!!!destination path!!!!*/
		
		if(strcmp(s_dir -> d_name,".") == 0 || strcmp(s_dir -> d_name,"..") ==0 /*|| strcmp(s_dir -> d_name, dst_path) == 0*/)	/*ingore . and ..*/
            continue;

        if((s_dir -> d_type) == DT_DIR){			/*file is directory 	*/
            s_inside = opendir(s_temp);				/*open found directory 	*/

            if(mkdir(d_temp, MODE) == -1){
				perror("Error directory Creating");	/*Print upon failure 	*/
			}

			dst = opendir(d_temp);	/*open created directory in dst 		*/

			if(s_inside != NULL)
				deep_copy(s_inside, s_temp, d_temp);
                    
            closedir(s_inside);	/*Close any found directory in src*/
            closedir(dst);		/*Close any found directory in src*/
        }

      	else{
      		src_fd = open(s_temp, O_RDONLY, PERMS);
      		copy_file(d_temp, src_fd);     		
      	}
	}
	return;
}

void copy_file(char* d_path, int src_fd){
	int new_file, nread;
	char buffer[BUFFER_SIZE];

	if( (new_file = open(d_path, O_CREAT | O_RDWR , PERMS) ) == -1){
      	perror("File creating");
      	return;
    }

    while(nread = read(src_fd, buffer, BUFFER_SIZE) > 0){
    	if(write(new_file, buffer, nread) < nread){
			close(new_file);
			close(src_fd);
			return;
		}
	}
	close(new_file);
	close(src_fd);

	return;
}