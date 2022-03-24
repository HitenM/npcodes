#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>

int main()
{
	int network_socket=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in address;
	address.sin_family=AF_INET;
	address.sin_port=htons(9069);
	address.sin_addr.s_addr=INADDR_ANY;

	connect(network_socket,(struct sockaddr*) &address,sizeof(address));

	char datas[256];
	char datar[256];
	char ex[256];
	char ss[256];
	char choice[1];
	while(1)
	{
		int e=read(network_socket,ex,sizeof(ex));
		ex[e]='\0';
		printf("%s",ex);
		scanf("%s",choice);
		write(network_socket,choice,sizeof(choice));
		if(choice[0]=='5')
		{
			break;
		}
		else{
			printf("Enter String Without Space:\n");
			scanf("%s",datas);
			write(network_socket,datas,sizeof(datas));
			if(choice[0]=='2')
			{
				printf("Enter 2nd string for comparison:\n");
				scanf("%s",ss);
				write(network_socket,ss,sizeof(ss));
			}
			if(choice[0]=='4'){
				printf("Enter index:\n");
				char index[4];
				scanf("%s",index);
				write(network_socket,index,sizeof(index));
				printf("\n\nPlease enter choice:\n1.Insertion\n2.Deletion\n");
				char choice2[2];
				scanf("%s", choice2);
				write(network_socket,choice2,sizeof(choice2));
				if(choice2[0]=='1'){
					printf("Enter char to be inserted:\n");
					char insert[2];
					scanf("%s:",insert);
					write(network_socket,insert,sizeof(insert));
				}

			
			}
			int ee=read(network_socket,datar,sizeof(datar));
			datar[ee]='\0';
			printf("Output from server: %s\n",datar);
			if(choice[0]=='2'){printf("%s",ex);}
		}
	}
	close(network_socket);
	return 0;
}

