#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 512

//global 
char buffer[BUFFER_SIZE];
int buffer_size =0;
int buffer_pos = 0;


int ReadTextLine(int fd, char str[], int max_len) {
	int i = 0;
	int j = 0;
	int ret = 0;

	// if current position is 0,
	// // reset buffer size and pos
	if(lseek(fd, 0, SEEK_CUR) == 0)
		buffer_pos = buffer_size = 0;

	while(j < max_len - 1){
	       	if(buffer_pos == buffer_size){
			buffer[0] = 0;
			buffer_size = read(fd, buffer, BUFFER_SIZE);
		       	buffer_pos = 0;
		}

		
		if(buffer_size == 0){	
			if(j == 0)
				ret = EOF;
		       	break;
		}

		while(j < max_len - 2 && buffer_pos < buffer_size){
			str[j++] = buffer[buffer_pos++];
			if(str[j - 1] == '\0' || str[j - 1] == 10){
				j--;
			       	max_len = j;
			       	break;
			}
		}
	}
	str[j] = 0;
       	return ret;
}

int main(void){
	int fd; 
	int  n=0;
	char buff[BUFFER_SIZE];

	fd = open("/proc/cpuinfo", O_RDONLY);
	while(n != -1){
		n = ReadTextLine(fd, buff, BUFFER_SIZE);
		
		char *p = strstr(buff, "cpu cores");
		if (p != NULL ){
			char *e = strstr(buff, ":");
			printf("# of processor cores = %s\n", e+1);
			break;
			}
	}
	close(fd);

	fd = open("/proc/cpuinfo", O_RDONLY);
	while(n != -1){
		n = ReadTextLine(fd, buff, BUFFER_SIZE);
		char *p = strstr(buff, "model name");
		if (p != NULL){
			char *e = strstr(buff, ":");
			printf("CPU model = %s\n", e+1);
			break;
		}
	}
	close(fd);

	fd = open("/proc/meminfo", O_RDONLY);
	while(n != -1){
		n = ReadTextLine(fd, buff, BUFFER_SIZE);
		char *p = strstr(buff, "MemTotal");
		if(p != NULL){
			char *e = strstr(buff, ":");
			printf("MemTotal = %s\n", e+1);
			break;
		}
	}
	close(fd);


	fd = open("/proc/loadavg", O_RDONLY);
	ReadTextLine(fd, buff, BUFFER_SIZE);
	int i = 0;
	printf("loadavg1 = ");
	for(; buff[i]!=' ' ; i++){
		printf("%c",buff[i]);
	}
	printf(", "); i++;

	printf("loadavg5 = ");
	for(; buff[i]!=' ' ; i++){
		printf("%c",buff[i]);
	}
	printf(", "); i++;

	printf("loadavg15 = ");
	for(; buff[i]!=' ' ; i++){
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

