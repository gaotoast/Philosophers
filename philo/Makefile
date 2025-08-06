NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror

RM = rm -f

SRCS = main.c init.c args.c simulate.c philo.c turn.c monitor.c utils.c clean_up.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
