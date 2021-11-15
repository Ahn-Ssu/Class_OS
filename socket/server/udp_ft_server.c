#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>


#define BUF_SIZE 50
void error_handling(char *message);

int main(int argc, char *argv[])
{
	int serv_sd;
	FILE * fp;
	int read_cnt=0;
	struct sockaddr_in serv_adr, clnt_adr;
	socklen_t clnt_adr_sz;
	
	
	if(argc!=2) {
		printf("Usage: %s <port>\n", argv[0]);
		exit(1);
	}
	
	
	serv_sd=socket(PF_INET, SOCK_DGRAM, 0);
	if(serv_sd == -1 ) error_handling("UDP socket creation error");
	
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family=AF_INET;
	serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_adr.sin_port=htons(atoi(argv[1]));
	
	if(bind(serv_sd, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1) error_handling("bind() error");
	
	for(;;){ //for operating iterative server.
		clnt_adr_sz=sizeof(clnt_adr);

		// init receive buffer to receive data from the client
		char message[BUF_SIZE]=""; 

		// first, read file 'name' from the client and open (make) the file.
		recvfrom(serv_sd, message, BUF_SIZE, 0,
								(struct sockaddr*)&clnt_adr, &clnt_adr_sz);
		fp=fopen((void*)message, "wb"); 
		
		// for monitor
		int pkt_cnt, byte_cnt = 0;
		// second, read the file data from teh client and write in the file. 
		while(1){
			(read_cnt=recvfrom(serv_sd, message, BUF_SIZE, 0, (struct sockaddr*)&clnt_adr, &clnt_adr_sz));
			if (read_cnt == -1 ) error_handling("recvfrom() -1 error");

			byte_cnt += read_cnt;
			// monitoring code for problem 2-2
			printf("#recv ={%d}, recv size ={%d}, total recv size ={%d}, \n",pkt_cnt,read_cnt,byte_cnt);
			pkt_cnt++;
			if (read_cnt != strlen(message)){
			fwrite(message, 1, strlen(message), fp);
			break;
			} 
			fwrite(message, 1, read_cnt, fp);
		}
		
		// close file descriptor
		fclose(fp);
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
