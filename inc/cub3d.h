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

// modifyable
# define MOVEMENT_SPEED	5				// number of clicks to walk across tiles
# define ROTATION_SPEED	0.1
# define FOV			66
# define MINIMAP_SIZE	600
# define WINDOW_WIDTH	1440
# define WINDOW_HEIGHT	775
# define TEX_HEIGHT		64
# define TEX_WIDTH		64

// constant
# define MAP_CHARS		" 01NESW"
# define RAD			0.0174533
# define PI				3.1415926535
# define NORTH			0
# define EAST			1
# define SOUTH			2
# define WEST			3

// keys
# define ESC_KEY		53
# define W_KEY			13
# define A_KEY			0
# define S_KEY			1
# define D_KEY			2
# define ARROW_LEFT_KEY	123
# define ARROW_RIGHT_KEY 124

/* ************************************************************************** */
/* STRUCTS																	  */
/* ************************************************************************** */

typedef struct	s_imgint
{
	void	*img;
	int		*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		img_width;
	int		img_height;
}	t_imgint;

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct	s_graphics
{
	void	*mlx;
	void	*win;
	t_img	image;
}	t_graphics;

typedef struct s_map
{
	char	**data;
	int		width;
	int		len;
	int		tile_size;
}	t_map;

typedef struct s_style
{
	char			*north_walls;
	char			*east_walls;
	char			*south_walls;
	char			*west_walls;
	int				textures[4][TEX_HEIGHT * TEX_WIDTH];
	int				tex_width[4];
	int				tex_height[4];
	unsigned int	floor_color;
	unsigned int	ceiling_color;
}	t_style;

typedef struct s_player
{
	double	x_pos;
	double	y_pos;
	double	x_delta;
	double	y_delta;
	double	direction;
	double	speed;
	int		size;
}	t_player;


typedef struct s_ray
{
	double	tile_play_pos;
	double	x_intersect_pos;
	double	y_intersect_pos;
	double	x_step;
	double	y_step;
}	t_ray;


/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

// draw.c
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
int		create_trgb(unsigned char t, unsigned char r, unsigned char g,
			unsigned char b);

// graphics.c
t_graphics	*get_graphics(void);
void		free_graphics(void);

// main.c
int	main(void);

// map_check.c
int	map_check(char **map);
int	player_check(char **map);

// map_parse.c
char	*find_map(char *lines);
void	count_dimensions(char **data);
void	fill_rows_with_spaces(char **data);
void	print_map(void);

// map.c
t_map	*get_map(void);
void	free_map(void);

// minimap.c
void	render_minimap(void);

// player.c
t_player	*get_player(void);
void		free_player(void);
void		render_player(void);
void		move_player(int keycode);

// read_file.c
void	read_file(char *filename);

// style.c
t_style	*get_style(void);
void	free_style(void);

// utils.c
void	put_error_and_exit(char *msg, int exitcode);

#endif
