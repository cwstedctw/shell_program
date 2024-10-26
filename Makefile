# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Werror -Iinclude

# Source files
SRCS = src/main.c src/exeBuildin.c src/parser.c src/path.c src/pipe_command.c src/pipe_number.c

# Object files
OBJS = $(SRCS:src/%.c=obj/%.o)

# Output executable
TARGET = my_shell

# Default target
all: $(TARGET)

# Linking the object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compiling .c files to .o files in obj/ directory
obj/%.o: src/%.c
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target to remove compiled files
clean:
	rm -rf obj $(TARGET)

# PHONY targets
.PHONY: all clean

