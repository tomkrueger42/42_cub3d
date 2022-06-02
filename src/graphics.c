#include "cub3d.h"

// This function initializes the mlx instance and returns the graphics pointer
t_graphics	*graphics(void)
{
	static t_graphics	*graphics = NULL;

	if (graphics == NULL)
	{
		graphics = ft_calloc(1, sizeof(t_graphics));
		if (graphics == NULL)
			put_error_and_exit("malloc failure in graphics()", 1);
		graphics->mlx = mlx_init();
		graphics->win = mlx_new_window(graphics->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
		graphics->img = mlx_new_image(graphics->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
		graphics->addr = mlx_get_data_addr(graphics->img, &graphics->bits_per_pixel, &graphics->line_length, &graphics->endian);
	}
	return (graphics);
}

#include <stdio.h>

void	free_graphics(void)
{
	t_graphics	*ptr;

	ptr = graphics();
	printf("free_graphics()\n");
	if (ptr != NULL)
	{
		mlx_destroy_image(ptr->mlx, ptr->img);
		mlx_destroy_window(ptr->mlx, ptr->win);
	}
	ft_free((void **)&ptr);
}


