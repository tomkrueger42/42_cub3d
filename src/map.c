#include "cub3d.h"

t_map	*get_map(void)
{
	static t_map	*map;

	if (map == NULL)
	{
		map = ft_calloc(1, sizeof(t_map));
		if (map == NULL)
			put_error_and_exit("malloc failure in get_map()", 1);
	}
	return (map);
}

void	free_map(void)
{
	t_map	*ptr;

	ptr = get_map();
	ft_free_array(&ptr->data);
	ft_free((void **)&ptr);
}
