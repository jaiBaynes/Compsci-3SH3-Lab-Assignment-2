#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/time.h>

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

int main(void) {

    struct timeval current;
    gettimeofday(&current, NULL);

    long write_msg[BUFFER_SIZE] = current; //possible answer
    long read_msg[BUFFER_SIZE];
    int fd[2];
    pid_t pid;

    /* create the pipe */
    if (pipe(fd) == -1) {
        fprintf(stderr,"Pipe failed");
        return 1;
    }
    /* fork a child process */
    pid = fork();

    if (pid < 0) { /* error occurred */
        fprintf(stderr, "Fork Failed");
        return 1;
    }

    if (pid > 0) { /* parent process */
        /* close the unused end of the pipe */
        close(fd[READ_END]);
        /* write to the pipe */
        write(fd[WRITE_END], write_msg, sizeof(write_msg)+1);
        /* close the write end of the pipe */
        close(fd[WRITE_END]);
    }
    else { /* child process */
        /* close the unused end of the pipe */
        close(fd[WRITE_END]);
        /* read from the pipe */
        read(fd[READ_END], read_msg, BUFFER_SIZE);
        printf("read %p",read_msg);
        printf("Seconds: %p Miliseconds: %p",read_msg.tv_sec, read_msg.tv_usec);
        /* close the read end of the pipe */
        close(fd[READ_END]);
    }
    return 0;
}

// modified from 3.21 and 3.22 on pages 141-142
