/*
fork_example.c
Simple demonstration of fork().
Parent and child run the same code after fork().
Compile: gcc -Wall -o fork_example fork_example.c
Run: ./fork_example
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void) {
    pid_t pid;

    printf("Before fork(): pid=%d\n", getpid());

    pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        /* Child process */
        printf("Child: pid=%d, parent=%d\n", getpid(), getppid());
    } else {
        /* Parent process */
        printf("Parent: pid=%d, child=%d\n", getpid(), pid);
    }

    /* Both processes continue here */
    printf("Process %d exiting\n", getpid());
    return 0;
}