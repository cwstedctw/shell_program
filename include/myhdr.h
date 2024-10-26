#ifndef MY_HDR_H
#define MY_HDR_H      /* Prevent accidental double inclusion */

/* Custom types and structures */
typedef struct {
    char command[100];
    char parameter[100];
    int delay;
} command_t;

/* Function declarations */
command_t *parser_command(char *commandStr); // parser.c: Parses a command string and returns a command structure
void process_printenv(char *parameter); // exeBuildin.c: Prints environment variables or a specific one
void process_setenv(char *parameter); // exeBuildin.c: Sets an environment variable based on input
void execute_external_command(char *command, char *parameter); // path.c: Executes an external command
void execute_pipe_command(char *cmd1, char *cmd2); // pipe_command.c: Executes two commands with a pipe between them
void process_number_pipe(command_t *cmd); // pipe_number.c: Processes a command with a delayed pipe
void execute_command(command_t *cmd); // pipe_number.c: Executes a given command
void check_and_run_pipes(); // pipe_number.c: Checks and runs any pending pipe commands

#endif /* MY_HDR_H */
