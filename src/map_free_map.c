#include"map_map.h"

void	free_map(t_map *map);
void	free_map_vars(t_map *map);

/*
	zusammenfassende free funktion der map
*/
void	free_map(t_map *map)
{
	printf("free function\n");
	int	ct;

	ct = 0;
	if (map == NULL)
		return ;
	while (map->map != NULL && map->map[ct] != NULL)
	{
		ft_free((void **)(&map->map[ct]));
		ct++;
	}
	free_map_vars(map);
	if (map != NULL)
		ft_free ((void **)(&map));
	return ;
}

/*
	freet die char * variablen in der map
	(platzgruende)
*/
void	free_map_vars(t_map *map)
{
	ft_free((void **)(&map->n));
	ft_free((void **)(&map->s));
	ft_free((void **)(&map->w));
	ft_free((void **)(&map->e));
	ft_free((void **)(&map->f));
	ft_free((void **)(&map->c));
	return ;
}
