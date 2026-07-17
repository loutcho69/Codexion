NAME    = codexion

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -pthread

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = includes

SRCS    = main.c \
          parsing.c \
          init.c \
          time_utils.c \
          log.c \
          heap.c \
          dongle.c \
          coder.c \
          monitor.c \
          cleanup.c

OBJS    = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
DEPS    = $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -MMD -MP -I$(INC_DIR) -c $< -o $@

-include $(DEPS)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re