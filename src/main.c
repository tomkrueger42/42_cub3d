#include "cub3d.h"

int	main(void)
{
	t_vars	vars;

	read_file("x.cub");
	parse_map();
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, map()->width * map()->box_size, map()->len * map()->box_size, "cub3d minimap");
	map()->minimap = mlx_new_image(vars.mlx, map()->width * map()->box_size, map()->len * map()->box_size);
	render_minimap(&vars);
	mlx_hook(vars.win, 02, 1L<<0, key_hook, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
