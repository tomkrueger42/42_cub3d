#include "cub3d.h"
#include <stdio.h>
#include <math.h>

void	draw_ray(t_vars *vars);

t_player	*player(void)
{
	static t_player	*player;

	if (player == NULL)
	{
		player = ft_calloc(1, sizeof(t_player));
		if (player == NULL)
			put_error_and_exit("malloc failure in player()", 1);
		player->x_pos = 300;
		player->y_pos = 300;
		player->y_del = -1;
		player->y_del = -1;
		player->direction = 1.5 * PI;
		player->size = map()->box_size / 2;
	}
	return (player);
}

void	render_player(t_vars *vars)
{
	int	x_px;
	int	y_px;

	y_px = - (player()->size / 3);
	while (y_px < player()->size / 3)
	{
		x_px = - (player()->size / 3);
		while (x_px < player()->size / 3)
		{
			my_mlx_pixel_put(map()->minimap, player()->x_pos + x_px, player()->y_pos + y_px, 0xffff00);
			x_px++;
		}
		y_px++;
	}
	draw_ray(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, map()->minimap->img, 0, 0);
}

void	draw_ray(__unused t_vars *vars)
{
	double	x;
	double	y;
	double	xy;

	x = round(player()->x_del * 100);
	y = round(player()->y_del * 100);
	if (player()->y_del == 0)
		xy = __INT_FAST64_MAX__;
	else
		xy = player()->x_del / player()->y_del;
	while (x != 0 || y != 0)
	{
		my_mlx_pixel_put(map()->minimap, player()->x_pos + x, player()->y_pos + y, 0xFF00);
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

	if (keycode == 13)	// W key // this movement tends to go slightly to the left
	{
		player()->x_pos += player()->x_del * MOVEMENT_SPEED;
		player()->y_pos += player()->y_del * MOVEMENT_SPEED;
		// printf("+ %f to x and + %f to y\n", player()->x_del * MOVEMENT_SPEED, player()->y_del * MOVEMENT_SPEED);
	}
	if (keycode == 0)	// A key
	{
		player()->x_pos += player()->y_del * MOVEMENT_SPEED;
		player()->y_pos -= player()->x_del * MOVEMENT_SPEED;
		// printf("+ %f to x and - %f to y\n", player()->x_del * MOVEMENT_SPEED, player()->y_del * MOVEMENT_SPEED);
	}
	else if (keycode == 1)	// S key
	{
		player()->x_pos -= player()->x_del * MOVEMENT_SPEED;
		player()->y_pos -= player()->y_del * MOVEMENT_SPEED;
		// printf("- %f to x and - %f to y\n", player()->x_del * MOVEMENT_SPEED, player()->y_del * MOVEMENT_SPEED);
	}
	else if (keycode == 2)	// D key // this movement tends to go slightly to the left
	{
		player()->x_pos -= player()->y_del * MOVEMENT_SPEED;
		player()->y_pos += player()->x_del * MOVEMENT_SPEED;
		// printf("- %f to x and + %f to y\n", player()->x_del * MOVEMENT_SPEED, player()->y_del * MOVEMENT_SPEED);
	}
	else if (keycode == 123) // Arrow left key
	{
		player()->direction -= ROTATION_SPEED;
		if (player()->direction < 0 * PI)
			player()->direction += 2 * PI;
		player()->x_del = cos(player()->direction);
		player()->y_del = sin(player()->direction);
	}
	else if (keycode == 124) // Arrow right key
	{
		player()->direction += ROTATION_SPEED;
		if (player()->direction >= 2 * PI)
			player()->direction -= 2 * PI;
		player()->x_del = cos(player()->direction);
		player()->y_del = sin(player()->direction);
	}
	// printf("x: %d, y: %d, x_d: %f, y_d: %f, dir: %f\n", player()->x_pos, player()->y_pos, player()->x_del, player()->y_del, player()->direction);
}
