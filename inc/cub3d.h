#ifndef CUB3D_H
# define CUB3D_H

/* ************************************************************************** */
/* INCLUDES																	  */
/* ************************************************************************** */

# include "libft.h"
# include <MLX42.h>

/* ************************************************************************** */
/* DEFINES																	  */
/* ************************************************************************** */

// modifyable
# define MVT_SPEED		6			// tiles per second
# define ROT_SPEED		2			// value 1 => 6 seconds for full 360
# define FOV			60
# define MINIMAP_SIZE	600
# define WINDOW_WIDTH	1440
# define WINDOW_HEIGHT	775

// constant
# define MAP_CHARS		" 01NESW"
# define RAD			0.0174533
# define PI				3.1415926535
# define NORTH			0
# define EAST			1
# define SOUTH			2
# define WEST			3
# define WHITE			0xffffffff
# define BLACK			0x000000ff
# define LIGHT_GREY		0xbbbbbbff
# define DARK_GREY		0x444444ff
# define YELLOW			0xffff00ff
# define RED			0xff0000ff
# define GREEN			0x00ff00ff
# define BLUE			0x0000ffff

/* ************************************************************************** */
/* STRUCTS																	  */
/* ************************************************************************** */

typedef struct	s_graphics
{
	mlx_t		*mlx;
	mlx_image_t	*image;
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
	mlx_texture_t	*texture[4];
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

typedef struct s_draw
{
	int		tex_x;
	int		tex_y;
	double	column_height;
	double	step;
	int		col_start;
	double	tex_pos;
}	t_draw;

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

// draw.c
int		create_trgb(unsigned char r, unsigned char g, unsigned char b,
			unsigned char t);

// graphics.c
t_graphics	*get_graphics(void);
void		free_graphics(void);

// intersect.c
int		wall_hit(double x, double y, double angle, int mode);
void	fan_out(int col_index, double radial);

// main.c
int	main(int argc, char **argv);

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
void		move_player(double add_to_x_pos, double add_to_y_pos);
void		rotate_player(double add_to_direction);

// raycast.c
double	horizontal_intersections(double angle);
double	vertical_intersections(double angle);

// read_file.c
void	read_file(int fd);

// style.c
t_style	*get_style(void);
void	free_style(void);

// utils.c
void	put_error_and_exit(char *msg);
long	now_ms(void);

#endif
