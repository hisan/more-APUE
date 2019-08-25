#include "apue.h"
#include "myerror.h"
#include <pwd.h>
#include <stddef.h>
#include <string.h>

void HexDump(char *buf,int len,int addr) {  
	int i,j,k;  
	char binstr[80];  
  
	for (i=0;i<len;i++) {  
		if (0==(i%16)) { //每16个字节
			sprintf(binstr,"%08x -",i+addr);  
			sprintf(binstr,"%s %02x",binstr,(unsigned char)buf[i]);  
		} else if (15==(i%16)) {  
			sprintf(binstr,"%s %02x",binstr,(unsigned char)buf[i]);  
			sprintf(binstr,"%s  ",binstr);  
			for (j=i-15;j<=i;j++) {  
				sprintf(binstr,"%s%c",binstr,('!'<buf[j]&&buf[j]<='~')?buf[j]:'.');  
			}  
			printf("%s\n",binstr);  
		} else {  
			sprintf(binstr,"%s %02x",binstr,(unsigned char)buf[i]);  
		}  
	}  
	if (0!=(i%16)) {  
		k=16-(i%16);  
		for (j=0;j<k;j++) {  
			sprintf(binstr,"%s   ",binstr);  
		}  
		sprintf(binstr,"%s  ",binstr);  
		k=16-k;  
		for (j=i-k;j<i;j++) {  
			sprintf(binstr,"%s%c",binstr,('!'<buf[j]&&buf[j]<='~')?buf[j]:'.');  
		}  
		printf("%s\n",binstr);  
	}  
} 


struct passwd *getpwnam1(const char *name)
{
	struct passwd *ptr;
	setpwent();
	while((ptr = getpwent()) != NULL)
	{
		if (strcmp(name,ptr->pw_name) == 0)
		{
			break;
		}
	}
	endpwent();
	return(ptr);
}

int main(int argc,char **argv)
{
	if (argc != 2)
	{
		err_sys("Usge: <filename>\n");
	}
	
	struct passwd * ppwd = getpwnam1(argv[1]);
	
	if ( ppwd == NULL)
	{
		return 0;
	}

	HexDump((char *)ppwd,sizeof(ppwd),(int)ppwd);

	exit(0);
}