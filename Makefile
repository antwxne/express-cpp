##
## EPITECH PROJECT, 2023
## CPP_Template
## File description:
## Makefile
##


NAME	= a.out
TEST_NAME	=	unit_tests

SRC_DIR	=	Sources/
TESTS_DIR	=	Tests/

SRC	=	$(addprefix $(SRC_DIR), Main.cpp)
OBJ	=	$(SRC:.cpp=.o)
TESTS_SRC	=	$(addprefix $(TESTS_DIR), basic_assertions.cpp \
	basic_parameterized.cpp)
TESTS_OBJ	=	$(TESTS_SRC:.c=.o)

CC	=	g++
rm	?=	rm -f
CXXFLAGS	=	-Wall -Wextra -Werror
CPPFLAGS	=	
LDLIBS	=
LDFLAGS	=

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDLIBS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME) $(TEST_NAME)

re: fclean all

debug: CXXFLAGS += -g3 -O0
debug: re

tests_run: CXXFLAGS += -fprofile-arcs -ftest-coverage -g3 -O0
tests_run: LDLIBS += -lcriterion -lgcov
tests_run: SRC := $(filter-out $(addprefix $(SRC_DIR), Main.cpp), $(SRC))
tests_run: $(OBJ) $(TESTS_OBJ)
	$(CC) -o $(TEST_NAME) $(OBJ) $(TESTS_OBJ) $(LDFLAGS) $(LDLIBS)
	./$(TEST_NAME)

.PHONY: all clean fclean $(NAME) re debug tests_run
