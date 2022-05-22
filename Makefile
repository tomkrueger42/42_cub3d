# **************************************************************************** #
#	General																	   #
# **************************************************************************** #

NAME		=	cub3d
CC			=	gcc
CFLAGS		+=	-Wall -Wextra -Werror -g -fsanitize=address
INC			=	-Iinc
DEP			=	./inc/cub3d.h
SRC_PATH	=	./src/
PREP		=	./objs
OBJ_PATH	=	./objs/
OBJS		=	$(addprefix $(OBJ_PATH), $(SRCS:.c=.o))

# **************************************************************************** #
#	Sources																	   #
# **************************************************************************** #

SRCS		=	draw.c\
				main.c\
				map_check.c map_parse.c map.c minimap.c\
				player.c\
				read_file.c\
				style.c\
				utils.c

# **************************************************************************** #
#	Libraries																   #
# **************************************************************************** #

LIBFT_PATH	=	./libs/libft/libft.a
LIBFT		=	-L./libs/libft -lft
LIBFT_INC	=	-Ilibs/libft/includes

MINILIBX_PATH =	./libs/minilibx/libmlx.a
MINILIBX	=	-framework OpenGL -framework AppKit -L./libs/minilibx -lmlx
MINILIBX_INC =	-Ilibs/minilibx

# **************************************************************************** #
#	Rules																	   #
# **************************************************************************** #

.PHONY: all clean fclean re

all: $(LIBFT_PATH) $(MINILIBX_PATH) $(NAME)

$(NAME): $(PREP) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) $(MINILIBX)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(DEP)
	$(CC) $(CFLAGS) $(INC) $(LIBFT_INC) $(MINILIBX_INC) -c $< -o $@

$(PREP):
	mkdir -p $(OBJ_PATH)

$(LIBFT_PATH):
	make -C ./libs/libft/

$(MINILIBX_PATH):
	make -C ./libs/minilibx

clean:
	rm -rf $(OBJ_PATH)
	rm -f *.o *~
	rm -rf *.dSYM
	make clean -C ./libs/libft
	make clean -C ./libs/minilibx

fclean: clean
	rm -rf $(NAME)
	rm -f $(LIBFT_PATH)
	rm -f $(MINILIBX_PATH)

re: fclean all