#include "cub3d.h"
#include <math.h>

#define HORI 1
#define VERTI 2

int		intersect_loop(t_ray r, double angle, int mode);

// returns the distance of the first horizontal intersection with a wall
double	horizontal_intersections(double angle)
{
	double		dist;
	t_ray		r;
	t_player	*player;

	player = get_player();
	r.tile_play_pos = player->y_pos - (int)player->y_pos;
	if (sin(angle) > 0)
	{
		r.y_intersect_pos = (int)player->y_pos + 1;
		r.x_intersect_pos = player->x_pos + (1 - r.tile_play_pos) / tan(angle);
		r.y_step = 1;
		r.x_step = 1 / tan(angle);
	}
	else
	{
		r.y_intersect_pos = (int)player->y_pos;
		r.x_intersect_pos = player->x_pos - r.tile_play_pos / tan(angle);
		r.y_step = -1;
		r.x_step = -1 / tan(angle);
	}
	dist = sqrt(pow(r.y_intersect_pos - player->y_pos, 2) \
			+ pow(r.x_intersect_pos - player->x_pos, 2));
	dist += sqrt(pow(r.y_step, 2) + pow(r.x_step, 2)) \
			* intersect_loop(r, angle, HORI);
	return (dist);
}

// returns the distance of the first vertical intersection with a wall
double	vertical_intersections(double angle)
{
	double		dist;
	t_ray		r;
	t_player	*player;

	player = get_player();
	r.tile_play_pos = player->x_pos - (int)player->x_pos;
	if (cos(angle) > 0)
	{
		r.x_intersect_pos = (int)player->x_pos + 1;
		r.y_intersect_pos = player->y_pos + (1 - r.tile_play_pos) * tan(angle);
		r.x_step = 1;
		r.y_step = tan(angle);
	}
	else
	{
		r.x_intersect_pos = (int)player->x_pos;
		r.y_intersect_pos = player->y_pos - r.tile_play_pos * tan(angle);
		r.x_step = -1;
		r.y_step = -tan(angle);
	}
	dist = sqrt(pow(r.y_intersect_pos - player->y_pos, 2) \
			+ pow(r.x_intersect_pos - player->x_pos, 2));
	dist += sqrt(pow(r.y_step, 2) + pow(r.x_step, 2)) \
			* intersect_loop(r, angle, VERTI);
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
		if (wall_hit(r.x_intersect_pos + r.x_step * index, \
				r.y_intersect_pos + r.y_step * index, angle, mode))
		{
			return (index);
		}
		index++;
	}
	return (index);
}
