/*
orphan_example.c
Demonstrates an orphaned child: parent exits first, child continues and its parent becomes init/systemd (PID 1).
Compile: gcc -Wall -o orphan_example orphan_example.c
Run: ./orphan_example
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
        /* Child: wait and then print its parent pid (should be 1 or systemd) */
        sleep(2); /* give parent time to exit */
        printf("Child (%d): my parent is %d (should be 1 or systemd)\n", getpid(), getppid());
        sleep(1);
        return 0;
    } else {
        /* Parent exits immediately */
        printf("Parent (%d) exiting immediately, child pid=%d\n", getpid(), pid);
        return 0;
    }
}