#include "apue.h"
#include "myerror.h"
#include <sys/msg.h>

#define MAXMSZ 521

struct mymesg
{
	long mtype;
	char mtext[MAXMSZ];
};

int main(int argc,char **argv)
{
	key_t key;
	long qid;
	struct mymesg m;
	
	if (argc != 3)
	{
		fprintf(stderr,"usgae:sending KEY message");
		exit(1);
	}
	
	key = strtol(argv[1],NULL,0);
	if ((qid = msgget(key,0)) < 0)
	{
		err_sys("can't open queue key %s",argv[1]);
	}
	memset(&m,0,sizeof(m));
	strncpy(m.mtext,argv[2],MAXMSZ-1);
	m.mtype = 1;
	if (msgsnd(qid,&m,strlen(m.mtext),0) < 0)
	{
		err_sys("can't send messgae");
	}
	exit(0);
}
