#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "myhdr.h"

// Parses a command string and returns a command structure
command_t *parser_command(char *commandStr) {
    // Allocate memory for the command structure
    command_t *cmd = (command_t *)malloc(sizeof(command_t));
    if (cmd == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Initialize command and parameter fields to zero
    memset(cmd->command, 0, sizeof(cmd->command));
    memset(cmd->parameter, 0, sizeof(cmd->parameter));

    // Parse the command string into command and parameter parts
    if (sscanf(commandStr, "%99s %99[^\n]", cmd->command, cmd->parameter) < 1) {
        fprintf(stderr, "No command found\n");
        free(cmd);
        return NULL;
    }

    return cmd;
}
