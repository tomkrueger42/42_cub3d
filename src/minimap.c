#include <stdio.h>
#include "../inc/cub3d.h"
#include <stdlib.h>

char	**make_map(void)
{
	char **map;
	map = ft_calloc(5, 5);
	map[0] = ft_strdup("1111");
	map[1] = ft_strdup("1001");
	map[2] = ft_strdup("1001");
	map[3] = ft_strdup("1111");
	map[4] = NULL;
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

int	render_image(t_vars vars, char **map)
{
	t_data	img;

	img.img = mlx_new_image(vars.mlx, 500, 500);
	
}

int	main(void)
{
	char	**map;
	t_vars	vars;

	map = make_map();
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 500, 500, "cub3d minimap");
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_loop(vars.mlx);
}
