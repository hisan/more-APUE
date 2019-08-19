#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SENDBUFFER 1024
#define SERVER_PORT 1000

int main()
{
	struct sockaddr_in servaddr;
	int socketfd = 0 ;
	int confd = 0;
	char sendbugger[SENDBUFFER] = {"I am a boy！ \r\n"};
	char *servaddr_string = "192.168.67.130";
	int count = 1;
	
	while(1)
	{
		if( (socketfd = socket(AF_INET,SOCK_STREAM,0)) == -1)
		{
			printf("create socket error!");
			return -1;
		}
		
		bzero(&servaddr,sizeof(servaddr));
		
		servaddr.sin_family = AF_INET;
		inet_pton(servaddr_string,&servaddr.sin_addr.s_addr);
		servaddr.sin_port = htons(SERVER_PORT);
		
		int ret = connect(socketfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
		if( ret != 0)
		{
			printf("connect the server error!\r\n");
			return -2;
		}
		
		printf("%d\r\n",count);
		count += 1;
		//printf("please input the message you wan't to send\r\n");
		//scanf("%s",sendbugger);
		write(socketfd,sendbugger,strlen(sendbugger));
		sleep(2000);
	}
	
	return 0;
}

