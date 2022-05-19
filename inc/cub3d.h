#ifndef CUB3D_H
# define CUB3D_H

/* ************************************************************************** */
/* INCLUDES																	  */
/* ************************************************************************** */

# include "libft.h"
# include <mlx.h>

/* ************************************************************************** */
/* DEFINES																	  */
/* ************************************************************************** */

# define MOVEMENT_SPEED	10
# define ROTATION_SPEED	0.1
# define RAD			0.0174533
# define PI				3.1415926535
# define MINIMAP_SIZE	500

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

typedef struct s_style
{
	char	*north_walls;
	char	*east_walls;
	char	*south_walls;
	char	*west_walls;
	int		floor_color;
	int		ceiling_color;
}	t_style;

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

// read_file.c
void	read_file(char *filename);
t_style	*style(void);

// parse_map.c
bool	parse_map(void);

// draw.c
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
int		create_trgb(unsigned char t, unsigned char r, unsigned char g,
			unsigned char b);

// minimap.c
t_map	*map(void);
int		key_hook(int keycode, t_vars *vars);
void	render_minimap(t_vars *vars);


// player.c
t_player	*player(void);
void		render_player(t_vars *vars);
void		move_player(int keycode);

// utils.c
void	put_error_and_exit(char *msg, int exitcode);

// map_read.c
t_style	*style(void);

#endif
