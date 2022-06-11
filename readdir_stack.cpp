#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
int main()
{
    struct dirent* filename;
    DIR* dp = opendir("/home/lighthouse/hpc/b2");
    char buf[512];
    char* path = "/home/lighthouse/hpc/b2";
    memcpy(buf, path, strlen(path));
    buf[strlen(path)] = '/';
    while(filename = readdir(dp))
    {
        memcpy( buf+strlen(path)+1, filename->d_name, strlen(filename->d_name));
        // 末尾追加0是为了避免乱码
        buf[strlen(path) + strlen(filename->d_name)+1] = 0;
        printf("%s %d %d %d\n", buf, filename->d_type, filename->d_ino, filename->d_reclen);
    }
}