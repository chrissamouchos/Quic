/*Directory operations prototypes*/

#pragma once 			/*include only once*/

#include <dirent.h>		/*DIR-related things*/

#include "Utils.h"

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

char* path_join(char* dest, const char* path,const char* suffix);	/*join strings together in path format 					*/

int print_dir(DIR* dir, char* path);								/*Print all content of given directory 					*/

// statistics deep_copy(DIR* src, char* src_path, char* dst_path);		/*Copy all content of src directory to dst directory 	*/

float copy_file(char* name, int BUFFSIZE);							/*copy file and return time elapsed 					*/

/*struct stat {
               dev_t     st_dev;         ID of device containing file
               ino_t     st_ino;         Inode number
               mode_t    st_mode;        File type and mode
               nlink_t   st_nlink;       Number of hard links
               uid_t     st_uid;         User ID of owner
               gid_t     st_gid;         Group ID of owner
               dev_t     st_rdev;        Device ID (if special file)
               off_t     st_size;        Total size, in bytes
               blksize_t st_blksize;     Block size for filesystem I/O
               blkcnt_t  st_blocks;      Number of 512B blocks allocated

               	Since Linux 2.6, the kernel supports nanosecond
                precision for the following timestamp fields.
                For the details before Linux 2.6, see NOTES.

               struct timespec st_atim;  Time of last access
               struct timespec st_mtim;  Time of last modification
               struct timespec st_ctim;  Time of last status change */

<<<<<<< HEAD
statistics update(DIR* src, char* src_path, char* dst_path);
=======
statistics update(DIR* src, char* src_path, char* dst_path); /*and/or copy files*/
>>>>>>> 3d56cefe7c2f34a359dd1d6434299d500692faf8
