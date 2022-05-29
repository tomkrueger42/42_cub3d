#include "cub3d.h"
#include <math.h>
#include <stdio.h>

int		intersect_loop(void);
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
double	intersect_hori(void)
{
	double	dist;

	ray()->y_tile_play_pos = player()->y_pos - (int)player()->y_pos;
	if (sin(player()->direction) > 0)
	{
		ray()->y_intersect_pos = (int)player()->y_pos + 1;
		ray()->x_intersect_pos = player()->x_pos + ray()->y_tile_play_pos / tan(player()->direction);
		ray()->y_step = 1;
		ray()->x_step = 1 / tan(player()->direction);
	}
	else
	{
		ray()->y_intersect_pos = (int)player()->y_pos;
		ray()->x_intersect_pos = player()->x_pos - ray()->y_tile_play_pos / tan(player()->direction);
		ray()->y_step = -1;
		ray()->x_step = - (1 / tan(player()->direction));
	}
	dist = sqrt(pow(ray()->y_intersect_pos - player()->y_pos, 2) + pow(ray()->x_intersect_pos - player()->x_pos, 2));
	dist += sqrt(pow(ray()->y_step, 2) + pow(ray()->x_step, 2)) * intersect_loop();
	return (dist);
}

// returns the distance of the first vertical intersection with a wall
double	intersect_verti(void)
{
	double	dist;

	ray()->x_tile_play_pos = player()->x_pos - (int)player()->x_pos;
	if (cos(player()->direction) > 0)
	{
		ray()->x_intersect_pos = (int)player()->x_pos + 1;
		ray()->y_intersect_pos = player()->y_pos + ray()->x_tile_play_pos / cos(player()->direction) * sin(player()->direction);
		ray()->x_step = 1;
		ray()->y_step = tan(player()->direction);
	}
	else
	{
		ray()->x_intersect_pos = (int)player()->x_pos;
		ray()->y_intersect_pos = player()->y_pos - ray()->x_tile_play_pos / cos(player()->direction) * sin(player()->direction);
		ray()->x_step = -1;
		ray()->y_step = - (tan(player()->direction));
	}
	dist = sqrt(pow(ray()->y_intersect_pos - player()->y_pos, 2) + pow(ray()->x_intersect_pos - player()->x_pos, 2));
	dist += sqrt(pow(ray()->y_step, 2) + pow(ray()->x_step, 2)) * intersect_loop();
	return (dist);
}

// loops until hits a wall
int	intersect_loop(void)
{
	int	index;

	index = 0;
	// printf("x_step: %f, y_step: %f\n", ray()->x_step, ray()->y_step);
	while ((int)(ray()->y_intersect_pos + ray()->y_step * index) < map()->len
			&& (int)(ray()->y_intersect_pos + ray()->y_step * index) > 0
			&& (int)(ray()->x_intersect_pos + ray()->x_step * index) < map()->width
			&& (int)(ray()->x_intersect_pos + ray()->x_step * index) > 0)
	{
		// printf("index: %d\t%c\n", index, map()->data[(int)(ray()->y_intersect_pos + ray()->y_step * index)][(int)(ray()->x_intersect_pos + ray()->x_step * index)]);
		highlight((ray()->x_intersect_pos + ray()->x_step * index) * map()->tile_size, (ray()->y_intersect_pos + ray()->y_step * index) * map()->tile_size, 3, 0xFF0000);
		if (map()->data[(int)(ray()->y_intersect_pos + ray()->y_step * index)][(int)(ray()->x_intersect_pos + ray()->x_step * index)] == '1')
		{
			highlight((ray()->x_intersect_pos + ray()->x_step * index) * map()->tile_size, (ray()->y_intersect_pos + ray()->y_step * index) * map()->tile_size, 3, 0xFFFFFF);
			return (index);
		}
		index++;
	}
	return (0);
}

// calls both functions for horizontal and vertical intersections and compares the output
double	closest_wall(void)
{
	double	hori;
	double verti;

	hori = intersect_hori();
	verti = intersect_verti();
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
