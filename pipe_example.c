/*
pipe_example.c
Sets up a pipe between parent and child.
Parent writes a message, child reads it and prints.
Compile: gcc -Wall -o pipe_example pipe_example.c
Run: ./pipe_example
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    int fd[2];
    pid_t pid;
    const char *msg = "Hello from parent via pipe\n";

    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        /* Child: read from pipe */
        close(fd[1]); /* close unused write end */
        char buffer[256];
        ssize_t n = read(fd[0], buffer, sizeof(buffer)-1);
        if (n < 0) {
            perror("read");
            _exit(1);
        }
        buffer[n] = '\0';
        printf("Child (%d) read: %s", getpid(), buffer);
        close(fd[0]);
        _exit(0);
    } else {
        /* Parent: write to pipe */
        close(fd[0]); /* close unused read end */
        write(fd[1], msg, strlen(msg));
        close(fd[1]);
        wait(NULL);
    }
    return 0;
}