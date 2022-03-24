#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#define PORT 8080
#define PORT1 8081

int main()
{
	struct sockaddr_in serv,cli;
	int sock;
	printf("fsdsfd");
	if((sock = socket(AF_INET, SOCK_DGRAM, 0))<0)
	{
		printf("Error Encountered");
		exit(0);
	}
	printf("Socket created successfully\n");
	
	memset(&serv, 0, sizeof(serv));
	memset(&cli, 0, sizeof(cli));
	
	serv.sin_addr.s_addr = htonl(INADDR_ANY);
	serv.sin_port = htons(PORT);
	serv.sin_family = AF_INET;
	
	cli.sin_addr.s_addr = inet_addr("127.0.0.1");
	cli.sin_port = htons(PORT1);
	cli.sin_family = AF_INET;
	
	if(bind(sock, (struct sockaddr*)&serv, sizeof(serv)) < 0)
	{
		printf("Error Encountered\n");
		exit(0);
	}
	printf("Socket Binded\n");
	
	char str[100];
	int n;
	int len = sizeof(cli);
	
	n = recvfrom(sock, (char *)str, 100, MSG_WAITALL, (struct sockaddr*)&cli, (socklen_t*) &len);
	str[n]='\0';
	printf("Received String is %s \n",str);
	
	int i=0, j=strlen(str)-1;
	char temp;
	while(i<j)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;j--;
	}
	sendto(sock, str, strlen(str), MSG_CONFIRM, (const struct sockaddr*)&cli, len);
	
	printf("String reversed and sent back to client\n");
	close(sock);
}
