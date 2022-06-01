#include "cub3d.h"
#include <math.h>
#include <stdio.h>

#define HORI 1
#define VERTI 2

int		intersect_loop(double angle, int mode);
void	highlight(int x, int y, int size, int color);

t_ray	*ray(void)
{
	static t_ray	*ray;

	if (ray == NULL)
	{
		ray = ft_calloc(1, sizeof(t_ray));
		if (ray == NULL)
			put_error_and_exit("malloc failure in player()", 1);
	}
	return (ray);
}

// returns the distance of the first horizontal intersection with a wall
double	intersect_hori(double angle)
{
	double	dist;

	ray()->y_tile_play_pos = player()->y_pos - (int)player()->y_pos;
	if (sin(angle) > 0)
	{
		ray()->y_intersect_pos = (int)player()->y_pos + 1;
		ray()->x_intersect_pos = player()->x_pos + ray()->y_tile_play_pos / tan(angle);
		ray()->y_step = 1;
		ray()->x_step = 1 / tan(angle);
	}
	else
	{
		ray()->y_intersect_pos = (int)player()->y_pos;
		ray()->x_intersect_pos = player()->x_pos - ray()->y_tile_play_pos / tan(angle);
		ray()->y_step = -1;
		ray()->x_step = - (1 / tan(angle));
	}
	dist = sqrt(pow(ray()->y_intersect_pos - player()->y_pos, 2) + pow(ray()->x_intersect_pos - player()->x_pos, 2));
	dist += sqrt(pow(ray()->y_step, 2) + pow(ray()->x_step, 2)) * intersect_loop(angle, HORI);
	return (dist);
}

// returns the distance of the first vertical intersection with a wall
double	intersect_verti(double angle)
{
	double	dist;

	ray()->x_tile_play_pos = player()->x_pos - (int)player()->x_pos;
	if (cos(angle) > 0)
	{
		ray()->x_intersect_pos = (int)player()->x_pos + 1;
		ray()->y_intersect_pos = player()->y_pos + ray()->x_tile_play_pos * tan(angle);
		ray()->x_step = 1;
		ray()->y_step = tan(angle);
	}
	else
	{
		ray()->x_intersect_pos = (int)player()->x_pos;
		ray()->y_intersect_pos = player()->y_pos - ray()->x_tile_play_pos * tan(angle);
		ray()->x_step = -1;
		ray()->y_step = - (tan(angle));
	}
	dist = sqrt(pow(ray()->y_intersect_pos - player()->y_pos, 2) + pow(ray()->x_intersect_pos - player()->x_pos, 2));
	dist += sqrt(pow(ray()->y_step, 2) + pow(ray()->x_step, 2)) * intersect_loop(angle, VERTI);
	return (dist);
}

// checks whether a wall has been hit
int	wall_hit(double x, double y, double angle, int mode)
{
	if (sin(angle) < 0 && mode == HORI)
		y -= 0.1;
	if (cos(angle) < 0 && mode == VERTI)
		x -= 0.1;
	if (map()->data[(int)y][(int)x] == '1')
		return (1);
	return (0);
}

// loops until hits a wall
int	intersect_loop(double angle, int mode)
{
	int	index;

	index = 0;
	while ((int)(ray()->y_intersect_pos + ray()->y_step * index) < map()->len
			&& (int)(ray()->y_intersect_pos + ray()->y_step * index) > 0
			&& (int)(ray()->x_intersect_pos + ray()->x_step * index) < map()->width
			&& (int)(ray()->x_intersect_pos + ray()->x_step * index) > 0)
	{
		// highlight((ray()->x_intersect_pos + ray()->x_step * index) * map()->tile_size, (ray()->y_intersect_pos + ray()->y_step * index) * map()->tile_size, 3, 0xFF0000);
		if (wall_hit(ray()->x_intersect_pos + ray()->x_step * index, ray()->y_intersect_pos + ray()->y_step * index, angle, mode))
		{
			// highlight((ray()->x_intersect_pos + ray()->x_step * index) * map()->tile_size, (ray()->y_intersect_pos + ray()->y_step * index) * map()->tile_size, 3, 0xFFFFFF);
			return (index);
		}
		index++;
	}
	return (0);
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

void	fan_out(void)
{
	double	radial;

	radial = - FOV / 2;
	while (radial < FOV / 2)
	{
		draw_fov(player()->direction + radial * RAD, closest_wall(player()->direction + radial * RAD));
		radial += RAD;
	}
}
