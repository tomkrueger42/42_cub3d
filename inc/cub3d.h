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

# define MOVEMENT_SPEED	10
# define RAD			0.0174533
# define PI				3.1415926535
#define	MAPWIN			500

/* ************************************************************************** */
/* STRUCTS																	  */
/* ************************************************************************** */

typedef struct	s_vars
{
	void	*mlx;
	void	*win;
}	t_vars;

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_map
{
	char	**data;
	int		width;
	int		len;
	int		box_size;
	t_img	*minimap;
}	t_map;

typedef struct s_player
{
	int		x_pos;
	int		y_pos;
	double	x_del;
	double	y_del;
	double	direction;
	int		size;
}	t_player;

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */


// draw.c
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);

// minimap.c
t_map	*map(void);

// player.c
t_player	*player(void);
void		render_player(t_vars *vars);
void		move_player(int keycode);

// utils.c
void	put_error_and_exit(char *msg, int exitcode);


#endif
