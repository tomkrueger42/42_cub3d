#include"map.h"

void	free_map(t_map *map);

void	free_map(t_map *map)
{
	int	ct;

	ct = 0;
	if (map == NULL)
		return ;
	while (map->map[ct] != NULL)
	{
		free(map->map[ct]);
		ct++;
	}
	free (map);
	return ;
}
