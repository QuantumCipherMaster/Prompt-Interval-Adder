#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

#define BUFFER_SIZE 1024
int lines;

// Function to create directory if it doesn't exist
int create_directory(const char *name) {
    struct stat st = {0};

    if (stat(name, &st) == -1) {
        if (mkdir(name, 0700) == -1) {  // 0700 permissions allow owner read, write, and execute
            fprintf(stderr, "Failed to create directory '%s': %s\n", name, strerror(errno));
            return 0;
        }
    }
    return 1;
}

void process_text(const char *file_path, const char *directory_name, const char *insert_text) {
    char buffer[BUFFER_SIZE];
    int line_counter = 1, file_number = 1;
    FILE *file = fopen(file_path, "r");
    if (!file) {
        fprintf(stderr, "Failed to open file '%s': %s\n", file_path, strerror(errno));
        return;
    }

    if (!create_directory(directory_name)) {
        fclose(file);
        return;
    }

    char output_file_path[256];
    sprintf(output_file_path, "%s/%d.txt", directory_name, file_number);
    FILE *output_file = fopen(output_file_path, "w");
    if (!output_file) {
        fprintf(stderr, "Failed to create output file '%s': %s\n", output_file_path, strerror(errno));
        fclose(file);
        return;
    }

    fprintf(output_file, "%s\n", insert_text); // Insert custom text at the start

    while (fgets(buffer, BUFFER_SIZE, file)) {
        fprintf(output_file, "%s", buffer);
        if (++line_counter % lines == 0) {
            fclose(output_file);
            file_number++;
            sprintf(output_file_path, "%s/%d.txt", directory_name, file_number);
            output_file = fopen(output_file_path, "w");
            if (!output_file) {
                fprintf(stderr, "Failed to create output file '%s': %s\n", output_file_path, strerror(errno));
                break;
            }
            fprintf(output_file, "%s\n", insert_text); // Insert custom text for new file segment
        }
    }

    if (output_file) {
        fclose(output_file);
    }
    fclose(file);
}

int main() {
    char file_path[256], directory_name[256], insert_text[1024];
    printf("Enter the path to the text file: ");
    fgets(file_path, 255, stdin);
    file_path[strcspn(file_path, "\n")] = 0; // Remove the newline character

    printf("Enter the directory name to save the files: ");
    fgets(directory_name, 255, stdin);
    directory_name[strcspn(directory_name, "\n")] = 0; // Remove the newline character

    printf("Enter the number you want to insert every n lines: ");
    scanf("%d", &lines);
    while (getchar() != '\n');  // Clear the input buffer

    printf("Enter the text to insert every %d lines: ", lines);
    fgets(insert_text, 1023, stdin);
    insert_text[strcspn(insert_text, "\n")] = 0; // Remove the newline character

    process_text(file_path, directory_name, insert_text);

    return 0;
}
