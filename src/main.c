#include "cub3d.h"
#include <stdlib.h>
#include <stdio.h>

void	graphic_loop(void *data)
{
	t_graphics	*graphics;
	t_player	*player;
	static long	old_time = 0;
	double		fps;

	graphics = data;
	player = get_player();
	fps = (double)(now_ms() - old_time) / 1000;
	// printf("fps: %f\n", 1 / fps);
	old_time = now_ms();
	if (mlx_is_key_down(graphics->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(graphics->mlx);
	}
	else if (mlx_is_key_down(graphics->mlx, MLX_KEY_W))
		move_player(player->x_delta * fps, player->y_delta * fps);
	else if (mlx_is_key_down(graphics->mlx, MLX_KEY_A))
		move_player(player->y_delta * fps, -player->x_delta * fps);
	else if (mlx_is_key_down(graphics->mlx, MLX_KEY_S))
		move_player(-player->x_delta * fps, -player->y_delta * fps);
	else if (mlx_is_key_down(graphics->mlx, MLX_KEY_D))
		move_player(-player->y_delta * fps, player->x_delta * fps);
	else if (mlx_is_key_down(graphics->mlx, MLX_KEY_LEFT))
		rotate_player(-fps);
	else if (mlx_is_key_down(graphics->mlx, MLX_KEY_RIGHT))
		rotate_player(fps);
	fan_out();
	render_minimap();
}

int	main(void)
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
	mlx_image_to_window(get_graphics()->mlx, get_graphics()->image, 0, 0);
	mlx_loop_hook(get_graphics()->mlx, &graphic_loop, get_graphics());
	mlx_loop(get_graphics()->mlx);
	free_graphics();
	return (EXIT_SUCCESS);
}