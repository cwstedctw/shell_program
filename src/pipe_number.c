#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "myhdr.h"

#define MAX_PIPE 100

command_t pipe_buffer[MAX_PIPE];
int pipe_count = 0;

// Processes a command with a delayed pipe
void process_number_pipe(command_t *cmd) {
    int delay = cmd->delay;
    if (delay > 0) {
        // Check if the pipe buffer is full
        if (pipe_count < MAX_PIPE) {
            pipe_buffer[pipe_count++] = *cmd;
            printf("Command '%s' will be executed in %d commands later\n", cmd->command, delay);
        } else {
            fprintf(stderr, "Pipe buffer full, cannot add more commands\n");
        }
    }
}

// Executes a given command
void execute_command(command_t *cmd) {
    if (cmd != NULL) {
        printf("Executing command: %s\n", cmd->command);
    }
}
