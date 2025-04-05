#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Include this library to use strlen and strcmp

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "a"); // Open file in append mode
    if (file == NULL) {
        file = fopen(argv[1], "w"); // Create file if it doesn't exist
        if (file == NULL) {
            perror("Error opening file");
            return 1;
        }
    }

    char input[256];
    printf("Enter strings to write to the file (enter \"-1\" to stop):\n");

    while (1) {
        printf("> ");
        fgets(input, sizeof(input), stdin);

        // Remove newline character
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }

        if (strcmp(input, "-1") == 0) {
            break;
        }

        fprintf(file, "%s\n", input);
    }

    fclose(file);
    printf("Data successfully written to %s\n", argv[1]);

    return 0;
}