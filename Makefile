NAME		=	cub3d
CC			=	gcc
CFLAGS		+=	-Wall -Wextra -Werror -fsanitize=address
DEP			=	./inc/cub3d.h
SRC_PATH	=	./src/
PREP		=	objs
OBJ_PATH	=	objs/
OBJS_DAVINA	=	$(addprefix $(OBJ_PATH), $(SRCS_DAVINA:.c=.o))
OBJS_TOM	=	$(addprefix $(OBJ_PATH), $(SRCS_TOM:.c=.o))
OBJS		=	$(addprefix $(OBJ_PATH), $(SRCS:.c=.o))
LIBFT		=	-L./libs/libft -lft
LIBFT_PATH	=	libs/libft/libft.a
MINILIBX	=	-framework OpenGL -framework AppKit -L./libs/minilibx -lmlx
MINILIBX_PATH =	libs/minilibx/libmlx.a
MINILIBX_INC =	-Imlx
LIBS		=	$(LIBFT) $(MINILIBX)

# hier kannst du deine files eintragen und dann mit "make davina" builden. dadurch koennen wir beide zum beispiel eine main() funktion haben
SRCS_DAVINA		=	map_free_map.c map_read.c map_test.c map_helper.c

SRCS_TOM		=	minimap.c draw.c player.c utils.c

SRCS			= $(SRCS_DAVINA) $(SRCS_TOM)

.PHONY: all davina tom clean fclean re

all: $(LIBFT_PATH) $(MINILIBX_PATH) $(NAME)

davina: $(PREP) $(OBJS_DAVINA)
	$(CC) $(CFLAGS) $(OBJS_DAVINA) -o $(NAME) $(LIBS)

tom: $(PREP) $(OBJS_TOM)
	$(CC) $(CFLAGS) $(OBJS_TOM) -o $(NAME) $(LIBS)

$(NAME): $(PREP) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(DEP)
	$(CC) $(CFLAGS) $(MINILIBX_INC) -c $< -o $@

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