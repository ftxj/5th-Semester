#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <pwd.h>
#include <grp.h>
#include <time.h>

struct node{
    char name[1000];
    char father[1000];
    struct node* next;
};
long long StackUse = 0;
typedef struct node node;

void printFile(struct stat info, struct dirent *file){
    struct passwd *pwd = getpwuid(info.st_uid);
    struct group *gp = getgrgid(info.st_gid);
    if(pwd == NULL || gp == NULL || file == NULL) return;
    char PermissionS[11];
    struct tm t;
    tzset();
    localtime_r(&(info.st_mtime), &t);
    char buf[30];
    strftime(buf, 30, "%m %d %H:%M", &t);

    PermissionS[0] = info.st_mode & S_IRUSR? 'r' : '-';
    PermissionS[1] = info.st_mode & S_IWUSR? 'w' : '-';
    PermissionS[2] = info.st_mode & S_IXUSR? 'x' : '-';

    PermissionS[3] = info.st_mode & S_IRGRP? 'r' : '-';
    PermissionS[4] = info.st_mode & S_IWGRP? 'w' : '-';
    PermissionS[5] = info.st_mode & S_IXGRP? 'x' : '-';

    PermissionS[6] = info.st_mode & S_IROTH? 'r' : '-';
    PermissionS[7] = info.st_mode & S_IWOTH? 'w' : '-';
    PermissionS[8] = info.st_mode & S_IXOTH? 'x' : '-';

    PermissionS[9] = '\0';
    char dirFlag;
    if(S_ISDIR(info.st_mode)){
        dirFlag = 'd';
    }
    else{
        dirFlag = '-';
    }
    printf("%c%s %d %-7s %-7s %10ld %-s %-s\n",
            dirFlag, PermissionS, (int)info.st_nlink, pwd->pw_name, gp->gr_name,
            info.st_size, buf, file->d_name);
}
void trave_dir(node* path, int depth){
    if(chdir(path->name) == -1){
        StackUse--;
        return;
    }
    struct node* begin = NULL;
    struct node* next = NULL;
    struct node* forfree = NULL;

    begin = (node*)malloc(sizeof(node));
    if(begin == NULL) return;
    begin->next = NULL;
    next = begin;
    forfree = begin;
    DIR* d = NULL;
    struct dirent *file = NULL;
    struct stat info;
    int numOfFILES = 0;
    if((d = opendir(".")) != NULL){
        printf("%s/%s stack:%lld:\n", path->father, path->name, StackUse);
        while((file = readdir(d)) != NULL){
            if(strcmp(file->d_name, ".") == 0 ||
                strcmp(file->d_name, "..") == 0){
                continue;
            }
            if(lstat(file->d_name, &info) == -1){
                continue;
            }
            if(S_ISDIR(info.st_mode) && !S_ISLNK(info.st_mode)){
                node* temp =(node*) malloc(sizeof(node));
                if(temp == NULL) return;
                strcpy(temp->name, file->d_name);
                strcpy(temp->father, path->father);
                int k;
                for(k = 0; k <= strlen(path->name); ++k){
                    temp->father[strlen(path->father) + k] = path->name[k];
                }
                int len = strlen(temp->name);
                temp->name[len] = '/';
                temp->name[len + 1] = '\0';
                temp->next = NULL;
                next->next = temp;
                next = temp;
            }
            printFile(info, file);
        }
        printf("\n");
        next = begin;
        while(begin->next != NULL){
            begin = begin->next;
            free(next);
            next = begin;
            StackUse++;
            trave_dir(begin, depth + 1);
        }
        free(next);
    }
    if(file != NULL) free(file);
    if(d != NULL) closedir(d);
    StackUse--;
    if(chdir("..") != 0){
        printf("error when return dir\n");
    }
}

int main(int argc, char** argv){
    node n;
    strcpy(n.name, ".");
    strcpy(n.father, "");
    n.next = NULL;
    if(argc == 1)
        trave_dir(&n, 0);
    else{
        node x;
        strcpy(x.name, argv[1]);
        strcpy(x.father, "");
        x.next = NULL;
        trave_dir(&x, 0);
    }
    return 0;
}
