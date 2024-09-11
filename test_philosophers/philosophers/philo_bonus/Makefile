SRC			=	main_bonus.c \
				dinner_bonus.c \
				atoi_bonus.c \
				error_bonus.c \
				sleep_bonus.c \
				parse_bonus.c \
				init_bonus.c \
				one_bonus.c

GREEN		=	'\033[32m'
NONE		=	'\033[0m'
CC			=	cc
NAME		=	philo_bonus
OBJ			=	$(SRC:.c=.o)
CFLAGS		=	-Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c philos_bonus.h struct_bonus.h
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: clean
