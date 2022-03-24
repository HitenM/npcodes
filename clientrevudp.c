#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define PORT 8080
#define PORT1 8081

int main()
{
	struct sockaddr_in serv,cli;
	
	int sock;
	
	if((sock = socket(AF_INET, SOCK_DGRAM, 0))==0)
	{
		printf("sdf");
		exit(0);
	}
	
	
	memset(&serv, 0, sizeof(serv));
	memset(&cli, 0, sizeof(cli));
	
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv.sin_port = htons(PORT);
	serv.sin_family = AF_INET;
	
	cli.sin_addr.s_addr = inet_addr("127.0.0.1");
	cli.sin_port = htons(PORT1);
	cli.sin_family = AF_INET;
	char *str = "hello";
	
	sendto(sock, str, strlen(str), 0, (const struct sockaddr*)&serv, sizeof(serv));
	int len;
	len = sizeof(cli);
	char buffer[100];
	recvfrom(sock, (char *)buffer, 100, 0, (struct sockaddr*)&cli, (socklen_t*) &len);
	printf("reversed:	%s", buffer);
}
