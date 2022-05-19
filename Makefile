NAME		=	cub3d
CC			=	gcc
CFLAGS		+=	-Wall -Wextra -Werror -fsanitize=address
INC			=	-Iinc
DEP			=	./inc/cub3d.h
SRC_PATH	=	./src/
PREP		=	objs
OBJ_PATH	=	objs/
OBJS		=	$(addprefix $(OBJ_PATH), $(SRCS:.c=.o))
LIBFT		=	-L./libs/libft -lft
LIBFT_PATH	=	libs/libft/libft.a
LIBFT_INC	=	-Ilibs/libft/includes
MINILIBX	=	-framework OpenGL -framework AppKit -L./libs/minilibx -lmlx
MINILIBX_PATH =	libs/minilibx/libmlx.a
MINILIBX_INC =	-Imlx
LIBS		=	$(LIBFT) $(MINILIBX)

SRCS			= minimap.c draw.c player.c utils.c main.c read_file.c parse_map.c

.PHONY: all clean fclean re

all: $(LIBFT_PATH) $(MINILIBX_PATH) $(NAME)

# tom: $(PREP) $(OBJS_TOM)
# 	$(CC) $(CFLAGS) $(OBJS_TOM) -o $(NAME) $(LIBS)

$(NAME): $(PREP) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(DEP)
	$(CC) $(CFLAGS) $(INC) $(MINILIBX_INC) $(LIBFT_INC) -c $< -o $@

$(PREP):
	mkdir -p $(OBJ_PATH)

$(LIBFT_PATH):
	make -C libs/libft/

$(MINILIBX_PATH):
	make -C libs/minilibx/

clean:
	rm -rf $(OBJ_PATH)
	rm -f *.o *~
	rm -rf *.dSYM
	make clean -C libs/libft/
	make clean -C libs/minilibx/

fclean: clean
	rm -rf $(NAME)
	rm -f libs/libft/libft.a
	rm -f libs/minilibx/libmlx.a

re: fclean all