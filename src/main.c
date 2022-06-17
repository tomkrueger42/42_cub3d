#include "cub3d.h"
#include <fcntl.h>
#include <stdlib.h>

void	graphic_loop(void *data)
{
	t_graphics	*graphics;
	t_player	*player;
	static long	old_time = 0;
	double		fps;

	graphics = data;
	player = get_player();
	fps = (double)(now_ms() - old_time) / 1000;
	old_time = now_ms();
	if (mlx_is_key_down(graphics->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(graphics->mlx);
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
	fan_out(0, -FOV / 2);
	render_minimap();
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		put_error_and_exit("incorrect amount of arguments");
	if (ft_strnstr(argv[1], ".cub", ft_strlen(argv[1]))
		!= argv[1] + ft_strlen(argv[1]) - 4)
		put_error_and_exit("filename must end with '.cub' extension");
	read_file(open(argv[1], O_RDONLY));
	count_dimensions(get_map()->data);
	fill_rows_with_spaces(get_map()->data);
	map_check(get_map()->data);
	player_check(get_map()->data);
	fan_out(0, -FOV / 2);
	render_minimap();
	mlx_image_to_window(get_graphics()->mlx, get_graphics()->image, 0, 0);
	mlx_loop_hook(get_graphics()->mlx, &graphic_loop, get_graphics());
	mlx_loop(get_graphics()->mlx);
	free_graphics();
	free_map();
	free_player();
	free_style();
	return (EXIT_SUCCESS);
}
