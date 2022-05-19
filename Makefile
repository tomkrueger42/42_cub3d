# **************************************************************************** #
#	General																	   #
# **************************************************************************** #

NAME		=	cub3d
CC			=	gcc
CFLAGS		+=	-Wall -Wextra -Werror -fsanitize=address
INC			=	-Iinc
DEP			=	./inc/cub3d.h
SRC_PATH	=	./src/
PREP		=	./objs
OBJ_PATH	=	./objs/
OBJS		=	$(addprefix $(OBJ_PATH), $(SRCS:.c=.o))

# **************************************************************************** #
#	Sources																	   #
# **************************************************************************** #

SRCS		=	minimap.c draw.c player.c utils.c main.c read_file.c parse_map.c

# **************************************************************************** #
#	Libraries																   #
# **************************************************************************** #

LIBFT_PATH	=	./libs/libft
LIBFT		=	-L$(LIBFT_PATH) -lft
LIBFT_INC	=	-I$(LIBFT_PATH)/includes

MINILIBX_PATH =	./libs/minilibx
MINILIBX	=	-framework OpenGL -framework AppKit -L$(MINILIBX_PATH) -lmlx
MINILIBX_INC =	-I$(MINILIBX_PATH)

LIBS		=	$(LIBFT) $(MINILIBX)

# **************************************************************************** #
#	Rules																	   #
# **************************************************************************** #

.PHONY: all clean fclean re

all: $(LIBFT_PATH)/libft.a $(MINILIBX_PATH)/mlx.a $(NAME)

$(NAME): $(PREP) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(DEP)
	$(CC) $(CFLAGS) $(INC) $(MINILIBX_INC) $(LIBFT_INC) -c $< -o $@

$(PREP):
	mkdir -p $(OBJ_PATH)

$(LIBFT_PATH)/libft.a:
	make -C $(LIBFT_PATH)

$(MINILIBX_PATH)/mlx.a:
	make -C $(MINILIBX_PATH)

clean:
	rm -rf $(OBJ_PATH)
	rm -f *.o *~
	rm -rf *.dSYM
	make clean -C $(LIBFT_PATH)
	make clean -C $(MINILIBX_PATH)

fclean: clean
	rm -rf $(NAME)
	rm -f $(LIBFT_PATH)/libft.a
	rm -f $(MINILIBX_PATH)/libmlx.a

re: fclean all