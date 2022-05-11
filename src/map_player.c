#include "map_map.h"

void	fill_player(t_map *map);

void	fill_player(t_map *map)
{
	map->player.direction = 'z';
	map->player.start_x = 0;
	map->player.start_y = 0;

}
