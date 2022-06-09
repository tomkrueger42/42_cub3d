#include "cub3d.h"
#include <math.h>
#include <stdio.h>

#define HORI 1
#define VERTI 2

int		intersect_loop(t_ray r, double angle, int mode);

// returns the distance of the first horizontal intersection with a wall
double	horizontal_intersections(double angle)
{
	double	dist;
	t_ray	r;

	r.tile_play_pos = get_player()->y_pos - (int)get_player()->y_pos;
	if (sin(angle) > 0)
	{
		r.y_intersect_pos = (int)get_player()->y_pos + 1;
		r.x_intersect_pos = get_player()->x_pos + (1 - r.tile_play_pos) / tan(angle);
		r.y_step = 1;
		r.x_step = 1 / tan(angle);
	}
	else
	{
		r.y_intersect_pos = (int)get_player()->y_pos;
		r.x_intersect_pos = get_player()->x_pos - r.tile_play_pos / tan(angle);
		r.y_step = -1;
		r.x_step = - (1 / tan(angle));
	}
	dist = sqrt(pow(r.y_intersect_pos - get_player()->y_pos, 2) + pow(r.x_intersect_pos - get_player()->x_pos, 2));
	dist += sqrt(pow(r.y_step, 2) + pow(r.x_step, 2)) * intersect_loop(r, angle, HORI);
	return (dist);
}

// returns the distance of the first vertical intersection with a wall
double	vertical_intersections(double angle)
{
	double	dist;
	t_ray	r;

	r.tile_play_pos = get_player()->x_pos - (int)get_player()->x_pos;
	if (cos(angle) > 0)
	{
		r.x_intersect_pos = (int)get_player()->x_pos + 1;
		r.y_intersect_pos = get_player()->y_pos + (1 - r.tile_play_pos) * tan(angle);
		r.x_step = 1;
		r.y_step = tan(angle);
	}
	else
	{
		r.x_intersect_pos = (int)get_player()->x_pos;
		r.y_intersect_pos = get_player()->y_pos - r.tile_play_pos * tan(angle);
		r.x_step = -1;
		r.y_step = - (tan(angle));
	}
	dist = sqrt(pow(r.y_intersect_pos - get_player()->y_pos, 2) + pow(r.x_intersect_pos - get_player()->x_pos, 2));
	dist += sqrt(pow(r.y_step, 2) + pow(r.x_step, 2)) * intersect_loop(r, angle, VERTI);
	return (dist);
}

// checks whether a wall has been hit
int	wall_hit(double x, double y, double angle, int mode)
{
	if (sin(angle) < 0 && mode == HORI)
	{
		y -= 1;
	}
	if (cos(angle) < 0 && mode == VERTI)
	{
		x -= 1;
	}
	if (get_map()->data[(int)y][(int)x] == '1')
		return (1);
	return (0);
}

// loops until hits a wall
int	intersect_loop(t_ray r, double angle, int mode)
{
	int	index;

	index = 0;
	while ((int)(r.y_intersect_pos + r.y_step * index) < get_map()->len
			&& (int)(r.y_intersect_pos + r.y_step * index) > 0
			&& (int)(r.x_intersect_pos + r.x_step * index) < get_map()->width
			&& (int)(r.x_intersect_pos + r.x_step * index) > 0)
	{
		if (wall_hit(r.x_intersect_pos + r.x_step * index, r.y_intersect_pos + r.y_step * index, angle, mode))
		{
			return (index);
		}
		index++;
	}
	return (index);
}

void get_tex(double angle, double dist, int col_index, int wall_dir)
{
	double	wallx;
	double	texx;
	double	step;
	double	y;
	t_style	*style;
	double	column_height;

	column_height = 1 / dist * WINDOW_HEIGHT;
	style = get_style();
	if (wall_dir == NORTH || wall_dir == SOUTH)
		wallx = cos(angle) * dist + get_player()->x_pos;
	else
		wallx = sin(angle) * dist + get_player()->y_pos;
	wallx -= floor(wallx);
	texx = (int)(wallx * (double)TEX_WIDTH);
	step = (double)TEX_HEIGHT / column_height;
	// printf("wallx: %f, texx: %f, step: %f\n", wallx, texx, step);
	y = 0;
	while (y < (WINDOW_HEIGHT - column_height) / 2)
		my_mlx_pixel_put(&get_graphics()->image, col_index, y++, style->ceiling_color);
	while (y < (WINDOW_HEIGHT - column_height) / 2 + column_height && y < WINDOW_HEIGHT)
	{
		my_mlx_pixel_put(&get_graphics()->image, col_index, y, style->textures[wall_dir][(int)((TEX_HEIGHT * texx) + (y - (WINDOW_HEIGHT - column_height) / 2) * step)]);
		y++;
	}
	while (y < WINDOW_HEIGHT)
		my_mlx_pixel_put(&get_graphics()->image, col_index, y++, style->floor_color);
}

void	fan_out(void)
{
	double	radial;
	double 	dist_hori;
	double 	dist_verti;
	int		col_index;
	double	angle;

	col_index = 0;
	radial = - FOV / 2;
	while (radial < FOV / 2)
	{
		angle = get_player()->direction + radial * RAD;
		dist_hori = cos(radial * RAD) * horizontal_intersections(angle);
		dist_verti = cos(radial * RAD) * vertical_intersections(angle);
		if (dist_hori < dist_verti && sin(angle) < 0)
			get_tex(angle, dist_hori, col_index, NORTH);
		else if (dist_verti < dist_hori && cos(angle) > 0)
			get_tex(angle, dist_verti, col_index, EAST);
		else if (dist_hori < dist_verti && sin(angle) > 0)
			get_tex(angle, dist_hori, col_index, SOUTH);
		else if (dist_verti < dist_hori && cos(angle) < 0)
			get_tex(angle, dist_verti, col_index, WEST);
		// if (dist_hori < dist_verti && sin(angle) < 0)
		// 	draw_col(&get_graphics()->image, cos(radial * RAD) * dist_hori, col_index, get_tex(angle, dist_hori, NORTH));
		// else if (dist_verti < dist_hori && cos(angle) > 0)
		// 	draw_col(&get_graphics()->image, cos(radial * RAD) * dist_verti, col_index, get_tex(angle, dist_verti, EAST));
		// else if (dist_hori < dist_verti && sin(angle) > 0)
		// 	draw_col(&get_graphics()->image, cos(radial * RAD) * dist_hori, col_index, get_tex(angle, dist_hori, SOUTH));
		// else if (dist_verti < dist_hori && cos(angle) < 0)
		// 	draw_col(&get_graphics()->image, cos(radial * RAD) * dist_verti, col_index, get_tex(angle, dist_verti, WEST));
		col_index++;
		radial += (double)FOV / (double)WINDOW_WIDTH;
	}
}
