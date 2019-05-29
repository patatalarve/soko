CC		=	gcc
CFLAGS		=	-Wall
CFLAGS		+=	-Werror
CFLAGS		+=	-Wextra
CFLAGS		+=	-I./includes
CFLAGS		+=	-lncurses

RM		=	rm -f

NAME		=	soko

## ressources
SRCS_DIR	=	src/
SRCS_FILES	=	main.c
SRCS_FILES	+= 	map.c

SRCS		=	$(addprefix $(SRCS_DIR), $(SRCS_FILES))

OBJS		=	$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) -o $(NAME) $(OBJS) $(CFLAGS) -g3
	@printf "[\033[0;36mbuilt\033[0m] % 32s\n" $(NAME) | tr ' ' '.'

%.o: %.c
	@$(CC) -c -o $@ $< $(CFLAGS)
	@printf "[\033[0;32mcompiled\033[0m] % 29s\n" $< | tr ' ' '.'

clean:
	@$(RM) $(OBJS)
	@printf "[\033[0;31mdeleted\033[0m] % 30s\n" $(OBJS) | tr ' ' '.'

fclean: clean
	@$(RM) $(NAME)
	@printf "[\033[0;31mdeleted\033[0m] % 30s\n" $(NAME) | tr ' ' '.'

re: fclean all


.PHONY: all clean fclean re
