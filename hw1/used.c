/* open(2) */

#include <sys/stat.h> 
#include <fcntl.h>

int open(const char *pathname, int flags);
int open(const char *pathname, int flags, mode_t mode);

/* 이미 존재하는 파일을 열거나 새로운 파일을 생성하는 sys call 함수, 
open(2)로 열려진 파일은 read(2), write(2), lseek(2), close(2)랑 사용 가능 

fd의 int 값을 리턴하거나  -1 이하인 경우 에러가 발생 */

/* 파라미터 
1) pathname :
- 오픈할 파일명에 대한 절대경로/상대경로

2) flags:
- 파일을 어떤 목적으로 open할 것인지, 파일의 초기화를 할 지 여부등을 지정함
- flag 값은 O_RDONLY, O_WRONLY, O_RDWR 중 하나는 반드시 설정되어야 합니다. 

    O_RDONLY : 파일을 읽기 전용으로 오픈
    O_WRONLY : 파일을 쓰기 전용으로 오픈
    O_RDWR : 파일을 읽기/쓰기 모두 할 수 있음 

    그 밖에 옵션들은 bit or 연산으로 여러개 설정 가능 "|"

    O_APPEND : 파일을 append mode로 오픈함, 이렇게 열면 오직 파일 끝에만 작성할 수 있음 
    O_CREAT : 파일이 존재하지 않으면 새로 만드는 설정, 반드시 param 3개 짜리 open으로 사용해야함  


3) mode
- 파일에 대한 access 권한을 설정
- 파일 접근 권한은 umask(2) 값의 영향을 받으며, (mode & ~umask) 의 값으로 권한이 설정
- mode 의 값은 아래의 상수들을 bit-or 연산으로 설정이 가능 

    7 읽기 쓰기 실행
    6 읽기 쓰기 
    4 읽기
    2 쓰기
    1 실행 
    보통 0666으로 설정
*/

// 예제
// // 파일 열기 
fd = open("/proc/cpuinfo", O_RDONLY); 
// // 유사 예제, POSIX 메모리 열기 
shm_fd = shm_open(SHM_FILE, O_CREAT | O_RDWR, 0666);




/* close(2) */
#include <unistd.h>

int close(int fd);

/* open(2) 또는 creat(2)를 통해 열은 파일을 닫음 

정상적으로 파일을 닫은 경우 0을 리턴하며 
오류가 발생한 경우에는 -1을 리턴한다 */

/* 파라미터 
1) fd 
- open(2) 또는 creat(2)를 통해서 생성한 file descripotr.  
*/

// 예제
// // 단순 사용
close(fd);



/* read(2) */
#include <unistd.h>

ssize_t read(int fd, void *buf, size_t count);
/* open(2), creat(2),... 등으로 생성한 file descripotr로 부터 데이터를 읽음 
파일을 읽으면 읽은 size만큼 파일의 다음 읽을 위치가 이동이 된다. 
읽을 위치가 피일의 끝에 도달하면 더 이상 읽을 데이터가 없으므로 0을 리턴

0보다 큰수의 리턴
- 실제로 읽은 데이터 byte수
- 일반적으로 size_t count와 같은 값을 return하지만, 보다 작은 경우에는 EOF에 도달 한 정도. 

0을 리턴
- EOF 에 도달하여 더 이상 읽을 자료가 없는 경우

(-1)을 리턴
- 오류가 발생한 경우 
*/

/* 파라미터
1) fd :
- open() 등으로 얻어낸 file descriptor 

2) buf :
- 읽을 데이터를 저장할 메모리 영역(buffer)

3) count :
- 읽을 size (byte 단위) 
*/

// 예제
// // readTextLine 
read(fd, buffer, BUFFER_SIZE);


/* read(2) */
#include <unistd.h>

ssize_t write(int fd, const void *buf, size_t count);
/* open(), creat() 등으로 생성한 파일 디스크립터로 데이터 쓰기 또는 전송을 수행함 
파일에 쓰기를 하면 파일의 쓰기 또는 읽기 위치가 쓴 size만큼 뒤로 이동을 함. 
wirte(2) 함수는 -1이 리턴되지 않는 한 , 웬만하면 count만큼 정상적으로 write됨 
+ O_APPEND로 파일을 연경우, 현재위치가 아닌 항상 파일의 끝에 쓰기가 발생 함 

0보다 큰 값 리턴
- 실제로 쓴 데이터의 byte 수
- count와 같은 크기의 값을 리턴하지만, 작은 경우에는 signal이 발생하였거나, 쓰기 공간이 부족한 경우

0 리턴
- 오류가 발생하지는 않았지만, 파일에 쓰지 못함 

(-1) 리턴
- 오류가 발생  */

/* 파라미터
1) fd:
- open(), creat() 등을 통하여 정상적으로 open한 파일 디스크립터 

2) buf: 
- 쓰기를 할 데이터 메모리 영역 (buffer)

3) count : 
- 쓸 데이터 size (byte 수)
*/


/*
ssize_t, size_t, pid_t 는 고전적인(primitive) 자료형이라 한다. 
일반적으로 헤더에 선언되어 있는데, 사실 C의 typedef 선언을 통해서 정의되어 있다.
즉 새롭게 등장한 것이 아니라, 잘 알고 있는 int, float, long과 같은 기본 자료형을 가지고, 
이름만 바꾸어 정의해 놓은 것이다. 이러한 자료형들은 꽤 오래 전부터 존재하고 있엇다.
그렇다면 도대체 왜 이러한 것을 정의해 놓고 사용하는 것일까?? 
int, short, float 라고 하면 사용하기 편할 텐데...
 
지금은 int가 32비트라고 한다. 보편적으로 사용되는 운영체제와 컴퓨터가 32비트이기 때문이다. 
과거 16비트 시설에는 int가 16비트였고 곧 64비트 시대가 도래 할 것이다. 
즉, 시스템에 따라서 자료형의 표현 방식이 틀려지므로 내가 구현한 프로그램을 다른 시스템에서 
실행 시키기 위해서는 코드의 수정 자체가 불가피하다.
 
그러나 4바이트의 자료형이 필요한 곳에, 지금 처럼 헤더파일에 unsigned int를 size_t로 정의해 
놓고 쓰게 되면, 나중에 시스템이 변경되어서 unsigned int가 더 이상 4바이트를 나타내지 않게 
되었을 때, 4바이트를 나타내는 다른 적절한 자료형을 가지고 헤더파일에 선언되어 있는 size_t를 
재정의해 주기만 하면 된다.
 
즉 소스 코드는 바꾸지 않고 컴파일만 다시 한번 하면 새로운 시스템에서 잘 돌아가게 된다는 것이다.
이것이 int, double, short, float과 같은 특정 자료형에 종속되지 않도록, 새로운 이름의 자료형을 정의해 주는 이유가 된다.
 
보통은 다음과 같은 형식으로 정의한다.
size_t : unsigned 형태의 변수 선언
ssize_t : signed 형태의 변수 선언
pid_t : Process ID를 표현하기 위해서 사용
[출처] ssize_t, size_t, pid_t 타입 개념잡기|작성자 몽키몽키*/