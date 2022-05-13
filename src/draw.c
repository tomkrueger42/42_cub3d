#include "../inc/cub3d.h"
#include <math.h>

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;
	t_map	*map_ptr;

	map_ptr = map();
	if (x > map_ptr->width * map_ptr->box_size || x < 0 || y > map_ptr->len * map_ptr->box_size || y < 0)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}