#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

	   
int main1(void)
{
	time_t t;
	struct tm *tmp;
	char buf1[16];
	char buf2[64];
	
	time(&t);
	
	tmp = localtime(&t);
	if (strftime(buf1,16,"time and date:%r, %a,%b,%d, %Y",tmp) == 0)
	{
		printf("buffer length 16 is too small!\r\n");
	}
	else
	{
		printf("%s\n",buf1);
	}
	
	if (strftime(buf2,64,"time and date: %r, %a,%b,%d, %Y",tmp) == 0)
	{
		printf("buffer length 64 is too small!\r\n");
	}
	else 
	{
		printf("%s\n",buf2);
	}
	
	exit(0);
}

int main(void)
{
   struct tm tm;
   char buf[255];

   memset(&tm, 0, sizeof(struct tm));
   strptime("2019-08-26 18:31:01", "%Y-%m-%d %H:%M:%S", &tm);
   strftime(buf, sizeof(buf), "%d %b %Y %H:%M", &tm);
   puts(buf);
   exit(EXIT_SUCCESS);
}