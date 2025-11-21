/*
fork_exec_example.c
Shows how a process can fork and the child replace its image with exec.
Child executes "ls -l" using execlp().
Compile: gcc -Wall -o fork_exec_example fork_exec_example.c
Run: ./fork_exec_example
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        /* Child: execute ls -l */
        printf("Child (%d): exec ls -l\n", getpid());
        execlp("ls", "ls", "-l", (char *)NULL);
        /* If execlp returns, an error happened */
        perror("execlp");
        _exit(1);
    } else {
        /* Parent: wait for child */
        int status;
        if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid");
            return 1;
        }
        printf("Parent: child finished\n");
    }
    return 0;
}