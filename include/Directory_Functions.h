/*Directory operations prototypes*/

#pragma once 			/*include only once*/

#include <dirent.h>		/*DIR-related things*/

#define MODE 0777 		/*Permission*/

typedef struct dir_wrapper{
	DIR* src;				/*Pointer to source directory 	*/
	DIR* dst;				/*Pointer to destination		*/
}dir_index;

typedef dir_index* Pdir;				/*Pointer to struct data type 		*/

Pdir dir_index_create(void);			/*Create a dir_wrapper struct 		*/

void dir_index_destroy(Pdir dirs);		/*Destroy struct, free the memory 	*/

Pdir open_or_create_directories(char* src, char* dst);		/*Open directory, if not exists, create it*/

void close_directories(Pdir d);			/*Close directories, call dir_index_destroy() */

/*-------------Incoroporated struct dirent content--------------*/
// struct dirent {
// 	ino_t          d_ino;       /* Inode number 				*/
// 	off_t          d_off;       /* Not an offset; see below 	*/
// 	unsigned short d_reclen;    /* Length of this record 		*/
// 	unsigned char  d_type;      /* Type of file; not supported
//   	                             by all filesystem types 	*/
// 	char           d_name[256]; /* Null-terminated filename 	*/
// };

typedef struct dirent Dirent;	/*Declare pointer to struct 	*/
/*-------------End of struct dirent ----------------------------*/

void print_dir(DIR* dir);
