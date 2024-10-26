#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "myhdr.h"

// Executes two commands with a pipe between them
void execute_pipe_command(char *cmd1, char *cmd2) {
    int pipefd[2];
    pid_t pid1, pid2;

    // Create a pipe
    if (pipe(pipefd) == -1) {
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }

  // Fork the first child to execute the first command
    if ((pid1 = fork()) == 0) {
        close(pipefd[0]);  // Close unused read end
        dup2(pipefd[1], STDOUT_FILENO);  // Redirect stdout to the pipe
        close(pipefd[1]);
        execlp(cmd1, cmd1, (char *)NULL);
        perror("exec failed");
        exit(EXIT_FAILURE);
    } else if (pid1 < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    // Fork the second child to execute the second command
    if ((pid2 = fork()) == 0) {
        close(pipefd[1]);  // Close unused write end
        dup2(pipefd[0], STDIN_FILENO);  // Redirect stdin to the pipe
        close(pipefd[0]);
        execlp(cmd2, cmd2, (char *)NULL);
        perror("exec failed");
        exit(EXIT_FAILURE);
    } else if (pid2 < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
   
    // Close both ends of the pipe in the parent process
    close(pipefd[0]);
    close(pipefd[1]);
    // Wait for both child processes to finish
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}
