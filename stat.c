// gcc -o stat stat.c -Wall
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
int main(int argc, char *argv[]){
    if(argc!=2){
        printf("Usage: %s filename\n", "Stat");
        exit(1);
    }
    struct stat data;

    if(stat(argv[1], &data)==-1){
        perror("stat");
        exit(1);
    }
    //打印文件大小，分配的磁盘块数，引用数
    printf("file_size:%ld\n",data.st_size);
    printf("num_of_disk:%ld\n",data.st_blocks);
    printf("links:%ld\n",data.st_nlink);

}