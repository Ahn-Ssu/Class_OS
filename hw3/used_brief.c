/* list 
1)
    time(), localtime(), struct tm
    gettimeofday(), struct timeval
    usleep()

2)
    getuid(), getpid(), getppid()
    uname(), struct utsname
    sysinfo(), struct sysinfo
    access(), stat(), struct stat

3)
    fork()
    execvp()
*/

#include <time.h> 		// for time(), localtime()
#include <sys/time.h> 	// for gettimeofday()
#include <unistd.h>


time_t time(time_t *tloc);
struct tm *localtime(const time_t *timer);
int gettimeofday(struct timeval *restrict tv, struct timezone *restrict tz);
int usleep(useconds_t usec);

struct tm

    struct tm
{
    int tm_sec;   /* 초: 0 ~ 59,(60,61윤초)*/
    int tm_min;   /* 분: 0 ~ 59*/
    int tm_hour;  /* 시: 0 ~ 23 */
    int tm_mday;  /* 일: 1 ~ 31 */
    int tm_mon;   /* 월: 0 ~ 11 (따라서 +1해야 함*/
    int tm_year;  /* 년: + 1900을 해야 함*/
    int tm_wday;  /* 요일: 0 ~ 6 */
    int tm_yday;  /* 1월1일부터 경과된 날수: 0 ~ 365 */
    int tm_isdst; /* daylight적용여부: 0:적용안됨, -값:유효하지 않음 +값:적용시간*/
};

struct timeval
{
    time_t tv_sec;      // seconds
    susecond_t tv_usec; // microseconds
}


#include <unistd.h> 	// for getuid(), getpid(), getppid()

uid_t getuid(void);
pid_t getpid(void);
pid_t getppid(void);

#include <sys/utsname.h> // for uname()

int uname(struct utsname *buf);

struct utsname
{
    char sysname[];  /* Operating system name (e.g., "Linux") */
    char nodename[]; /* Name within "some implementation-defined
                                     network" */
    char release[];  /* Operating system release
                                     (e.g., "2.6.28") */
    char version[];  /* Operating system version */
    char machine[];  /* Hardware identifier */
#ifdef _GNU_SOURCE
    char domainname[]; /* NIS or YP domain name */
#endif
};

#include <sys/sysinfo.h> // for sysinfo()

int sysinfo(struct sysinfo *info);

struct sysinfo {
               long uptime;             /* Seconds since boot */
               unsigned long loads[3];  /* 1, 5, and 15 minute load averages */
               unsigned long totalram;  /* Total usable main memory size */
               unsigned long freeram;   /* Available memory size */
               unsigned long sharedram; /* Amount of shared memory */
               unsigned long bufferram; /* Memory used by buffers */
               unsigned long totalswap; /* Total swap space size */
               unsigned long freeswap;  /* Swap space still available */
               unsigned short procs;    /* Number of current processes */
               unsigned long totalhigh; /* Total high memory size */
               unsigned long freehigh;  /* Available high memory size */
               unsigned int mem_unit;   /* Memory unit size in bytes */
               char _f[20-2*sizeof(long)-sizeof(int)];
                                        /* Padding to 64 bytes */
           };


#include <unistd.h>  	// for access()
#include <sys/types.h>  // for stat(), stat struct
#include <sys/stat.h>	// for stat(), stat struct

int access(const char *pathname, int mode);
int stat(const char *restrict pathname, struct stat *restrict statbuf);

struct stat { 
    dev_t st_dev; /* ID of device containing file */ 
    ino_t st_ino; /* inode number */ 
    mode_t st_mode; /* 파일의 종류 및 접근권한 */ 
    nlink_t st_nlink; /* hardlink 된 횟수 */ 
    uid_t st_uid; /* 파일의 owner */ 
    gid_t st_gid; /* group ID of owner */ 
    dev_t st_rdev; /* device ID (if special file) */ 
    off_t st_size; /* 파일의 크기(bytes) */ 
    blksize_t st_blksize; /* blocksize for file system I/O */ 
    blkcnt_t st_blocks; /* number of 512B blocks allocated */ 
    time_t st_atime; /* time of last access */ 
    time_t st_mtime; /* time of last modification */ 
    time_t st_ctime; /* time of last status change */ };


// fork
#include <unistd.h> 	// for fork(), execvp()

pid_t fork(void);
int execvp(const char*file, char *const argv[]);