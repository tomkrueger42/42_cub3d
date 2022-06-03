#include "cub3d.h"
#include <math.h>
#include <stdio.h>

#define HORI 1
#define VERTI 2

int		intersect_loop(t_ray r, double angle, int mode);
void	highlight(int x, int y, int size, int color);

// returns the distance of the first horizontal intersection with a wall
double	intersect_hori(double angle)
{
	double	dist;
	t_ray	r;

	r.y_tile_play_pos = player()->y_pos - (int)player()->y_pos;
	if (sin(angle) > 0)
	{
		r.y_intersect_pos = (int)player()->y_pos + 1;
		r.x_intersect_pos = player()->x_pos + (1 - r.y_tile_play_pos) / tan(angle);
		r.y_step = 1;
		r.x_step = 1 / tan(angle);
	}
	else
	{
		r.y_intersect_pos = (int)player()->y_pos;
		r.x_intersect_pos = player()->x_pos - r.y_tile_play_pos / tan(angle);
		r.y_step = -1;
		r.x_step = - (1 / tan(angle));
	}
	dist = sqrt(pow(r.y_intersect_pos - player()->y_pos, 2) + pow(r.x_intersect_pos - player()->x_pos, 2));
	int	loop = intersect_loop(r, angle, HORI);
	dist += sqrt(pow(r.y_step, 2) + pow(r.x_step, 2)) * (double)loop;
	return (dist);
}

// returns the distance of the first vertical intersection with a wall
double	intersect_verti(double angle)
{
	double	dist;
	t_ray	r;

	r.x_tile_play_pos = player()->x_pos - (int)player()->x_pos;
	if (cos(angle) > 0)
	{
		r.x_intersect_pos = (int)player()->x_pos + 1;
		r.y_intersect_pos = player()->y_pos + (1 - r.x_tile_play_pos) * tan(angle);
		r.x_step = 1;
		r.y_step = tan(angle);
	}
	else
	{
		r.x_intersect_pos = (int)player()->x_pos;
		r.y_intersect_pos = player()->y_pos - r.x_tile_play_pos * tan(angle);
		r.x_step = -1;
		r.y_step = - (tan(angle));
	}
	dist = sqrt(pow(r.y_intersect_pos - player()->y_pos, 2) + pow(r.x_intersect_pos - player()->x_pos, 2));
	dist += sqrt(pow(r.y_step, 2) + pow(r.x_step, 2)) * (double)intersect_loop(r, angle, VERTI);
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
	if (map()->data[(int)y][(int)x] == '1')
		return (1);
	return (0);
}

// loops until hits a wall
int	intersect_loop(t_ray r, double angle, int mode)
{
	int	index;

	index = 0;
	while ((int)(r.y_intersect_pos + r.y_step * index) < map()->len
			&& (int)(r.y_intersect_pos + r.y_step * index) > 0
			&& (int)(r.x_intersect_pos + r.x_step * index) < map()->width
			&& (int)(r.x_intersect_pos + r.x_step * index) > 0)
	{
		// highlight((r.x_intersect_pos + r.x_step * index) * map()->tile_size, (r.y_intersect_pos + r.y_step * index) * map()->tile_size, 3, 0xFF0000);
		if (wall_hit(r.x_intersect_pos + r.x_step * index, r.y_intersect_pos + r.y_step * index, angle, mode))
		{
			// highlight((r.x_intersect_pos + r.x_step * index) * map()->tile_size, (r.y_intersect_pos + r.y_step * index) * map()->tile_size, 3, 0xFFFFFF);
			return (index);
		}
		index++;
	}
	return (index);
}

// calls both functions for horizontal and vertical intersections and compares the output
double	closest_wall(double angle)
{
	double	hori;
	double verti;

	hori = intersect_hori(angle);
	verti = intersect_verti(angle);
	if (hori < verti)
	{
		printf("hori is shorter with %f vs %f\n", hori, verti);
		return (hori);
	}
	else
	{
		printf("verti is shorter with %f vs %f\n", verti, hori);
		return (verti);
	}
}

// draws a box
void	highlight(int x, int y, int size, int color)
{
	int	x_step;
	int	y_step;

	y_step = - (size / 2);
	while (y_step <= size / 2)
	{
		x_step = - (size / 2);
		while (x_step <= size / 2)
		{
			my_mlx_pixel_put(graphics(), x + x_step, y + y_step, color);
			x_step++;
		}
		y_step++;
	}
}

void	draw_fov(double angle, double distance)
{
	double	x;
	double	y;
	double	xy;

	x = round(cos(angle) * distance * map()->tile_size);
	y = round(sin(angle) * distance * map()->tile_size);
	if (y == 0)
		xy = __INT_FAST64_MAX__;
	else
		xy = x / y;
	while (x != 0 || y != 0)
	{
		my_mlx_pixel_put(graphics(), player()->x_pos * map()->tile_size + x, player()->y_pos * map()->tile_size + y, 0xFFAA33);
		if (x > 0 && (y == 0 || (x / y >= xy && xy > 0) || (x / y < xy && xy < 0)))
			x--;
		else if (x < 0 && (y == 0 || (x / y <= xy && xy < 0) || (x / y > xy && xy > 0)))
			x++;
		else if (y > 0)
			y--;
		else if (y < 0)
			y++;
	}
}

void	draw_col(t_graphics *graphics_struct, double distance, int col_index)
{
	int		y;
	double	column_height;

	y = 0;
	column_height = 1 / distance * WINDOW_HEIGHT;
	while (y < column_height)
	{
		my_mlx_pixel_put(graphics_struct, col_index, y + (WINDOW_HEIGHT - column_height) / 2, 0xAAAAFF);
		y++;
	}
}

void	fan_out(void)
{
	double	radial = 0;
	double 	distance;
	int		col_index;

	col_index = 0;

	radial = - FOV / 2;
	while (radial < FOV / 2)
	{
		distance = closest_wall(player()->direction + radial * RAD);
		draw_col(graphics(), cos(radial * RAD) * distance, col_index);
		draw_fov(player()->direction + radial * RAD, distance);
		col_index++;
		radial += (double)FOV / (double)WINDOW_WIDTH;
	}
	mlx_put_image_to_window(graphics()->mlx, graphics()->win, graphics()->img, 0, 0);
}
