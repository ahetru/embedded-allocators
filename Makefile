NAME = libembedded_allocators.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -MMD -MP

SRC_DIR = src
OBJ_DIR = obj

UNITY_DIR = test/Unity/src
UNITY_SRC = $(UNITY_DIR)/unity.c
UNITY_INC = -I$(UNITY_DIR)

TEST_SRC = test/test.c
TEST_RUNNER = test_runner

SRC = \
	$(SRC_DIR)/bump.c

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

DEP = $(OBJ:.o=.d)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $@ $^

$(OBJ_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_RUNNER): $(NAME) $(TEST_SRC) $(UNITY_SRC)
	$(CC) $(CFLAGS) \
		$(UNITY_INC) \
		$(TEST_SRC) \
		$(UNITY_SRC) \
		-L. -lembedded_allocators \
		-o $@

test: $(TEST_RUNNER)

run_test: $(TEST_RUNNER)
	./$(TEST_RUNNER)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME) $(TEST_RUNNER) $(TEST_RUNNER).d

re: fclean all

-include $(DEP)

.PHONY: all test run_test clean fclean re
