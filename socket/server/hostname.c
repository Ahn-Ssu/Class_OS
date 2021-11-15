#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>


int main(int argc, char *argv[])
{
	
	if(argc!=2) {
		printf("Usage: %s <URL>\n", argv[0]);
		exit(1);
	}

	struct hostent *info;

	info = gethostbyname(argv[1]);

	int i;
	printf("Official name: %s\n", info->h_name);
	for(i = 0 ; info->h_aliases[i]; i++) 
		printf("Aliases %d: %s\n", i+1, info->h_aliases[i]);
	printf("Address type: %s\n", info->h_addrtype==AF_INET? "AF_INET" : "AF_INET6");
	for(i = 0 ; info->h_addr_list[i]; i++) 
		printf("Ip addr %d: %s\n", i+1, inet_ntoa(*(struct in_addr*)info->h_addr_list[i]));
	

	
	
	return 0;
}
