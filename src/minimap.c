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

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_box(t_data *img, int pos_x, int pos_y, t_map *map)
{
	size_t	x;
	size_t	y;
	int		color;

	y = 1;
	while (y < map->box_size - 1)
	{
		x = 1;
		while (x < map->box_size - 1)
		{
			if (map->data[pos_y][pos_x] == '0')
				color = 0x00bbbbbb;
			else if (map->data[pos_y][pos_x] == '1')
				color = 0x00444444;
			else if (map->data[pos_y][pos_x] == ' ')
				color = 0xFF000000;
			my_mlx_pixel_put(img, (pos_x * map->box_size) + x, (pos_y * map->box_size) + y, color);
			x++;
		}
		y++;
	}
}

t_data	render_map(t_vars vars, t_map *map)
{
	t_data	img;
	size_t	x;
	size_t	y;

	img.img = mlx_new_image(vars.mlx, MAPWIN, MAPWIN);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	y = 0;
	while (y < map->len)
	{
		x = 0;
		while (x < map->width)
		{
			draw_box(&img, x, y, map);
			x++;
		}
		y++;
	}
	return (img);
}

int	main(void)
{
	t_map	*map;
	t_vars	vars;

	map = make_map();
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, map->width * map->box_size, map->len * map->box_size, "cub3d minimap");
	mlx_put_image_to_window(vars.mlx, vars.win, render_map(vars, map).img, 0, 0);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_loop(vars.mlx);
}
