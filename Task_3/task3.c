#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int process_count = 1; // Start with the initial parent process

void create_child_if_odd(DWORD pid) {
    if (pid % 2 == 1) { // Check if the PID is odd
        STARTUPINFO si;
        PROCESS_INFORMATION pi;
        
        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        ZeroMemory(&pi, sizeof(pi));

        if (CreateProcess(NULL, "cmd.exe /c echo New child process created", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
            process_count++; // Increment process count
            WaitForSingleObject(pi.hProcess, INFINITE);
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
        } else {
            fprintf(stderr, "Failed to create new child process.\n");
        }
    }
}

int main() {
    STARTUPINFO siA, siB, siC;
    PROCESS_INFORMATION piA, piB, piC;

    // Initialize structures
    ZeroMemory(&siA, sizeof(siA));
    siA.cb = sizeof(siA);
    ZeroMemory(&piA, sizeof(piA));

    ZeroMemory(&siB, sizeof(siB));
    siB.cb = sizeof(siB);
    ZeroMemory(&piB, sizeof(piB));

    ZeroMemory(&siC, sizeof(siC));
    siC.cb = sizeof(siC);
    ZeroMemory(&piC, sizeof(piC));

    // Create three child processes
    if (CreateProcess(NULL, "cmd.exe /c echo Child A created", NULL, NULL, FALSE, 0, NULL, NULL, &siA, &piA)) {
        process_count++;
        create_child_if_odd(piA.dwProcessId);
        WaitForSingleObject(piA.hProcess, INFINITE);
        CloseHandle(piA.hProcess);
        CloseHandle(piA.hThread);
    }

    if (CreateProcess(NULL, "cmd.exe /c echo Child B created", NULL, NULL, FALSE, 0, NULL, NULL, &siB, &piB)) {
        process_count++;
        create_child_if_odd(piB.dwProcessId);
        WaitForSingleObject(piB.hProcess, INFINITE);
        CloseHandle(piB.hProcess);
        CloseHandle(piB.hThread);
    }

    if (CreateProcess(NULL, "cmd.exe /c echo Child C created", NULL, NULL, FALSE, 0, NULL, NULL, &siC, &piC)) {
        process_count++;
        create_child_if_odd(piC.dwProcessId);
        WaitForSingleObject(piC.hProcess, INFINITE);
        CloseHandle(piC.hProcess);
        CloseHandle(piC.hThread);
    }

    // Parent process prints the total count
    printf("Total processes created: %d\n", process_count);

    return 0;
}