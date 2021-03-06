# **************************************************************************** #
#	General																	   #
# **************************************************************************** #

NAME		=	cub3D
CC			=	gcc
CFLAGS		+=	-Wall -Wextra -Werror #-g -fsanitize=address
INC			=	-Iinc
DEP			=	./inc/cub3d.h
SRC_PATH	=	./src/
PREP		=	./objs
OBJ_PATH	=	./objs/
OBJS		=	$(addprefix $(OBJ_PATH), $(SRCS:.c=.o))

# **************************************************************************** #
#	Sources																	   #
# **************************************************************************** #

SRCS		=	graphics.c\
				main.c\
				map_check.c map_parse.c map.c minimap.c\
				player.c\
				raycast.c\
				read_file.c\
				style.c\
				texture.c\
				utils.c

# **************************************************************************** #
#	Libraries																   #
# **************************************************************************** #

LIBFT_PATH	=	./libs/libft/libft.a
LIBFT		=	-L./libs/libft -lft
LIBFT_INC	=	-Ilibs/libft/includes

MLX42_PATH =	./libs/libmlx42/libmlx42.a
# MLX42		=	-L/opt/homebrew/Cellar/glfw/3.3.7/lib -I include -lglfw -L./libs/libmlx42 -lmlx42							# for compilation with glfw as a homebrew package
MLX42	=		-L./libs/libmlx42 -lmlx42 libs/libmlx42/libglfw3.a -framework Cocoa -framework OpenGL -framework IOKit		# for compilation with glfw as built library in libmlx42/
MLX42_INC =		-Ilibs/libmlx42/include/MLX42

# **************************************************************************** #
#	Rules																	   #
# **************************************************************************** #

.PHONY: all clean fclean re

all: $(LIBFT_PATH) $(MLX42_PATH) $(NAME)

$(NAME): $(PREP) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) $(MLX42)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(DEP)
	$(CC) $(CFLAGS) $(INC) $(LIBFT_INC) $(MLX42_INC) -c $< -o $@

$(PREP):
	mkdir -p $(OBJ_PATH)

$(LIBFT_PATH):
	make -C ./libs/libft/

$(MLX42_PATH):
	make -C ./libs/libmlx42

clean:
	rm -rf $(OBJ_PATH)
	rm -f *.o *~
	rm -rf *.dSYM
	make clean -C ./libs/libft
	make clean -C ./libs/libmlx42

fclean: clean
	rm -rf $(NAME)
	rm -f $(LIBFT_PATH)
	rm -f $(MLX42_PATH)

re: fclean all