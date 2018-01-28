#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define MAX_NIDS 8
#define SHM_SIZE 1024

union semun {
    int              val;    /* Value for SETVAL */
    struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
    unsigned short  *array;  /* Array for GETALL, SETALL */
    struct seminfo  *__buf;  /* Buffer for IPC_INFO(Linux-specific) */
};


int semReadId, semWriteId;
char* shmptr[MAX_NIDS];

void P(int semid){
    struct sembuf op;
    op.sem_num = 0;
    op.sem_op = -1;
    op.sem_flg = 0;
    semop(semid, &op, 1);
}
void V(int semid){
    struct sembuf op;
    op.sem_num = 0;
    op.sem_op = 1;
    op.sem_flg = 0;
    semop(semid, &op, 1);
}

void ReadBuf(int fd){
    int index = 0;
    while(true){
        P(semReadId);
        if(read(fd, shmptr[index], SHM_SIZE) < SHM_SIZE){
            V(semWriteId);
            break;
        };
        index = (index + 1) % MAX_NIDS;
        V(semWriteId);
    }
}

void WriteBuf(int fd, int totalBytes){
    int index = 0, writeBytes, totalWriteBytes = 0;
    while(totalWriteBytes < totalBytes){
        P(semWriteId);
        if(totalWriteBytes + SHM_SIZE <= totalBytes)
            writeBytes = write(fd, shmptr[index], SHM_SIZE);
        else
             writeBytes = write(fd, shmptr[index], totalBytes - totalWriteBytes);
        if(writeBytes == -1){
            printf("write error\n");
            break;
        }
        totalWriteBytes += writeBytes;
        index = (index + 1) % MAX_NIDS;
        V(semReadId);
    }
}
int main(int argc, char** argv){
    if(argc < 3){
        printf("usage : copy file1 file2");
        return 1;
    }

    int file1 = open(argv[1], O_RDONLY);
    int file2 = open(argv[2], O_WRONLY | O_CREAT | O_APPEND, 777);
    if(file1 == -1){
        printf("sources file open fail\n");
        exit(1);
    }
    if(file2 == -1){
        printf("target file open fail\n");
        exit(1);
    }


    struct stat st;
    stat(argv[1], &st);
    int fileLength = st.st_size;
    printf("%d bytes will write from %s to %s, please press any key to begin\n", fileLength, argv[1], argv[2]);
    getchar();

    int i, shmid[MAX_NIDS];
    for(i = 0; i < MAX_NIDS; ++i){
        shmid[i] = shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT | 0666);
        if(shmid[i] == -1){
            printf("%d is the max number of shm in sys", i);
            break;
        }
    }

    int j;
    for(j = 0; j < i; ++j){
        shmptr[j] = (char*)shmat(shmid[j], NULL, SHM_R | SHM_W);
    }

    semReadId = semget(IPC_PRIVATE, 1, IPC_CREAT);
    semWriteId =semget(IPC_PRIVATE, 1, IPC_CREAT);
    if(semReadId == -1 || semWriteId == -1){
        printf("sem get error\n");
        exit(1);
    }
    union semun arg1, arg2;
    arg1.val = MAX_NIDS;
    if(semctl(semReadId, 0, SETVAL, arg1) == -1){
        printf("sem set fail\n");
        exit(1);
    }
    arg2.val = 0;
    if(semctl(semWriteId, 0, SETVAL, arg2) == -1){
        printf("sem set fail\n");
        exit(1);
    }

    int pid1, pid2;
    pid1 = fork();
    if(pid1 != 0){
        pid2 = fork();
        if(pid2 != 0){
            waitpid(pid1, NULL, 0);
            waitpid(pid2, NULL, 0);
        }
        else{
            WriteBuf(file2, fileLength);
            return 0;
        }
    }
    else{
        ReadBuf(file1);
        return 0;
    }

    printf("copy success\n");
    close(file1);
    close(file2);
    return 0;
}
