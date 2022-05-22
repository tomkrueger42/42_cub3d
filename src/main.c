#include "cub3d.h"

int	main(void)
{
	t_vars	vars;

	read_file("x.cub");
	count_dimensions(map()->data);
	fill_rows_with_spaces(map()->data);
	if (map_check(map()->data) || player_check(map()->data))
	{
		free_style();
		free_map();
		free_player();
		return (1);
	}
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, map()->width * map()->box_size, map()->len * map()->box_size, "cub3d minimap");
	map()->minimap.img = mlx_new_image(vars.mlx, map()->width * map()->box_size, map()->len * map()->box_size);
	map()->minimap.addr = mlx_get_data_addr(map()->minimap.img,
		&map()->minimap.bits_per_pixel, &map()->minimap.line_length,
		&map()->minimap.endian);
	render_minimap(&vars);
	mlx_hook(vars.win, 02, 1L<<0, key_hook, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
