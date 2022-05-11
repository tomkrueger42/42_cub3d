#ifndef CUB3D_H
# define CUB3D_H

/* ************************************************************************** */
/* INCLUDES																	  */
/* ************************************************************************** */

# include "../libs/libft/includes/libft.h"
# include <mlx.h>

/* ************************************************************************** */
/* DEFINES																	  */
/* ************************************************************************** */



/* ************************************************************************** */
/* STRUCTS																	  */
/* ************************************************************************** */

typedef struct	s_vars
{
	void	*mlx;
	void	*win;
}	t_vars;

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_map
{
	char	**data;
	size_t	width;
	size_t	len;
	size_t	box_size;
}	t_map;

typedef struct s_player
{
	size_t	x_pos;
	size_t	y_pos;
	double	direction;
	size_t	size;
}	t_player;

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */


// draw.c
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

// minimap.c

#endif
