#include "cub3d.h"
void	make_map(t_vars vars);
int	main(void)
{
	t_vars	vars;

	read_file("x.cub");
	parse_map();
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, map()->width * map()->box_size, map()->len * map()->box_size, "cub3d minimap");
	// map()->minimap = ft_calloc(1, sizeof(t_img));
	// if (map()->minimap == NULL)
	// 	put_error_and_exit("malloc failure in make_map()", 1);
	map()->minimap.img = mlx_new_image(vars.mlx, map()->width * map()->box_size, map()->len * map()->box_size);
	map()->minimap.addr = mlx_get_data_addr(map()->minimap.img,
		&map()->minimap.bits_per_pixel, &map()->minimap.line_length,
		&map()->minimap.endian);
	render_minimap(&vars);
	mlx_hook(vars.win, 02, 1L<<0, key_hook, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
