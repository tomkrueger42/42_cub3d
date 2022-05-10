#include "map_map.h"

void	print_map(t_map *map);

int	main(void)
{
	t_map	*test;

	test = read_map("x.cub");
	print_map(test);
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
	printf("PLAYER = \t\t%c\n", map->player);
	printf("FLOOR COLOUR = \t\t%s\n", map->f);
	printf("CEILING COLOUR = \t%s\n", map->c);
	printf("\nMAP:\n");
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
