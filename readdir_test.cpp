#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>

int main(int argc, char* argv[])
{
    DIR* dp;
    struct dirent* filename;
    dp = opendir(argv[1]);
    if(!dp)
    {
        fprintf(stderr, "open direntory error\n");
        return 0;
    }
    while(filename = readdir(dp))
    {
        // short d_reclen是这个文件的长度，需要注意的是这里的长度并不是指文件大小，
        // 因为大小和长度是两回回事了，你可以用lseek将文件长度移得很长，但大小其实还是那么大。
        printf("%s %ld %us\n", filename->d_name, filename->d_ino, filename->d_reclen);
    }
    closedir(dp);
}