#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 512

//global
char buffer[BUFFER_SIZE];
int buffer_size = 0;
int buffer_pos = 0;

int ReadTextLine(int fd, char str[], int max_len)
{
	int i = 0;
	int j = 0;
	int ret = 0;

	// if current position is 0,
	// // reset buffer size and pos
	/* 	off_t lseek(int fd, off_t offset, int whence);
	offset 인자 -> 기준 위치로부터 상대적인 변위를 나타냄
	whence 인자 -> 기준위치를 나타냄 | SEEK_SET : 파일의 맨 처음 | SEEK_CUR : 파일의 현재 위치 | SEEK_END : 파일의 맨 끝

	해당 코드, 현재 fd의 위치가 0과 동일하다면, 버퍼사이즈와 버퍼의 pos를 0으로 초기화 
	*/
	if (lseek(fd, 0, SEEK_CUR) == 0)
		buffer_pos = buffer_size = 0;

	while (j < max_len - 1)
	{
		if (buffer_pos == buffer_size)
		{
			buffer[0] = 0;
			/* ssize_t read(int fd, void* buf, size_t nbytes)
			파일이 정상적으로 실행되었다면, 읽어들인 바이트 수를, 실패했다면 -1을 반환 함 */
			// 여기에서 read를 통해, 버퍼에 읽고 buffersize에 얼마나 읽었는지 받아옴
			buffer_size = read(fd, buffer, BUFFER_SIZE);
			// buffer_pos를 0으로 셋
			buffer_pos = 0;
		}

		// buffer_size가 0 인 것은, 어떤 라인(?)에서 읽어들일ㄹ 수 있는 걸 다 읽었다는거
		if (buffer_size == 0)
		{
			if (j == 0) // 동시에, j가 0으로 마지막 라인까지 도달한 경우에는 끝까지 읽엇음을 리턴함
				ret = EOF;
			break;
		}

		while (j < max_len - 2 && buffer_pos < buffer_size)
		{
			// 버퍼 size만큼 읽혔을 것이고, j에서 최대 설정한 값 까지(\0고려) 읽기를 수행함 
			// str에 buffer의 내용을 가져감 
			// char(10)은 현재 커서가 위치한 곳에서 아래로 한줄 내리는 기능을 담당함. 
			str[j++] = buffer[buffer_pos++]; 
			if (str[j - 1] == '\0' || str[j - 1] == 10)
			{		 // 만약 문장의 끝을 읽어낸 경우
				j--; // remove LF로, 커서를 현재 행의 다음 행으로 내리는 것을 지움(?)
				max_len = j; // to terminate outer loop
				break;		// break inner loop
			}
		}
	}
	str[j] = 0;
	return ret;
}

int main(void)
{
	int fd;
	int n = 0;
	char buff[BUFFER_SIZE];

	/* 이미 존재하는 파일을 열거나 새로운 파일을 생성하는 sys call함수.*/
	fd = open("/proc/cpuinfo", O_RDONLY);
	while (n != -1)
	{
		n = ReadTextLine(fd, buff, BUFFER_SIZE);

		char *p = strstr(buff, "cpu cores");
		if (p != NULL)
		{
			char *e = strstr(buff, ":");
			printf("# of processor cores = %s\n", e + 1);
			break;
		}
	}
	close(fd);

	fd = open("/proc/cpuinfo", O_RDONLY);
	while (n != -1)
	{
		n = ReadTextLine(fd, buff, BUFFER_SIZE);
		char *p = strstr(buff, "model name");
		if (p != NULL)
		{
			char *e = strstr(buff, ":");
			printf("CPU model = %s\n", e + 1);
			break;
		}
	}
	close(fd);

	fd = open("/proc/meminfo", O_RDONLY);
	while (n != -1)
	{
		n = ReadTextLine(fd, buff, BUFFER_SIZE);
		char *p = strstr(buff, "MemTotal");
		if (p != NULL)
		{
			char *e = strstr(buff, ":");
			printf("MemTotal = %s\n", e + 1);
			break;
		}
	}
	close(fd);

	fd = open("/proc/loadavg", O_RDONLY);
	ReadTextLine(fd, buff, BUFFER_SIZE);
	int i = 0;
	printf("loadavg1 = ");
	for (; buff[i] != ' '; i++)
	{
		printf("%c", buff[i]);
	}
	printf(", ");
	i++;

	printf("loadavg5 = ");
	for (; buff[i] != ' '; i++)
	{
		printf("%c", buff[i]);
	}
	printf(", ");
	i++;

	printf("loadavg15 = ");
	for (; buff[i] != ' '; i++)
	{
		printf("%c", buff[i]);
	}
	printf("\n");
	close(fd);

	//char *p = strstr(buffer, "cpu cores");
	//printf("%s",p);

	//	printf("# of processor cores = %d");
	//	printf("CPU model = %s");
	//	printf("MemTotal = %s");
	//	printf("loadavg1 = %s, loadavg5 = %s, loadavg15 = %s");

	return 0;
}
