#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <dirent.h>
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
void ls(char* path)
{
    char buf[512];
    int fd;
    struct stat st;
    
    // 打开文件
    if((fd = open(path, 0)) < 0)
    {
        fprintf(stderr, "ls error\n", path);
        return;
    }
    // 获取文件stat信息
    if(fstat(fd, &st) < 0)
    {
        fprintf(stderr, "ls cannot stat %s\n", path);
        close(fd);
        return;
    }
    // 如果是文件：打印（文件名，类型，ino，大小）
    if(S_ISREG(st.st_mode))
    {
        printf("%s %d %d %d\n", fmtname(path), st.st_mode, st.st_ino, st.st_size);
    }
    // 如果是目录
    else if(S_ISDIR(st.st_mode))
    {
        if(strlen(path) + 1 + 300   > sizeof(buf))
        {
            printf("ls: path too long\n");
            return;
        }
        // path 放入缓冲区
        strcpy(buf, path);
        char* p = buf + strlen(buf);
        *p++ = '/';
        DIR* dp = opendir(path);
        struct dirent* filename;
        while(filename = readdir(dp))
        {
            memcmp(p, filename->d_name, sizeof(filename->d_name));
            p[sizeof(filename->d_name)] = 0;
            printf("%s %d %d\n", filename->d_name, filename->d_type, filename->d_ino);
        }
    }
}

int main(int argc, char* argv[])
{
    int i;
    if(argc < 2)
    {
        ls(".");
        exit(0);
    }
    for(int i = 1; i < argc; i++)
    {
        // ls 每个目录
        ls(argv[i]);
    }
    exit(0);
}