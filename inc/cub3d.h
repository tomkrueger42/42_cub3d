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

# define MAP_CHARS		" 01NESW"
# define MOVEMENT_SPEED	4				// number of clicks to walk across tiles
# define ROTATION_SPEED	0.1
# define RAD			0.0174533
# define PI				3.1415926535
# define MINIMAP_SIZE	1200
# define WINDOW_WIDTH	1200
# define WINDOW_HEIGHT	1200

# define ESC_KEY		53
# define W_KEY			13
# define A_KEY			0
# define S_KEY			1
# define D_KEY			2
# define ARROW_LEFT_KEY	123
# define ARROW_RIGHT_KEY 124

# define HORI			1
# define VERTI			2


/* ************************************************************************** */
/* STRUCTS																	  */
/* ************************************************************************** */



typedef struct	s_graphics
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
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
	char	*north_walls;
	char	*east_walls;
	char	*south_walls;
	char	*west_walls;
	int		floor_color;
	int		ceiling_color;
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
	double	x_tile_play_pos;
	double	y_tile_play_pos;
	double	x_intersect_pos;
	double	y_intersect_pos;
	double	x_step;
	double	y_step;
	int	len_hit_hori;
	int	len_hit_verti;
	int	len_hit_wall;

}	t_ray;


/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */

// draw.c
void	my_mlx_pixel_put(t_graphics *data, int x, int y, int color);
int		create_trgb(unsigned char t, unsigned char r, unsigned char g,
			unsigned char b);

// graphics.c
t_graphics	*graphics(void);
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
t_map	*map(void);
void	free_map(void);

// minimap.c
void	render_minimap(void);

// player.c
t_player	*player(void);
void		free_player(void);
void		render_player(void);
void		move_player(int keycode);

// read_file.c
void	read_file(char *filename);

// style.c
t_style	*style(void);
void	free_style(void);

// utils.c
void	put_error_and_exit(char *msg, int exitcode);

#endif
