#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

#include <sys/time.h>

#include <sys/types.h>
#include <sys/wait.h>



int main (int argc, char *argv[]) {

    struct timeval current_time;
//long time = gettimeofday(&current_time, NULL); //initializes the time of day as the current time

//establish region of shared memory before child process is forked
/* the size (in bytes) of shared memory object */
const int SIZE = 4096;
/* name of the shared memory object */
const char *name = "OS";
/* strings written to shared memory */
const long *message_0 = gettimeofday(&current_time, NULL);
/* shared memory file descriptor */
int fd;
/* pointer to shared memory obect */
long *ptr;
    /* open the shared memory object */
    fd = shm_open(name, O_RDONLY, 0666);
    /* memory map the shared memory object */
    ptr = (long *) mmap(0, SIZE, PROT_READ, MAP_SHARED, fd, 0); //what happens if star is removed?

    pid_t pid;
    pid = fork(); //fork child process

    if (pid < 0) { /* error occured */
        fprintf(stderr, "Fork Failed");
        return 1;
    }
    else {
        if (pid == 0) { /* child process */
            //memcpy();

            /* the size (in bytes) of shared memory object */
            const int SIZE = 4096;
            /* name of the shared memory object */
            const char *name = "OS";
            /* strings written to shared memory */
            //const char *message 0 = "Hello";
            //const char *message 1 = "World!";
            const char *message_3 = "Lab 2 Practice!"; //possible answer. Read rest for more info
            /* shared memory file descriptor */
            int fd;
            /* pointer to shared memory obect */
            char *ptr;
                /* create the shared memory object */
                fd = shm_open(name,O_CREAT | O_RDWR,0666);
                /* configure the size of the shared memory object */
                ftruncate(fd, SIZE);
                /* memory map the shared memory object */
                ptr = (char *)
                    mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
                /* write to the shared memory object */
                
                /*
                sprintf(ptr,"%s",message 0);
                ptr += strlen(message 0);
                sprintf(ptr,"%s",message 1);
                ptr += strlen(message 1);
                */

                sprintf(ptr,"%s",message_3); //answer
                ptr += strlen(message_3);
                

            execlp("/bin/ls","ls",NULL); ///find a way with variables   
            return 0;
        }
        else { /* parent will wait for the child to compete */
            wait(NULL);
            /* open the shared memory object */
            fd = shm_open(name, O_RDONLY, 0666);
            /* read from the shared memory object */

            printf("%ld",(long *)ptr); //what happens if star is removed?
            /* remove the shared memory object */
            shm_unlink(name);
            return 0;

            //sprintf(ptr, "Elapsed time: %ld", (*message_0 - gettimeofday(&current_time, NULL)));
            // print current_time - end_time
        }
    }
    return 0;
}