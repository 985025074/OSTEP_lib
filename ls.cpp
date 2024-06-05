//gcc -o ls ls.cpp -Wall
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <cstring>
int main(int argc, char *argv[]){
    int flag=0;
    char opt;
   while((opt=getopt(argc,argv,":l::"))!=-1){
        switch (opt)
        {
        case 'l':
            if(optarg!=NULL){
                flag=2;
            }
            else{
                flag=1;
            }
            break;
        
        case '?':
            printf("Error! just -l is accpetable.\n");
            exit(1);
            break;
        }
   }
    
    DIR* dir=flag!=2?opendir("."):opendir(optarg);
    struct dirent *temp;
    while((temp=readdir(dir))!=NULL){
        printf("%s\n",temp->d_name);
       if(flag!=0){
        //此时打印出文件所有者，所属组权限以及stat函数获得的一些其他信息
        char buf[100];
        if(flag==1){
        getcwd(buf,100);
        }
        else{
        strcpy(buf,optarg);    
        }
        strcat(buf,"/");
        strcat(buf,temp->d_name);
        printf("%s\n",buf);
        struct stat st;
        if(stat(buf, &st)==-1){
            perror("stat");
            exit(1);
            }
        printf("file_size:%ld\n",st.st_size);
        printf("num_of_disk:%ld\n",st.st_blocks);
        printf("links:%ld\n",st.st_nlink);
        }

        
    }
    closedir(dir);
    return 0;

}