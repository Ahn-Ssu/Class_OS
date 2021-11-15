#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <time.h>

#define BUF_SIZE 10
void error_handling(char *message);

int main(int argc, char *argv[])
{
	int sd;
	FILE *fp;
	char buf[BUF_SIZE]="";
	int read_cnt;
	int send_size_cnt=0;
	struct sockaddr_in serv_adr;
	struct timeval start_time, end_time;

	// modified condition for getting filename args 
	if(argc!=4) { 
		printf("Usage: %s <IP> <port> <filename>\n", argv[0]);
		exit(1);
	}

	sd=socket(PF_INET, SOCK_STREAM, 0);
	if(sd == -1 ) error_handling("TCP socket creation error");

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family=AF_INET;
	serv_adr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_adr.sin_port=htons(atoi(argv[2]));

	connect(sd, (struct sockaddr*)&serv_adr, sizeof(serv_adr));

	// time record
	gettimeofday(&start_time, NULL);
	// open src file of the client side
	fp=fopen(argv[3], "rb");

	// first, send the file name to the server
	// and record length of file name to calculate throughput
	// write(sd, argv[3], strlen(argv[3])); 
	send(sd, argv[3], strlen(argv[3]), 0);
	send_size_cnt += strlen(argv[3]);

	// second, send the file data to the server
	int pkt_cnt = 0;
	while(1)
	{
		read_cnt=fread((void*)buf, 1, BUF_SIZE, fp);
		send_size_cnt += read_cnt; // record length of file name to calculate throughput
		pkt_cnt++;

		if(read_cnt<BUF_SIZE)
		{
			// write(sd, buf, read_cnt);
			send(sd, buf, read_cnt, 0);
			break;
		}
		// write(sd, buf, BUF_SIZE);
		send(sd, buf, BUF_SIZE, 0);
		printf("#send ={%d}, send size ={%d}, total send size ={%d}, \n",pkt_cnt,read_cnt,send_size_cnt);
	}
	printf("total pkt number : %d\n", pkt_cnt);

	fclose(fp);
	close(sd);

	gettimeofday(&end_time, NULL);
	
	float elapsed = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 1000000.F;
	printf("elapsed time = %f sec, throughput = %f BPS\n", elapsed, send_size_cnt/elapsed);

	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}