/* list 
1)
    -- POSIX Shared Memory 
    shm_open()
    shm_unlink()
    mmap()
    munmmap()
*/


// shm_open()
#include <sys/mman.h>
#include <sys/stat.h>       /* For mode constants */
#include <fcntl.h>          /* For 0_* constants */

int shm_open(const char *name, int oflag, mode_t mode);
/* -lrt 옵션과 함께  link를 수행할 수 있다.  POSIX 방식의 공유 메모리 객체를 생성한다. 
만약에 존재하는 경우에는,  open 을 수행한다. 

리턴!
    양수 
    -  file descriptor 번호를 리턴한다. 

    (-1)
    - 어떠한 에러가 발생하였고, errno 에 기록이 되어 있다.
*/

/* 파라미터
1) name 
    - open하거나 생성할 file의 이름이다. 없는 경우 oflag에 O_CREAT 옵션을 통해 생성하도록 유도할 수 있다. 

2) oflag
    - 공유 메모리 객체를 얻을 때 사용할 방법에 대한 플래그 이다.
    -  O_RDONLY, O_RDWR, O_CREAT 등이 존재하며, O_CREAT 는 비트 or 연산자로 옵션을 제공한다. 

3) mode
    - 파일의 chmod 를 주는 것 같다...!
    - 보통 예제들과 과제 수행에서 0666으로 줬었음 
*/

// shm_unlink()
#include <sys/mman.h>
#include <sys/stat.h>       /* For mode constants */
#include <fcntl.h>          /* For 0_* constants */

int shm_unlink(const char *name);
/* -lrt 옵션과 함께 link에 대한 수행을 할 수 있다. POSIX 방식으로 얻은 공유 메모리 객체의 링크를 끊어버림 

리턴!
    0
    - 정상적으로 unlink 된 경우 0을 리턴한다.

    (-1)
    - 과정 중에 오류가 발생했다. 
*/

/* 파라미터
1) name
    - shm_open 에 사용 되었던 name을 그대로 사용한다.  shm_open으로 제공한 파일에 대해서 동작을 수행함 
*/

// mmap()
#include <sys/mman.h>

void *mmap(void  *addr, size_t length, int prot, int flags, int fd, off_t offset);
/* 어떠한 파일이나 디바이스를 메모리에 맵핑하는 함수  

mmap() 호출은 파일 디스크립터 fd가 가르키는 객체를 파일에서 offset 바이트를 기준으로 length로 제공한 바이트만큼 메모리에 맵핑 하도록 커널에 요청한다.
addr를 넘길 경우, 메모리에서 해당 시작 주소를 선호한다고 커널에게 알린다. 접근 권한은 prot에 지정을 하고, 추가적인 동작 방식은 flags에 지정을 한다.

리턴
    성공
    - 매핑된 지역을 가르키는 pointer를 리턴을 해준다. 
    - 맵핑이 시작하는 실제 메모리 주소라고도 함
    
    실패
    -MAP_FAILED라는 포인터((void *) -1)가 리턴이 된다.*/

/* 파라미터
1) addr
    - 커널에게 파일을 어디에 맵핑하면 좋을지 제안하는 값 (보통 0을 사용한다)

2) length
    - 맵핑시킬 메모리 영역의 길이이다. ( byte 단위)

3) prot
    -맵핑에 원하는 메모리 보호정책 
        PROT_READ : 읽기 가능한 페이지
        PROT_WRITE : 쓰기 가능한 페이지
        PROT_EXEC : 실행 가능한 페이지
        PROT_NONE : 접근할 수 없는 페이지 

4)flags
    -맵핑 유형과 동작 구성 요소
        MAP_SHARED : 동일 파일을 맵핑한 모든 프로세스들이 공유. 객체 접근에 대한 동기하를 위해 msync, munmap을 사용
        MAP_PRIVATE : 맵핑을 공유하지 않아, 파일은 쓰기 후 복사로 맵핑되며, 변경된 메모리 속성은 실제 파일에는 반영되지 않음 
5) fd
    - shm_open으로 얻은 shm_fd
6) offset
    - 맵핑 할때, len의 시작점을 지정함 
*/
// munmmap()
#include <sys/mman.h>

int munmap(void *addr, size_t length);
/* mmap()으로 만들어진 맵핑을 제거하기 위한 시스템 호출, addr에서 시작하는 프로세스 주소 공간에 위치한 페이지를 포함하는
모든 맵핑을 제거한다. 이 영역은 length 바이트 만큼 계속해서 이어져야하며, 페이지에 정렬되어 있어야한다.


리턴!
    성공
    - 0을 리턴함 
    
    실패
    - (-1)을 리턴함  */