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

// time
#include <time.h>

time_t time(time_t *tloc);
/* time()은 1970-01-01 00:00:00 이후부터 현재까지 경과된 초단위 값을 리턴
t가 NULL이 아니면 t에 결과 값을 채우고 그 값을 리턴, NULL이면 경과된 초단위의 값만 리턴

리턴!
    0 이상
        - 1970-01-01 00:00:00 이후부터 현재까지의 경과 초

    (-1)
    - 오류가 발생하였음
*/

/* 파라미터
1) t:
    - 현재 시간을 저장할 데이터 버퍼
    - NULL이면 입력부는 무시된다. 
*/

time_t
/* C++ 에서는 int64로 typedef해서 사용 중 */

// localtime
#include <time.h>

    struct tm *
    localtime(const time_t *timer);
/* localtime() 함수는 time_t tpye의 시간을 지역 시간의 struct tm tpye으로 변환하는 함수 
time_t type은 주로 time 함수를 이용하여 얻습니다.

이 함수는 내부적으로 local static struct tm 변수에 데이터를 저장하고 있기 때문에 멀티 스레드 환경에서 문제 발생 가능
localtime을 또 호출하면 값이 바뀌므로 다른 변수에 데이터를 복사하거나 localtime을 호출하기 전에 데이터 처리를 끝내야함.

리턴!
    NULL 아님
    - 정상적으로 변환이 되었으며, 내부적으로 static 변수를 리턴 함으로 localtime을 또 호출할 때 까지
        유효하며, 바로 사용하거나 다른 변수에 복제를 해야 한다. 
    -thread-safe한 함수가 아니므로 멀티스레드 환경에서는 반드시 localtime_r을 사용하도록 합니다. 

    NULL
    - 오류발생
*/

/* 파라미터
1) timer
    - 주로 time() 함수의 리턴 갑싱나 gettimeofday()의 struct timeval 의 tv_sec등 초단위의 시간을 저장한 변수 
*/

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

// gettimeofday()
#include <sys/time.h>

int gettimeofday(struct timeval *restrict tv, struct timezone *restrict tz);
/* gettimeofday() 함수는 1970-01-01 00:00:00 이후의 현재까지의 경과된 초와 micro초 (백만분의 1) 값을 얻는 함수 
정밀한 시간 정보가 필요한 경우에 사용하는데, tz는 사용하지 않음으로 무시가 된다. 

리턴!
    0
        - 정상적으로 조회가 된 상태 
    (-1)
        - 오류가 발생함.
*/

/* 파라미터
1) tv
    - 1970-01-01 이후 경과된 초와 micro를 저장할 buffer 
*/

struct timeval
{
    time_t tv_sec;      // seconds
    susecond_t tv_usec; // microseconds
}

#include <unistd.h>

int
usleep(useconds_t usec);
/* usleep()은 설정된 micro초 동안 대기 상태가 됨 

리턴!
    0
    - usleep() 함수가 정상적으로 종료 

    (-1)
    - 처리도중 오류가 발생하였음
*/

/* 파라미터
1) usec
    - 대기할 시간(micro초 단위, 100만분의 1초 1000*1000)
*/

// getuid()
#include <unistd.h>

uid_t getuid(void);
/* getuid() sys call 함수는 현재 실행 중인 프로세스의 real user id (uid) 를 얻는 함수입니다. 
이 uid는 계정이 생성될 때에 할당되는 user별로 unique한 번호 입니다. 
프로세스의 real uid는 명령어를 실행한 계정을 의미 

리턴!
    real uid()
    - 항상 성공함 
*/

// getpid()
#include <unistd.h>

pid_t getpid(void);
pid_t getppid(void);
/* getpid 현재 프로세스의 프로세스 ID를 얻는 함수입ㄴ디ㅏ. 프로세스 ID는 프로세스가 생성된 순서대로 
번호를 순차적으로 할당합니다. 먼저 실행된 process가 종료되었다고 해서 비어 있는 프로세스 ID를 사용하지 않습니다. 
그리고 할당할 수 있는, 최대 프로세스 ID에 도달하면 다시 1번 부터 사용하지 않는 프로세스 ID를 찾아서 할당해 나감 

리턴
    양수
    - 현재 프로세스 ID
    - 이 함수는 항상 정상적으로 실행 됨 
*/

#include <unistd.h>

pid_t getppid(void);
/* 부모 프로세스의 ID를 얻는 함수, 부모 프로세스가 fork를 할때에 자식 프로세스가 생성되며, 
생성된 자식 프로세스에서는 생성한 부모 프로세스를 언제든지 조회할 수 있음. 
getppid()는 이 부모 프로세스의 ID를 얻는 함수. 그러나 부모 프로세스가 자식보다 먼저 종료되면
자식 프로세스의 부모프로세스는 init으로 변경되며, ppid는 1로 변경이 됩니다. 

리턴
    양수
    - 부모 프로세스의 ID
    - 이 함수는 항상 성공 
*/

