NAME	= codexion

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -pthread

SRCS	= main.c \
		  parsing.c \
          parsing_utils.c \
		  init.c \
		  coder.c \
		  monitor.c \
          monitor_utils.c \
		  heap.c \
          heap_utils.c \
          heap_utils2.c \
          time_utils.c \
          utils.c \
		  cleanup.c

OBJS	= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c codexion.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re