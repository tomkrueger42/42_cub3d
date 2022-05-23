#include "cub3d.h"

void	my_mlx_pixel_put(t_graphics *graphics, int x, int y, int color)
{
	char	*dst;

	if (x >= WINDOW_WIDTH || x < 0 || y >= WINDOW_HEIGHT || y < 0)
		return ;
	dst = graphics->addr + (y * graphics->line_length + x * (graphics->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	create_trgb(unsigned char t, unsigned char r, unsigned char g, unsigned char b)
{
	return (*(int *)(unsigned char [4]){b, g, r, t});
}
