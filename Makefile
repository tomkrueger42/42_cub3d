NAME	=	cub3d
CC		=	gcc
CFLAGS	+=	-Wall -Wextra -Werror
DEP		= ./inc/cub3d.h
SRC_PATH =	./src/
PREP	=	objs
OBJ_PATH =	objs/
OBJS	=	$(addprefix $(OBJ_PATH), $(SRCS:.c=.o))
LIBFT	=	-L./libs/libft -lft
LIBFT_PATH = libs/libft/libft.a
LIBS	=	$(LIBFT)

SRCS 	=	new_project.c

.PHONY: all clean fclean re

all: $(LIBFT_PATH) $(NAME)

$(NAME): $(PREP) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(DEP)
	$(CC) $(CFLAGS) -c $< -o $@

$(PREP):
	mkdir -p $(OBJ_PATH)

$(LIBFT_PATH):
	make -C libs/libft/

clean:
	rm -rf $(OBJ_PATH)
	rm -f *.o *~
	rm -rf *.dSYM
	make clean -C libs/libft/

fclean: clean
	rm -rf $(NAME)
	rm -f libs/libft/libft.a

re: fclean all