#include <stdio.h>
#include "../inc/cub3d.h"
#include <stdlib.h>

#define	MAPWIN 500

t_map *make_map(void)
{
	t_map	*map;

	map = ft_calloc(1, sizeof(t_map));
	if (map == NULL)
		return (NULL);
	map->data = ft_calloc(10, sizeof(char *));
	map->data[0] = ft_strdup("1111111");
	map->data[1] = ft_strdup("1 01001");
	map->data[2] = ft_strdup("1001101");
	map->data[3] = ft_strdup("11 1 00");
	map->data[4] = ft_strdup("1111111");
	map->data[5] = ft_strdup("       ");
	map->data[6] = ft_strdup("0000000");
	map->data[7] = ft_strdup("0001010");
	map->data[8] = ft_strdup("1110101");
	map->data[9] = NULL;
	map->width = 7;
	map->len = 9;
	if (map->width > map->len)
		map->box_size = MAPWIN / map->width;
	else
		map->box_size = MAPWIN / map->len;
	return (map);
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
}

void	draw_box(t_data *minimap, int x_pos, int y_pos, t_map *map)
{
	size_t	x_px;
	size_t	y_px;
	int		color;

	y_px = 1;
	while (y_px < map->box_size - 1)
	{
		x_px = 1;
		while (x_px < map->box_size - 1)
		{
			if (map->data[y_pos][x_pos] == '1')							// wall
				color = 0x00444444;
			else if (map->data[y_pos][x_pos] == ' ')					// transparent
				color = 0xFF000000;
			else
				color = 0x00bbbbbb;										// ground below player / sprite
			my_mlx_pixel_put(minimap, (x_pos * map->box_size) + x_px,
				(y_pos * map->box_size) + y_px, color);
			x_px++;
		}
		y_px++;
	}
}

void	render_minimap(t_map *map, t_data *minimap)
{
	size_t	x_pos;
	size_t	y_pos;

	y_pos = 0;
	while (y_pos < map->len)
	{
		x_pos = 0;
		while (x_pos < map->width)
		{
			draw_box(minimap, x_pos, y_pos, map);
			x_pos++;
		}
		y_pos++;
	}
}

t_player *player_init(t_map *map)
{
	t_player	*player;

	player = ft_calloc(1, sizeof(t_player));
	if (player == NULL)
		exit(123);
	player->x_pos = 300;
	player->y_pos = 300;
	player->direction = 0.5;
	player->size = map->box_size / 2;
	return (player);
}

void	render_player(t_player *player, t_data *minimap)
{
	int	x_px;
	int	y_px;

	y_px = - (player->size / 2);
	while (y_px < (int)(player->size / 2))
	{
		x_px = - (player->size / 2);
		while (x_px < (int)(player->size / 2))
		{
			my_mlx_pixel_put(minimap, player->x_pos + x_px, player->y_pos + y_px, 0xffff00);
			x_px++;
		}
		y_px++;
	}
}

int	main(void)
{
	t_map		*map;
	t_vars		vars;
	t_data		*minimap;
	t_player	*player;

	map = make_map();
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, map->width * map->box_size, map->len * map->box_size, "cub3d minimap");
	minimap = ft_calloc(1, sizeof(t_data));
	if (minimap == NULL)
		return (12);
	minimap->img = mlx_new_image(vars.mlx, MAPWIN, MAPWIN);
	minimap->addr = mlx_get_data_addr(minimap->img, &minimap->bits_per_pixel, &minimap->line_length, &minimap->endian);
	render_minimap(map, minimap);
	player = player_init(map);	// this is done by davina
	render_player(player, minimap);
	mlx_put_image_to_window(vars.mlx, vars.win, minimap->img, 0, 0);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_loop(vars.mlx);
}
