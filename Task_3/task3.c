// task3.c
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    int count = 1; // initial parent process

    pid_t a = fork();
    if (a == 0) {
        // Child
    } else if (a > 0) {
        count++;
    }

    pid_t b = fork();
    if (b == 0) {
        // Child
    } else if (b > 0) {
        count++;
    }

    pid_t c = fork();
    if (c == 0) {
        // Child
    } else if (c > 0) {
        count++;
    }

    pid_t pid = getpid();
    if (pid % 2 != 0) {
        fork(); // create a new child if PID is odd
        count++;
    }

    sleep(1); // let all processes finish
    if (getppid() > 1) // to prevent printing from zombie processes
        printf("Process ID: %d, Parent ID: %d\n", getpid(), getppid());

    wait(NULL);
    return 0;
}
