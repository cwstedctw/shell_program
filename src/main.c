#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "myhdr.h"

// Handles user input and command execution loop
void handle_command() {
    char commandStr[256] = {0};
    command_t *cmd = NULL;

    do {
        printf("MyShell%% ");
        // Read the command input from the user
        if (fgets(commandStr, sizeof(commandStr), stdin) == NULL) {
            break;  // Exit loop if input fails
        }
        commandStr[strcspn(commandStr, "\n")] = 0;  // Remove trailing newline character

        // Parse the command string into a command structure
        cmd = parser_command(commandStr);
        if (cmd == NULL) {
            continue;  // Skip if no command was parsed
        }
	// Handle different commands based on the parsed command structure
        if (strcmp(cmd->command, "printenv") == 0) {
            process_printenv(cmd->parameter);
        } else if (strcmp(cmd->command, "setenv") == 0) {
            process_setenv(cmd->parameter);
        } else {
            printf("Unknown command: %s\n", cmd->command);
        }

        // Free the allocated memory for the command structure
        free(cmd);
    } while (strcmp(commandStr, "quit") != 0);
}

// Main function to start the shell
int main() {
    handle_command();
    return 0;
}
