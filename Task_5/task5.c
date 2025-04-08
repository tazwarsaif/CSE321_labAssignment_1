// task5.c
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    printf("1. Parent process ID: %d\n", getpid());

    pid_t child = fork();
    if (child == 0) {
        printf("2. Child process ID: %d\n", getpid());

        for (int i = 0; i < 3; i++) {
            pid_t grandchild = fork();
            if (grandchild == 0) {
                printf("3. Grandchild process ID: %d\n", getpid());
                exit(0); // grandchild exits after printing
            }
        }

        for (int i = 0; i < 3; i++) {
            wait(NULL); // child waits for grandchildren
        }
    } else {
        wait(NULL); // parent waits for child
    }

    return 0;
}
