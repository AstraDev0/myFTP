##
## EPITECH PROJECT, 2023
## B-MAT-400-BER-4-1-201yams-matthis.brocheton
## File description:
## Makefile
##

SRC		=	$(wildcard ./src/*.c)	\

OBJ		=	$(SRC:.c=.o)

NAME	=	myftp

LDFLAGS	=	-I ./include -g3 -lm

UNIT_TEST	=	./tests/unit_tests.c --coverage -lcriterion	\

$(NAME):
		gcc -o $(NAME) main.c $(SRC) $(LDFLAGS)

all:	$(NAME)

clean:
		rm -f $(OBJ)

fclean:	clean
		rm -f $(NAME)
		rm -f ./tests/*.vgcore
		rm -f ./tests/*.gcno
		rm -f ./tests/*.gcda
		rm -f ./tests/unit_tests

re:		fclean all

unit_tests:	fclean
		gcc -o ./tests/unit_tests $(UNIT_TEST) $(SRC) $(LDFLAGS)

tests_run:	unit_tests
		./tests/unit_tests

.PHONY:	re fclean clean all
