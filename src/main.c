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
		mlx_destroy_image(get_graphics()->mlx, get_graphics()->img);
		get_graphics()->img = mlx_new_image(get_graphics()->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
		get_graphics()->addr = mlx_get_data_addr(get_graphics()->img, &get_graphics()->bits_per_pixel, &get_graphics()->line_length, &get_graphics()->endian);
		fan_out();
		render_minimap();
		mlx_put_image_to_window(get_graphics()->mlx, get_graphics()->win, get_graphics()->img, 0, 0);
	}
	return (0);
}


int	main(void) // needs argc, **argv
{
	read_file("x.cub");
	count_dimensions(get_map()->data);
	fill_rows_with_spaces(get_map()->data);
	if (map_check(get_map()->data) || player_check(get_map()->data))
	{
		free_style();
		free_map();
		free_player();
		return (EXIT_FAILURE);
	}
	fan_out();
	render_minimap();
	mlx_put_image_to_window(get_graphics()->mlx, get_graphics()->win, get_graphics()->img, 0, 0);
	mlx_hook(get_graphics()->win, 02, 1L<<0, key_hook, NULL);
	mlx_loop(get_graphics()->mlx);
	return (EXIT_SUCCESS);
}