#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
// 截取出文件名
char* fmtname(char* path)
{
    static char buf[512];
    char* p;
    for(p= path + strlen(path); p >= path && *p != '/'; p--);
    p++;
    if(strlen(p) >= 512)return p;
    memmove(buf, p, strlen(p));
    memset(buf + strlen(p), '\0', 512 - strlen(p));
    return buf;
}
int main()
{
    printf("%s", fmtname("/home/workspace"));
}