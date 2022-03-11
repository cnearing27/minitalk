SRCS_S		=	server_files/server.c 

SRCS_C		=	client_files/client.c \
				client_files/ft_atoi.c

HEADER		=	minitalk.h

OBJS_S		= $(SRCS_S:.c=.o)
OBJS_C		= $(SRCS_C:.c=.o)

NAME		= server
NAME_C		= client

CC			= cc
RM			= rm -f
FLAGS		= -Wall -Wextra -Werror -I.

all:	$(NAME) $(NAME_C)

$(NAME):		$(OBJS_S)
			$(MAKE) -C ft_printf/
			cp ft_printf/libftprintf.a $(NAME)
			$(CC) $(OBJS_S) ft_printf/libftprintf.a -o $(NAME)

$(NAME_C):		$(OBJS_C)
			$(CC) $(OBJS_C) -o $(NAME_C)

%.o:			%.c $(HEADER)
			$(CC) $(FLAGS) -c $< -o $@

clean:
			$(MAKE) clean -C ft_printf/
			$(RM) $(OBJS_S)
			$(RM) $(OBJS_C)

fclean:	clean
			$(MAKE) fclean -C ft_printf/
			$(RM) $(NAME)
			$(RM) $(NAME_C)

re:		fclean all

.PHONY: all clean fclean re