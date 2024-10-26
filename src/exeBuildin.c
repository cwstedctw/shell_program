#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "myhdr.h"

extern char **environ;  // Declare to use environment variables

// Prints environment variables or a specific one
void process_printenv(char *parameter) {
    // If no parameter is provided, print all environment variables
    if (parameter == NULL || strlen(parameter) == 0) {
        char **env = environ;
        while (*env) {
            printf("%s\n", *env++);
        }
    } else {
        // Print the specific environment variable if it exists
        char *value = getenv(parameter);
        if (value) {
            printf("%s=%s\n", parameter, value);
        } else {
            printf("%s not found\n", parameter);
        }
    }
}

// Sets an environment variable based on input
void process_setenv(char *parameter) {
    char key[100], value[100];
    // Parse the input parameter in the format key=value
    if (sscanf(parameter, "%99[^=]=%99s", key, value) == 2) {
        // Set the environment variable
        setenv(key, value, 1);
        printf("Environment variable set: %s=%s\n", key, value);
    } else {
        printf("Invalid format. Use: key=value\n");
    }
}
