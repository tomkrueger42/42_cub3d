#include "cub3d.h"
#include <stdio.h>
#include <math.h>

void	draw_ray(void);

t_player	*player(void)
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

	ptr = player();
	ft_free((void **)&ptr);
}

int	first_intersect_hori(void);
int	first_intersect_verti(void);
int	len_hit_wall();

void	render_player(void)
{
	int	x_px;
	int	y_px;

	y_px = - (player()->size / 2);
	while (y_px < player()->size / 2)
	{
		x_px = - (player()->size / 2);
		while (x_px < player()->size / 2)
		{
			my_mlx_pixel_put(graphics(), player()->x_pos * map()->tile_size + x_px, player()->y_pos * map()->tile_size + y_px, 0xffff00);
			x_px++;
		}
		y_px++;
	}
	draw_ray();

	//
	first_intersect_hori();
	first_intersect_verti();
	len_hit_wall();
	//
	mlx_put_image_to_window(graphics()->mlx, graphics()->win, graphics()->img, 0, 0);
}

void	draw_ray(void)
{
	double	x;
	double	y;
	double	xy;

	x = round(player()->x_delta * MINIMAP_SIZE);
	y = round(player()->y_delta * MINIMAP_SIZE);
	if (player()->y_delta == 0)
		xy = __INT_FAST64_MAX__;
	else
		xy = player()->x_delta / player()->y_delta;
	while (x != 0 || y != 0)
	{
		my_mlx_pixel_put(graphics(), player()->x_pos * map()->tile_size + x, player()->y_pos * map()->tile_size + y, 0xFF00);
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
	// they do some weird stuff still -> not going straight to the direction the player is pointing to (but probably not really noticeable)

	if (keycode == W_KEY)
	{
		player()->x_pos += player()->x_delta * player()->speed;
		player()->y_pos += player()->y_delta * player()->speed;
	}
	if (keycode == A_KEY)
	{
		player()->x_pos += player()->y_delta * player()->speed;
		player()->y_pos -= player()->x_delta * player()->speed;
	}
	else if (keycode == S_KEY)
	{
		player()->x_pos -= player()->x_delta * player()->speed;
		player()->y_pos -= player()->y_delta * player()->speed;
	}
	else if (keycode == D_KEY)
	{
		player()->x_pos -= player()->y_delta * player()->speed;
		player()->y_pos += player()->x_delta * player()->speed;
	}
	else if (keycode == ARROW_LEFT_KEY)
		player()->direction -= ROTATION_SPEED;
	else if (keycode == ARROW_RIGHT_KEY)
		player()->direction += ROTATION_SPEED;
	if (player()->direction < 0 * PI)
		player()->direction += 2 * PI;
	else if (player()->direction >= 2 * PI)
		player()->direction -= 2 * PI;
	player()->x_delta = cos(player()->direction);
	player()->y_delta = sin(player()->direction);
	printf("x: %f, y: %f, x_d: %f, y_d: %f, dir: %f, speed: %f\n", player()->x_pos, player()->y_pos, player()->x_delta, player()->y_delta, player()->direction, player()->speed);
}
