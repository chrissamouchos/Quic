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

typedef struct dirent* Dirent;	/*Declare pointer to struct 	*/

/*DT_BLK This is a block device.

              DT_CHR 	This is a character device.

              DT_DIR 	This is a directory.

              DT_FIFO 	This is a named pipe (FIFO).

              DT_LNK 	This is a symbolic link.

              DT_REG 	This is a regular file.

              DT_SOCK	This is a UNIX domain socket.

              DT_UNKNOWN
                     The file type could not be determined */

/*-------------End of struct dirent ----------------------------*/

char* path_join(char* dest, const char* path,const char* suffix);	/*join strings together in path format 	*/

int print_dir(DIR* dir, char* path);	/*Print all content of given directory 					*/

void deep_copy(DIR* src, char* src_path, char* dst_path);					/*Copy all content of src directory to dst directory 	*/

void copy_file(char* name, int BUFFSIZE);