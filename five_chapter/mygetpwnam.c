#include "apue.h"
#include "myerror.h"
#include <stddef.h>
#include <string.h>

struct passwd *getpwnam1(const char *name)
{
	struct passwd *ptr;
	setpwdent();
	
}