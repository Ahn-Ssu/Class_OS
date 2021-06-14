/* list 
1)
    mkdir()
    rmdir()
    chdir()
    getcwd() 
2) 
    opendir()
    readdir()
    closedir()

*/

#include <sys/stat.h>   // for mkdir()
#include <unistd.h>     // for rmdir(), chdir(), *getcwd

int mkdir(const char *pathname, mode_t mode);
int rmdir(const char *pathname);
int chdir(const char * path);
char *getcwd(char *buf, size_t size);

#include <sys/types.h>  // for opendir(), closedir()
#include <dirent.h>     // for opendir(), readdir(), closedir(), DIR, dirent
DIR *opendir (const char *name);
struct dirent *readdir(DIR *dir);
int closedir(DIR *dirp);


struct dirent
{
	long		    d_ino;		
	unsigned short	d_reclen;	
	unsigned short	d_namlen;	/* Length of name in d_name. */
	char		    d_name[260]; /* [FILENAME_MAX] */ /* File name. */
};


typedef struct
{
	
	struct _finddata_t	dd_dta; /* disk transfer area for this dir */
	struct dirent		dd_dir;
	
	intptr_t		dd_handle;  /* _findnext handle */

	/*
	 * Status of search:
	 *   0 = not started yet (next entry to read is first entry)
	 *  -1 = off the end
	 *   positive = 0 based index of next entry
	 */
	int			dd_stat;

	char			dd_name[1];
} DIR;
