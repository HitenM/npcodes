#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
int main()
{
	int server_socket=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in server_address;
	server_address.sin_family=AF_INET;
	server_address.sin_port=htons(9069);
	server_address.sin_addr.s_addr=INADDR_ANY;

	bind(server_socket,(struct sockaddr*) &server_address,sizeof(server_address));

	listen(server_socket,2);
	printf("Waiting for client:\n");
	int client_socket=accept(server_socket,NULL,NULL);

	char datas[256]="\n\nPlease enter your choice:\n1.String Sorting.\n2.String Comparison.\n3.String Copy.\n4.String insertion, deletion from index.\n5.Exit\n";
	char strr[256];
	char ss[256];
	char choice[2];
	int ch=0;
	while(1)
	{
		write(client_socket,datas,sizeof(datas));
		int es=read(client_socket,choice,sizeof(choice));
		choice[es]='\0';
		printf("Choice given by user: %s",choice);
		printf("\n");
		
		if(choice[0]=='5')
		{
			printf("Exiting Program.\n");
			break;
		}
		else if(choice[0]=='1'){

			printf("Option chosen: String Sorting.\n\n");
			int e=read(client_socket,strr,sizeof(strr));
			//strr[e]='\0';
			printf("String received: %s\n",strr);
			int n=strlen(strr);
			//Bubble Sorting string
			for(int i=0;i<n-1;i++){
				for(int j=i+1;j<n;j++){
					if(strr[i]>strr[j]){
						
						char swap=strr[j];
						strr[j]=strr[i];
						strr[i]=swap;
					}
				}			
			}

			printf("Sorted String to be sent: %s\n", strr);
			write(client_socket,strr,sizeof(strr));


		}
		else if(choice[0]=='2'){
			printf("Option chosen: String Comparison.\n");
			int e=read(client_socket,strr,sizeof(strr));
			printf("String received: %s\n",strr);
			int ee=read(client_socket,ss,sizeof(ss));
			printf("Second String Received: %s\n",ss);
			int ans=strcmp(strr,ss);
			if(ans==0){char data[]="The Strings are equal.\n";write(client_socket,data,sizeof(data));}
			else{char data[]="The Strings are not equal.\n";write(client_socket,data,sizeof(data));}
		}
		else if(choice[0]=='3'){
			printf("Option chosen: String Copy.\n");
			int e=read(client_socket,strr,sizeof(strr));
			printf("String received: %s\n",strr);
			char data[strlen(strr)];
			strcpy(data,strr);

			printf("String to be sent: %s\n",data);
			write(client_socket,data,sizeof(data));
		}
		else if(choice[0]=='4'){
			printf("Option chosen: Insertion, Deletion\n");
			int e=read(client_socket,strr,sizeof(strr));
			char index[4];
			int ee=read(client_socket,index,sizeof(index));
			int l=strlen(index);
			int ii=0;//index
			int places=1;
			for(int i =l-1;i>=0;i--,places*=10){
				ii=ii+((((int)index[i])-((int)'0'))*places);
			
			}
			char choice2[2];
			read(client_socket,choice2,sizeof(choice2));
			if(choice2[0]=='1'){
				char insert[2];
				read(client_socket,insert,sizeof(insert));
				strr[ii]=insert[0];
			}
			else{
				int len=strlen(strr);
				for(int i=ii;i<len-1;i++){
					strr[i]=strr[i+1];
				}
				char neww[len-1];
				for(int i=0;i<len-1;i++){neww[i]=strr[i];}
				write(client_socket,neww,sizeof(neww));
				continue;
				
			}
			write(client_socket,strr,sizeof(strr));

		}else{
			printf("Wrong Input. Please try again.\n");

		}
	}
	close(server_socket);
	return 0;
}

