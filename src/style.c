#include "cub3d.h"

// This function returns the pointer to our style-struct
t_style	*get_style(void)
{
	static t_style	*style;

	if (style == NULL)
	{
		style = ft_calloc(1, sizeof(t_style));
		if (style == NULL)
			put_error_and_exit("malloc failure in style()", 1);
		style->texture[NORTH] = NULL;
		style->texture[EAST] = NULL;
		style->texture[SOUTH] = NULL;
		style->texture[WEST] = NULL;
	}
	return (style);
}

void	free_style(void)
{
	t_style	*ptr;

	ptr = get_style();
	ft_free((void **)&ptr->north_walls);
	ft_free((void **)&ptr->east_walls);
	ft_free((void **)&ptr->south_walls);
	ft_free((void **)&ptr->west_walls);
	ft_free((void **)&ptr);
}
