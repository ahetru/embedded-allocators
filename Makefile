NAME = libembedded_allocators.a
CC = gcc
FLAGS = -Wall -Wextra -Werror -g -MMD -MP

SRC_DIR = src
OBJ_DIR = obj
TEST_SRC = test/test.c

SRC = $(SRC_DIR)/bump.c \

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o) \

all: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(FLAGS) -c $< -o $@

test: all
	$(CC) $(FLAGS) $(TEST_SRC) -L. -lembedded_allocators -o test_runner

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME) test_runner test_runner.d

re: fclean all

.PHONY: all clean fclean re test
