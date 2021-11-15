#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>


#define BUF_SIZE 3
void error_handling(char *message);

int main(int argc, char *argv[])
{
	int serv_sd, clnt_sd;
	FILE * fp;
	int read_cnt;
	
	struct sockaddr_in serv_adr, clnt_adr;
	socklen_t clnt_adr_sz;
	
	if(argc!=2) {
		printf("Usage: %s <port>\n", argv[0]);
		exit(1);
	}
	
	
	serv_sd=socket(PF_INET, SOCK_STREAM, 0);
	if(serv_sd == -1 ) error_handling("TCP socket creation error");
	
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family=AF_INET;
	serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_adr.sin_port=htons(atoi(argv[1]));
	
	bind(serv_sd, (struct sockaddr*)&serv_adr, sizeof(serv_adr));
	listen(serv_sd, 5); 
	
	clnt_adr_sz=sizeof(clnt_adr);
	for(;;){ //for operating iterative server.
		clnt_sd=accept(serv_sd, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);

		// executing error handler by connection fail.
		if (clnt_sd < 0 ) error_handling("accept error"); 

		// init receive buffer to receive data from the client
		char buf[BUF_SIZE]=""; 

		// first, read file 'name' from the client and open (make) the file.
		read(clnt_sd, buf, BUF_SIZE);
		fp=fopen((void*)buf, "wb"); 
		
		int pkt_cnt, byte_cnt= 0;
		// second, read the file data from teh client and write in the file. 
		// while((read_cnt=read(clnt_sd, buf, BUF_SIZE ))!=0)
		// 	fwrite((void*)buf, 1, read_cnt, fp);
		while((read_cnt=recv(clnt_sd, buf, BUF_SIZE,0 ))!=0){
			pkt_cnt++;byte_cnt+=read_cnt;
			printf("#recv ={%d}, recv size ={%d}, total recv size ={%d}, \n",pkt_cnt,read_cnt,byte_cnt);
			fwrite((void*)buf, 1, read_cnt, fp);
		}

		
		// close file descriptor and only connected sokect for iterative attribute
		fclose(fp);
		close(clnt_sd); 
		printf("total recv number : %d\n", pkt_cnt);
		printf("\n");
	}
	
	close(serv_sd);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
