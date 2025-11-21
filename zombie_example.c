/*
zombie_example.c
Demonstrates how a child can become a zombie when the parent does not wait immediately.
Parent sleeps allowing you to run `ps` to see the zombie.
Compile: gcc -Wall -o zombie_example zombie_example.c
Run: ./zombie_example
Then in another terminal quickly run: ps -o pid,ppid,state,cmd -p <child-pid>
Look for 'Z' state (zombie).
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        /* Child exits immediately */
        printf("Child (%d) exiting immediately\n", getpid());
        _exit(0);
    } else {
        /* Parent sleeps, child remains zombie until parent waits */
        printf("Parent (%d): sleeping for 10 seconds. Child pid=%d\n", getpid(), pid);
        sleep(10);
        printf("Parent: now exiting (child should be reaped automatically by exit)\n");
        return 0;
    }
}