#include "map_map.h"

void	fill_player(t_map *map);
double	find_direction(t_map *map, int *ct, int *ct2);

/*
	befuellt die variablen des players
*/
void	fill_player(t_map *map)
{
	int	ct;
	int	ct2;

	ct = 0;
	ct2 = 0;
	map->player.direction = find_direction(map, &ct, &ct2);
	map->player.start_x = ct2 - 1;
	map->player.start_y = ct;
	return ;
}

/*
	sucht nach N W E S und legt die blickrichtung 
	im bogenmass als double fest
	ausserdem werden ct & ct2 veraendert, die dann 
	die x/y start-koordinate ergeben
*/
double	find_direction(t_map *map, int *ct, int *ct2)
{
	double	val;

	val = -1;
	while (val == -1 && map->map != NULL && map->map[*ct] != NULL)
	{
		while (val == -1 && map->map[*ct][*ct2] != '\0')
		{
			if (map->map[*ct][*ct2] == 'N')
				val = 0.5;
			else if (map->map[*ct][*ct2] == 'E')
				val = 0;
			else if (map->map[*ct][*ct2] == 'W')
				val = 1;
			else if (map->map[*ct][*ct2] == 'S')
				val = 1.5;
			(*ct2)++;
		}
		if (val == -1)
		{
			*ct2 = 0;
			(*ct)++;
		}
	}
	return (val);
}
