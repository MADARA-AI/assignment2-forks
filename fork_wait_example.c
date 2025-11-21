/*
fork_wait_example.c
Demonstrates creating a child and using waitpid() in the parent to wait for it.
Compile: gcc -Wall -o fork_wait_example fork_wait_example.c
Run: ./fork_wait_example
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        /* Child */
        printf("Child (%d): doing some work...\n", getpid());
        sleep(2); /* simulate work */
        printf("Child (%d): exiting with status 42\n", getpid());
        _exit(42);
    } else {
        /* Parent */
        int status;
        printf("Parent (%d): waiting for child %d\n", getpid(), pid);
        if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid");
            return 1;
        }
        if (WIFEXITED(status)) {
            printf("Parent: child exited with status %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Parent: child killed by signal %d\n", WTERMSIG(status));
        }
    }
    return 0;
}