/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkruger <tkruger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 17:10:22 by tkruger           #+#    #+#             */
/*   Updated: 2022/06/19 17:10:23 by tkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void	draw_box(int x_pos, int y_pos, t_map *map, t_graphics *graphics);
void	draw_ray(t_map *map, t_player *player, t_graphics *graphics);
void	render_player(t_map *map, t_player *player, t_graphics *graphics);

void	render_minimap(void)
{
	int			x_pos;
	int			y_pos;
	t_map		*map;
	t_player	*player;
	t_graphics	*graphics;

	y_pos = 0;
	map = get_map();
	player = get_player();
	graphics = get_graphics();
	while (y_pos < map->len)
	{
		x_pos = 0;
		while (x_pos < map->width)
			draw_box(x_pos++, y_pos, map, graphics);
		y_pos++;
	}
	render_player(map, player, graphics);
}

void	draw_box(int x_pos, int y_pos, t_map *map, t_graphics *graphics)
{
	int		x_px;
	int		y_px;
	size_t	color;

	y_px = 0;
	while (y_px < map->tile_size - 0)
	{
		x_px = 0;
		while (x_px < map->tile_size - 0)
		{
			if (map->data[y_pos][x_pos] == '1')
				color = DARK_GREY;
			else if (map->data[y_pos][x_pos] == ' ')
				return ;
			else
				color = LIGHT_GREY;
			if (y_px == 0 || x_px == 0)
				color = BLACK;
			mlx_put_pixel(graphics->image, (x_pos * map->tile_size) + x_px,
				(y_pos * map->tile_size) + y_px, color);
			x_px++;
		}
		y_px++;
	}
}

void	render_player(t_map *map, t_player *player, t_graphics *graphics)
{
	int			x_px;
	int			y_px;

	y_px = - (player->size / 2);
	while (y_px < player->size / 2)
	{
		x_px = - (player->size / 2);
		while (x_px < player->size / 2)
		{
			mlx_put_pixel(graphics->image, player->x_pos * map->tile_size
				+ x_px, player->y_pos * map->tile_size + y_px, YELLOW);
			x_px++;
		}
		y_px++;
	}
	draw_ray(map, player, graphics);
}

void	draw_ray(t_map *map, t_player *player, t_graphics *graphics)
{
	double		x;
	double		y;
	double		xy;

	x = round(player->x_delta * map->tile_size);
	y = round(player->y_delta * map->tile_size);
	if (player->y_delta == 0)
		xy = __INT_FAST64_MAX__;
	else
		xy = player->x_delta / player->y_delta;
	while (x != 0 || y != 0)
	{
		mlx_put_pixel(graphics->image, player->x_pos * map->tile_size + x,
			player->y_pos * map->tile_size + y, YELLOW);
		if (x > 0
			&& (y == 0 || (x / y >= xy && xy > 0) || (x / y < xy && xy < 0)))
			x--;
		else if (x < 0
			&& (y == 0 || (x / y <= xy && xy < 0) || (x / y > xy && xy > 0)))
			x++;
		else if (y > 0)
			y--;
		else if (y < 0)
			y++;
	}
}
