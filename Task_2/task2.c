#include <stdio.h>
#include <windows.h>

int main() {
    STARTUPINFO siChild, siGrandchild;
    PROCESS_INFORMATION piChild, piGrandchild;

    // Initialize memory for child process structures
    ZeroMemory(&siChild, sizeof(siChild));
    siChild.cb = sizeof(siChild);
    ZeroMemory(&piChild, sizeof(piChild));

    // Initialize memory for grandchild process structures
    ZeroMemory(&siGrandchild, sizeof(siGrandchild));
    siGrandchild.cb = sizeof(siGrandchild);
    ZeroMemory(&piGrandchild, sizeof(piGrandchild));

    // Create the grandchild process first
    if (!CreateProcess(NULL, "cmd.exe /c echo I am grandchild", NULL, NULL, FALSE, 0, NULL, NULL, &siGrandchild, &piGrandchild)) {
        fprintf(stderr, "Error creating grandchild process.\n");
        return 1;
    }

    // Wait for the grandchild process to complete
    WaitForSingleObject(piGrandchild.hProcess, INFINITE);

    // Close grandchild process handles
    CloseHandle(piGrandchild.hProcess);
    CloseHandle(piGrandchild.hThread);

    // Create the child process
    if (!CreateProcess(NULL, "cmd.exe /c echo I am child", NULL, NULL, FALSE, 0, NULL, NULL, &siChild, &piChild)) {
        fprintf(stderr, "Error creating child process.\n");
        return 1;
    }

    // Wait for the child process to complete
    WaitForSingleObject(piChild.hProcess, INFINITE);

    // Close child process handles
    CloseHandle(piChild.hProcess);
    CloseHandle(piChild.hThread);

    // The parent process prints its message
    printf("I am parent\n");

    return 0;
}