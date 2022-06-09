#include "cub3d.h"
#include <stdio.h>
#include <math.h>

void	draw_ray(void);

t_player	*get_player(void)
{
	static t_player	*player;

	if (player == NULL)
	{
		player = ft_calloc(1, sizeof(t_player));
		if (player == NULL)
			put_error_and_exit("malloc failure in player()", 1);
	}
	return (player);
}

void	free_player(void)
{
	t_player	*ptr;

	ptr = get_player();
	ft_free((void **)&ptr);
}

void	render_player(void)
{
	int	x_px;
	int	y_px;

	y_px = - (get_player()->size / 2);
	while (y_px < get_player()->size / 2)
	{
		x_px = - (get_player()->size / 2);
		while (x_px < get_player()->size / 2)
		{
			my_mlx_pixel_put(&get_graphics()->image, get_player()->x_pos * get_map()->tile_size + x_px, get_player()->y_pos * get_map()->tile_size + y_px, 0xffff00);
			x_px++;
		}
		y_px++;
	}
	draw_ray();
}

void	draw_ray(void)
{
	double	x;
	double	y;
	double	xy;

	x = round(get_player()->x_delta * get_map()->tile_size * 2);
	y = round(get_player()->y_delta * get_map()->tile_size * 2);
	if (get_player()->y_delta == 0)
		xy = __INT_FAST64_MAX__;
	else
		xy = get_player()->x_delta / get_player()->y_delta;
	while (x != 0 || y != 0)
	{
		my_mlx_pixel_put(&get_graphics()->image, get_player()->x_pos * get_map()->tile_size + x, get_player()->y_pos * get_map()->tile_size + y, 0xFFAA33);
		if (x > 0 && (y == 0 || (x / y >= xy && xy > 0) || (x / y < xy && xy < 0)))
			x--;
		else if (x < 0 && (y == 0 || (x / y <= xy && xy < 0) || (x / y > xy && xy > 0)))
			x++;
		else if (y > 0)
			y--;
		else if (y < 0)
			y++;
	}
}

void	move_player(int keycode)
{
	if (keycode == W_KEY)
	{
		get_player()->x_pos += get_player()->x_delta * get_player()->speed;
		get_player()->y_pos += get_player()->y_delta * get_player()->speed;
	}
	if (keycode == A_KEY)
	{
		get_player()->x_pos += get_player()->y_delta * get_player()->speed;
		get_player()->y_pos -= get_player()->x_delta * get_player()->speed;
	}
	else if (keycode == S_KEY)
	{
		get_player()->x_pos -= get_player()->x_delta * get_player()->speed;
		get_player()->y_pos -= get_player()->y_delta * get_player()->speed;
	}
	else if (keycode == D_KEY)
	{
		get_player()->x_pos -= get_player()->y_delta * get_player()->speed;
		get_player()->y_pos += get_player()->x_delta * get_player()->speed;
	}
	else if (keycode == ARROW_LEFT_KEY)
		get_player()->direction -= ROTATION_SPEED;
	else if (keycode == ARROW_RIGHT_KEY)
		get_player()->direction += ROTATION_SPEED;
	if (get_player()->direction < 0 * PI)
		get_player()->direction += 2 * PI;
	else if (get_player()->direction >= 2 * PI)
		get_player()->direction -= 2 * PI;
	get_player()->x_delta = cos(get_player()->direction);
	get_player()->y_delta = sin(get_player()->direction);
	// printf("x: %f, y: %f, x_d: %f, y_d: %f, dir: %f, speed: %f\n", get_player()->x_pos, get_player()->y_pos, get_player()->x_delta, get_player()->y_delta, get_player()->direction, get_player()->speed);
}
