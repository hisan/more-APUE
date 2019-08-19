#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SERVER_PORT 1000
#define servaddr_string "192.168.67.130"
#define pending_confd 20
#define RECVBUFFER 1024

int main()
{
	int confd = 0;
	int clilen = 0;
	int skfd = 0;
	int rcvlen = 0;
	char recvbuffer[RECVBUFFER] = {0};
	
	skfd = socket(AF_INET,SOCK_STREAM,0);
	if(skfd == -1)
	{
		printf("crater socket error!\r\n");
		return -1;
	}
	
	struct sockaddr st_clientaddr;
	struct sockaddr_in st_serveraddr;
	
	bzero(&st_serveraddr,sizeof(st_serveraddr));
	bzero(&st_clientaddr,sizeof(st_clientaddr));
	
	st_serveraddr.sin_family = AF_INET;
	
	st_serveraddr.sin_port = htons(SERVER_PORT);
	
	if((inet_aton(servaddr_string,(struct in_addr*)st_serveraddr.sin_addr.s_addr)) == -1)
	{
		return -1;
	}
	
	if(-1 == bind(skfd,(struct sockaddr *)&st_serveraddr,sizeof(st_serveraddr)))
	{
		printf("bind the socket fd error!\r\n");
		return -2;
	}
	
	if((listen(skfd,pending_confd))!=0)
	{
		printf("listen the connect is error\r\n");
		return -3;
	}
	
	while(1)
	{
		clilen = sizeof(st_clientaddr);
		if((confd = accept(skfd,(struct sockaddr*)&st_clientaddr,&clilen)) < 0 )
		{
			printf("accept error\r\n");
			return -4;
		}
		
		rcvlen = read(confd,recvbuffer,RECVBUFFER);
		
		if(rcvlen <= 0 )
		{
			printf("read nothing!\r\n");
		}
		else
		{
			printf("%s\r\n",recvbuffer);
		}
		memset(recvbuffer,0,RECVBUFFER);
	}
	return 0;
}