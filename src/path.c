#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "myhdr.h"

// Executes an external command
void execute_external_command(char *command, char *parameter) {
    // Get the PATH environment variable
    char *path_env = getenv("PATH");
    if (!path_env) {
        fprintf(stderr, "PATH environment variable not found\n");
        return;
    }

    char path_copy[1024];
    // Copy the PATH to a local buffer
    strncpy(path_copy, path_env, sizeof(path_copy) - 1);
    path_copy[sizeof(path_copy) - 1] = '\0';  // Ensure null termination
    char *path = strtok(path_copy, ":");
    char full_path[256];
    
    // Iterate through each directory in the PATH
    while (path != NULL) {
        snprintf(full_path, sizeof(full_path), "%s/%s", path, command);
        // Check if the command exists and is executable
        if (access(full_path, X_OK) == 0) {
            pid_t pid = fork();
            if (pid == 0) {
                // Child process executes the command
                execl(full_path, command, parameter, (char *)NULL);
                perror("exec failed");
                exit(EXIT_FAILURE);
            } else if (pid > 0) {
                // Parent process waits for the child to finish
                wait(NULL);
            } else {
                perror("fork failed");
            }
            return;
        }
        path = strtok(NULL, ":");
    }

    printf("Command not found: %s\n", command);
}
