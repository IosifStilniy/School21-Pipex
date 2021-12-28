SRCS	= ${wildcard *.c}

OBJS	= $(SRCS:.c=.o)

HEADS	= libft.h

NAME	= libft.a

LIBPATH	= ../

LIB		= $(addprefix $(LIBPATH), $(NAME))

GCC		= gcc -g -c -Wall -Wextra -Werror -MMD

AR		= ar -crs

RM		= rm -f

%.o: 		%.c	$(HEADS)
			$(GCC) $< -o $@

$(LIB):		$(OBJS)
			$(AR) $(LIB) $?

all:		$(NAME)

clean:
			$(RM) $(OBJS)

fclean: 	clean
			$(RM) $(wildcard *.d)
			$(RM) $(addprefix $(LIBPATH), $(NAME))

re:			fclean all

include		$(wildcard *.d)

.PHONY:		all clean fclean re