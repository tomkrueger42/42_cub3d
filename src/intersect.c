#include "cub3d.h"
#include <math.h>
#include <stdio.h>



/* returns the distance between player and the first intersection with horizontal line
*
*/

int	rounded_sin(double rad)
{
	if (sin(rad) > 0)
		return (1);
	else if (sin(rad) < 0)
		return (-1);
	return (0);
}

void	scetch_hori_intersect(int x_intersect_pos, int y_intersect_pos, int x_step)
{
	int	index;
	
	index = 0;
	while (index < 10)
	{
		my_mlx_pixel_put(graphics(), x_intersect_pos + (x_step * index) - 1, y_intersect_pos + (map()->tile_size * rounded_sin(player()->direction) * index) - 1, 0xFFFFFF);
		my_mlx_pixel_put(graphics(), x_intersect_pos + (x_step * index), y_intersect_pos + (map()->tile_size * rounded_sin(player()->direction) * index) - 1, 0xFFFFFF);
		my_mlx_pixel_put(graphics(), x_intersect_pos + (x_step * index) + 1, y_intersect_pos + (map()->tile_size * rounded_sin(player()->direction) * index) - 1, 0xFFFFFF);
		my_mlx_pixel_put(graphics(), x_intersect_pos + (x_step * index) - 1, y_intersect_pos + (map()->tile_size * rounded_sin(player()->direction) * index), 0xFFFFFF);
		my_mlx_pixel_put(graphics(), x_intersect_pos + (x_step * index), y_intersect_pos + (map()->tile_size * rounded_sin(player()->direction) * index), 0xFFFFFF);
		my_mlx_pixel_put(graphics(), x_intersect_pos + (x_step * index) + 1, y_intersect_pos + (map()->tile_size * rounded_sin(player()->direction) * index), 0xFFFFFF);
		my_mlx_pixel_put(graphics(), x_intersect_pos + (x_step * index) - 1, y_intersect_pos + (map()->tile_size * rounded_sin(player()->direction) * index) + 1, 0xFFFFFF);
		my_mlx_pixel_put(graphics(), x_intersect_pos + (x_step * index), y_intersect_pos + (map()->tile_size * rounded_sin(player()->direction) * index) + 1, 0xFFFFFF);
		my_mlx_pixel_put(graphics(), x_intersect_pos + (x_step * index) + 1, y_intersect_pos + (map()->tile_size * rounded_sin(player()->direction) * index) + 1, 0xFFFFFF);
		index++;
	}
}

int	first_hori_intersect(void)
{
	int	x_tile_play_pos;
	int	y_tile_play_pos;
	int	x_intersect_pos;
	int	y_intersect_pos;

	x_tile_play_pos = player()->x_pos % map()->tile_size;
	y_tile_play_pos = player()->y_pos % map()->tile_size;
	if (player()->direction < PI)
	{
		y_intersect_pos = player()->y_pos - y_tile_play_pos + map()->tile_size;
		x_intersect_pos = player()->x_pos + y_tile_play_pos / /* sin(player()->direction) * */ tan(player()->direction);
	}
	else
	{
		y_intersect_pos = player()->y_pos - y_tile_play_pos;
		x_intersect_pos = player()->x_pos - y_tile_play_pos / /* sin(player()->direction) * */ tan(player()->direction);
	}

	int	x_step = map()->tile_size / y_tile_play_pos * (x_intersect_pos - player()->x_pos);

	scetch_hori_intersect(x_intersect_pos, y_intersect_pos, x_step);

	//calc the distance btw player and intersection with horizontal


	int distance;
	int addj;

	addj = (y_intersect_pos - y_tile_play_pos) / tan(player()->direction);
	distance = (addj / cos(player()->direction));

	return (distance);

}