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



// mkdir 
#include <sys/stat.h>

int mkdir(const char *pathname, mode_t mode);
/* pathname으로 새로운 디렉토리를 생성, 기존에 생성된 디렉토리의 하위에 디렉토리를 생성합니다.

e.g) b디렉토리가 만들어져 있지 않은 상황에서, mkdir("/a/b/c", 0777);은 오류가 발생함으로 
반드시 순서대로 mkdir("/a/b", 0777); mkdir("/a/b/c", 0777); 처럼 두번 호출해서 생성해야 함 

리턴!
    0 리턴 
    - 정상적으로 디렉토리가 생성되었음

    (-1) 리턴
    - 오류 발생 
*/

/* 파라미터
1) pathname:
- 생성하려는 디렉토리의 상대 또는 절대 경로 

2) mode: 
- 생성시 설정할 디렉토리에 대한 접근권한을 설정 

    1 search 권한 -> cd 명령어로 그 디렉토리에 들어갈 수 있느냐? 
    2 쓰기 권한
    4 읽기 권한 
    보통 8진수로 설정을함 0766 
*/

// 예제
(mkdir(argv[1], 0755) == -1);


// rmdir 
#include <unistd.h>

int rmdir(const char *pathname);
/* 비어 있는 디렉토리를 삭제합니다. 만약, 디렉토리에 다른 디렉토리나 파일이 있으면
삭제를 수행하지 않는다. UNIX/LINUX 표준 C에서는 비어 있지 않은 디렉토리 전체를 삭제 하는 함수는 제공하지 않음 

리턴!
    0 리턴
    - 정상적으로 디렉토리 삭제

    (-1) 리턴
    - 오류발생 
    */

/* 파라미터
1) pathname 
    - 삭제할 디렉토리에 대한 절대 상대 경로 
*/


// chdir
#include <unistd.h>

int chdir(const char * path);
/* 현재 작업 디렉토리를 변경

리턴!
    0 리턴
    - "프로세스"의 작업 디렉토리가 정상적으로 변경 

    (-1) 리턴
    - 오류가 발생하였으며, 기존의 작업디렉토리가 유지가 됨
*/

/* 파라미터
1) path :
    - 변경할 상대/절대 디렉토리 패쓰 
*/


// chdir 
#include <unistd.h>

char *getcwd(char *buf, size_t size);
/* 현재 작업 디렉토리의 절대 경로 명을 null-terminated 문자열로 얻습니다.
현재 작업 디렉토리를 저장할 buf의 size 가 작으면 NULL을 리턴함. 
만약 buf를 NULL로 설정하면 malloc을 통해서 할당된 메모리에 
작업디렉토리를 저장하여 리턴, 따라서 free를 호출하여 메모리 해제해줘야함 

리턴!
    NULL 아님
    - 정상적으로 현재 작업 디렉토리를 얻어왔스빈다.

    NULL
    - 현재 작업 디렉토리 정보는 얻는데 실패
*/

/* 파라미터
1) buf
    - 현재 작업 디렉토리를 저장할 buffer.
    - buf가 null 이면 getcwd는 malloc을 통해서 메모리를 할당한 후에 작업디렉토리 명을 문자열로 리턴
        -이 경우에는 반드시 free를 통해서 메모리를 해제해야함

2)size
    - buffer에 할당된 메모리의 크기 
*/


// opendir()
#include <sys/types.h>
#include <dirent.h>

DIR *opendir (const char *name);
/* 특정 디렉토리의 하위에 있는 파일명 및 디렉토리 명 등의 목록을 얻기 위한 DIR*를 생성합니다. 
opendir()은 절대경로 혹은 상대경로로  DIR*을 생성합니다. 

리턴!
     NULL이 아닌 값
     - 정상적으로 DIR* 이 생성되었습니다. 
     - DIR* 은 마치 FILE*와 비슷합니다. FILE*는 파일의 데이터를 읽기 위한 용도라면 DIR*은 디렉토리 하위에 있는 파일 또는 디렉토리명을 얻기 위해 생성 

     NULL
     - 오류가 발생
*/

/* 파라미터
1) name:
    -  디렉토리 정보를 얻고 싶은 디렉토리명
*/

// DIR 구조체
#include <dirent.h>
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

// readdir
#include <dirent.h>

struct dirent *readdir(DIR *dir);
/* 디렉토리의 하위에 잇는 파일 및 디렉토리 정보를 한 건 읽습니다. 
readdir()에 대해서 1회 호출에 1건의 정보를 리턴합니다. 
읽는 순서는 어떤 기준이 없으므로 기본적으로 sorting되어 있지 않습니다. 

리턴!
    NULL이 아닌 경우
    - 파일 또는 디렉토리 정보를 얻습니다.
    - linux struct dirent 구조체는 unix마다 다르므로 호환성을 유지하기 위해서는 d_name만 유효 

    NULL
    - 더 이상 읽을 정보가 없거나, 오류가 발생한 것 
*/

/* 파라미터
1) drip
    - opendir 을 통하여 생성된 DIR*
*/

#include <sys/types.h>
#include <dirent.h>

int closedir(DIR *dirp);
/* opendir으로 open한 DIR *에 대해, 더 이상 디렉토리 파일 목록을 검색하지 않을 경우에 
closedir(3)으로 DIR *를 close 한다. 

리턴!
    0
    - 정상적으로 close 
    
    (-1)
    - 오류가 발생
*/

/* 파라미터
1) dirp
    - opendir로 생성된 DIR* 
*/



