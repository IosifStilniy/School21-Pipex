SRCS		=	main.c			\
				utils.c			\

B_SRCS		=	${wildcard *_bonus.c}

OBJS		=	$(SRCS:.c=.o)	

B_OBJS		=	$(B_SRCS:.c=.o)	

HEADS		=	pipex.h

B_HEADS		=	pipex_bonus.h

LIBNAME		=	libft.a

LIB			=	libft

NAME		=	pipex

GCC			=	gcc -g -Wall -Wextra -Werror -MMD

RM			=	rm -f

%.o: 		%.c
			$(GCC) -c -I$(LIB) $< -o $@

$(NAME):	$(HEADS) $(OBJS) $(LIBNAME)
			$(GCC) $(OBJS) $(LIBNAME) -o $(NAME)

all:		$(NAME)

$(LIBNAME):	lib

lib:		
			@$(MAKE) -C $(LIB)

bonus:		$(B_HEADS) $(B_OBJS) $(LIBNAME)
			$(GCC) $(B_OBJS) $(LIBNAME) -o $(NAME)

clean:
			@$(MAKE) -C $(LIB) clean
			$(RM) $(OBJS)
			$(RM) $(B_OBJS)

fclean: 	clean
			@$(MAKE) -C $(LIB) fclean
			$(RM) $(wildcard *.d)
			$(RM) $(NAME)

re:			fclean all

include		$(wildcard *.d)

.PHONY:		all bonus clean fclean re lib