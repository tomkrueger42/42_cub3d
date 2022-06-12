#include "cub3d.h"
#include <stdio.h>
#include <math.h>

void	draw_ray(t_player *player, t_map *map);

t_player	*get_player(void)
{
	static t_player	*player;

	if (player == NULL)
	{
		player = ft_calloc(1, sizeof(t_player));
		if (player == NULL)
			put_error_and_exit("malloc failure in player()", 1);
	}
	return (player);
}

void	free_player(void)
{
	t_player	*ptr;

	ptr = get_player();
	ft_free((void **)&ptr);
}

void	render_player(void)
{
	int			x_px;
	int			y_px;
	t_player	*player;
	t_map		*map;

	player = get_player();
	map = get_map();
	y_px = - (player->size / 2);
	while (y_px < player->size / 2)
	{
		x_px = - (player->size / 2);
		while (x_px < player->size / 2)
		{
			mlx_put_pixel(get_graphics()->image, player->x_pos * map->tile_size + x_px, player->y_pos * map->tile_size + y_px, YELLOW);
			x_px++;
		}
		y_px++;
	}
	draw_ray(player, map);
}

void	draw_ray(t_player *player, t_map *map)
{
	double		x;
	double		y;
	double		xy;

	x = round(player->x_delta * map->tile_size * 2);
	y = round(player->y_delta * map->tile_size * 2);
	if (player->y_delta == 0)
		xy = __INT_FAST64_MAX__;
	else
		xy = player->x_delta / player->y_delta;
	while (x != 0 || y != 0)
	{
		mlx_put_pixel(get_graphics()->image, player->x_pos * map->tile_size + x, player->y_pos * map->tile_size + y, YELLOW);
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

void	move_player(double add_to_x_pos, double add_to_y_pos)
{
	t_player *player;

	player = get_player();
	if (wall_hit(player->x_pos + add_to_x_pos * MVT_SPEED, player->y_pos, 0, 0) == 0)
		player->x_pos += add_to_x_pos * MVT_SPEED;
	if (wall_hit(player->x_pos, player->y_pos + add_to_y_pos * MVT_SPEED, 0, 0) == 0)
		player->y_pos += add_to_y_pos * MVT_SPEED;
}

void	rotate_player(double add_to_direction)
{
	t_player	*player;

	player = get_player();
	player->direction += add_to_direction * ROT_SPEED;
	if (player->direction < 0 * PI)
		player->direction += 2 * PI;
	else if (player->direction >= 2 * PI)
		player->direction -= 2 * PI;
	player->x_delta = cos(player->direction);
	player->y_delta = sin(player->direction);
}
