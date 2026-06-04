NAME = embedded-allocators
CC = gcc
FLAGS = -Wall -Wextra -Werror -g -MMD -MP

SRC_DIR = src
OBJ_DIR = obj

SRC = $(SRC_DIR)/bump.c \

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o) \

all: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
