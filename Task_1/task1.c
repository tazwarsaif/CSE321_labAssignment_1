// task1.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s filename\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "a"); // open for appending, create if not exists
    if (fp == NULL) {
        perror("File opening failed");
        return 1;
    }

    char input[100];
    while (1) {
        printf("Enter string ('-1' to stop): ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0; // remove newline character

        if (strcmp(input, "-1") == 0)
            break;

        fprintf(fp, "%s\n", input);
    }

    fclose(fp);
    printf("File saved successfully.\n");
    return 0;
}