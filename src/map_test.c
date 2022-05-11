#include "map_map.h"

void	print_map(t_map *map);

int	main(void)
{
	t_map	*test;

	test = read_map("x.cub");
	print_map(test);
	valid_check(test);
	free_map(test);
	//system("leaks cub3d"); // wenn ich den nicht auskommentiere kriege ich probleme
}

void	print_map(t_map *map)
{
	int	ct;

	ct = 0;
	if (map == NULL)
	{
		printf("map is null!!!\n");
		return ;
	}
	printf("EAST = \t\t\t%s\n", map->e);
	printf("NORTH = \t\t%s\n", map->n);
	printf("WEST = \t\t\t%s\n", map->w);
	printf("SOUTH = \t\t%s\n", map->s);
	printf("FLOOR COLOUR = \t\t%s\n", map->f);
	printf("CEILING COLOUR = \t%s\n", map->c);
	printf("x_max = \t\t%d\n", map->x_max);
	printf("y_max = \t\t%d\n", map->y_max);
	printf("\n____________________\nPLAYER INFOS\n");
	printf("Player direction = %f\n", map->player.direction);
	printf("Player starts at = (%d|%d)\n", map->player.start_x, map->player.start_y);
	printf("\n___________________\nMAP:\n");
	if (map->map == NULL)
	{
		printf("map->map is null!!!\n");
		return ;
	}
	while (map->map[ct] != NULL)
	{
		printf("|%s|\n", map->map[ct]);
		ct++;
	}
	return ;
}
