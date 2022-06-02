#include "cub3d.h"
#include <stdlib.h>

void	fan_out(void);

int	key_hook(int keycode)
{
	if (keycode == ESC_KEY)
	{
		free_graphics();
		free_player();
		free_map();
		free_style();
		exit(0);
	}
	else if (keycode == W_KEY || keycode == A_KEY || keycode == S_KEY || keycode == D_KEY
				|| keycode == ARROW_LEFT_KEY || keycode == ARROW_RIGHT_KEY)
	{
		move_player(keycode);
		mlx_destroy_image(graphics()->mlx, graphics()->img);
		graphics()->img = mlx_new_image(graphics()->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
		graphics()->addr = mlx_get_data_addr(graphics()->img, &graphics()->bits_per_pixel, &graphics()->line_length, &graphics()->endian);
		render_minimap();
		fan_out();
	}
	return (0);
}


int	main(void) // needs argc, **argv
{
	read_file("x.cub");
	count_dimensions(map()->data);
	fill_rows_with_spaces(map()->data);
	if (map_check(map()->data) || player_check(map()->data))
	{
		free_style();
		free_map();
		free_player();
		return (EXIT_FAILURE);
	}
	render_minimap();
	mlx_hook(graphics()->win, 02, 1L<<0, key_hook, NULL);
	mlx_loop(graphics()->mlx);
	return (EXIT_SUCCESS);
}