// uname
#include <sys/utsname.h>

int uname(struct utsname *buf);
/* 현재의 커널에 대한 이름과 정보를 얻는 함수 전달한 buf에 내용이 담긴다. 

리턴!
    0   
    - 성공의 리턴

    (-1)
    - 에러가 발생, 보통 buf가 적절하지 않은 경우 발생 
*/

/* 파라미터
1) buf
    - utsname struct이다. 
*/

// utsname
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

// sysinfo
#include <sys/sysinfo.h>

int sysinfo(struct sysinfo *info);
/* 시스템 정보를 얻는 함수, 특정 메모리 등등에 대한 정보가 있음 

리턴
    0
    - 성공의 리턴 

    (-1)
    - 에러가 발생한 경우 
*/

/* 파라미터
1) sysinfo struct 
    - 정보를 담을 버퍼성격의 구조체 
*/

// sysinfo struct
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


// access()
#include <unistd.h>

int access(const char *pathname, int mode);
/* 주어진 파일에 대한 유저의 권한을 확인하는 함수이다. 
F_OK, R_OK, W_OK, X_OK 가 있는데, F_OK는 파일이 존재하는지에 대한 테스트이다.

리턴!
    0
    - 성공의 리턴이다. 

    -1
    - 권한이 없거나, 파일이 없거나, 에러가 나면 리턴됨 
*/

/*파라미터
1) pathname
    - 권한을 확인할 파일 
2) 
    - 확인할 모드 
*/

// stat
#include <sys/types.h>
#include <sys/stat.h>

int stat(const char *restrict pathname, struct stat *restrict statbuf);
/* 파일의 크기, 파일의 권한, 파일의 생성일시, 등 파일의 상태나 파일의 정보를 얻는 함수
stat() 함수는 symbolic link인 파일을 path로 넘기면 그 원본 파일의 정보를 얻습니다. 

리턴!
    0
    - 성공의 리턴, 정상적으로 파일의 정보를 조회하였습니다. 

    (-1)
    - 오류가 발생하였음 
*/

/* 파라미터
1) path
    - 파일 명 또는 파일에 대한 상대경로 또는 절대경로

2) buf
    - 파일의 상태 및 정보를 저장할 구조체 
*/

// stat struct 
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
#include <unistd.h>

pid_t fork(void);
/* 현재 실행중인 프로세스와 동일한 기능을 하는 새로운 프로세스를 생성합니다. 

새로운 프로세스를 자식프로세스라고 하고, 기존의 프로세스를 부모프로세스라고 합니다.
부모 프로세스와 자식 프로세스는 아래의 내용이외에는 거의 동일

    - 프로세스 ID가 서로 다르며, 부모 프로세스 ID도 다름
    - 자식프로세스의 PPID는 부모 프로세스의 PID와 같습니다.
    - 외 기타


리턴!
    양수
    - fork()에서 1 이상을 리턴 받은 프로세스는 부모 프로세스입니다. 리턴 값은 자식프로세스 ID입니다. 
        즉, 부모는 방금 생성한 자식 프로세스 ID를 알 필요가 있기 때문에 return을 받습니다. 
        자식 프로세스의 종료를 대기하거나 시그널에 대한 처리를 위해서 필요합니다. 
        또한 자식 프로세스 ID는 여러개가 있을 수 있기 때문에 자식프로세스 ID를 얻는 함수가 없습니다. 

    0
    - fork에서 0을 리턴 받은 프로세스는 자식 프로세스입니다. 
        부모 프로세스 ID는 getppid를 통해서 얻을 수 있기 때문에 0을 리턴 받습니다. 
    
    (-1)
    - 오류가 발생하여서 자식프로세스가 생성되지 않음 
*/

// execvp
#include <unistd.h>

int execvp(const char*file, char *const argv[]);
/* 실행가능한 파일인 file의 실행코드를 현재 프로세스에 적재하여 기존의 실행코드와 교체하여 새로운 기능으로 실행합니다. 
즉, 현재 실행되는 프로그램의 기능은 없어지고, file프로그램을 메모리에 loading하여 처음부터 실행합니다. 
file은 명령어 또는 실행가능 한 파일로 환경변수 PATH에 디렉토리가 포함되어 있으면, 명령어만 설정 가능합니다. 

리턴!
    없음
    - 정상적으로 처리되면  execv(3) 다음 로직은 실행할 수 없습니다. 
        왜냐하면 이미 다른 프로그램이 되었기 때문입니다. 
        
    (-1)
    - binary 교체가 실패하였으며, 상세한 오류 내용은 errno 전역 변수에 설정됩니다. */

    