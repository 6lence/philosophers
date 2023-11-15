SRC_DIR := ./src
SRC_FILES :=	main.c \
				ft_main_loop.c \
				ft_arguments.c 

OBJ_DIR := ./obj
EXECUTABLE := philo

# Generate a list of object files with paths
OBJ_FILES := $(addprefix $(OBJ_DIR)/,$(SRC_FILES:.c=.o))

# Compiler and compiler flags
CC := gcc
CFLAGS := -Wall -Werror -Wextra -g -pthread

RM := rm -f

all: $(OBJ_DIR) $(EXECUTABLE)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(EXECUTABLE): $(OBJ_FILES)
	@$(CC) $(CFLAGS) $^ -o $@ 
	@echo "\033[32m✅ Done! Executable $(EXECUTABLE) is ready.\033[0m"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) -r $(OBJ_DIR)
	@echo "\033[32m✅ Done! Object files removed.\033[0m"

fclean: clean
	@$(RM) $(EXECUTABLE)
	@echo "\033[32m✅ Done! Executable $(EXECUTABLE) removed.\033[0m"

re: fclean all

.PHONY: all clean fclean re
