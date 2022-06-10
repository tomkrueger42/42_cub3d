#include "cub3d.h"

// This function initializes the mlx instance and returns the graphics pointer
t_graphics	*get_graphics(void)
{
	static t_graphics	*graphics = NULL;

	if (graphics == NULL)
	{
		graphics = ft_calloc(1, sizeof(t_graphics));
		if (graphics == NULL)
			put_error_and_exit("malloc failure in get_graphics()", 1);
		graphics->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d", false);
		if (graphics->mlx == NULL)
			put_error_and_exit("mlx init failure", 1);
		graphics->image = mlx_new_image(graphics->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
		if (graphics->image == NULL)
		{
			mlx_terminate(graphics->mlx);
			put_error_and_exit("mlx new image failure", 1);
		}
	}
	return (graphics);
}

void	free_graphics(void)
{
	t_graphics	*ptr;

	ptr = get_graphics();
	if (ptr != NULL)
	{
		mlx_delete_image(ptr->mlx, ptr->image);
		mlx_terminate(ptr->mlx);
	}
	ft_free((void **)&ptr);
}


