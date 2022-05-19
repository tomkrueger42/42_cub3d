#include "cub3d.h"

void	print_map(t_map *map);

int	main(void)
{
	read_map("x.cub");
	print_map(test);
	// valid_check(test);
	// free_map(test);
	//system("leaks cub3d"); // wenn ich den nicht auskommentiere kriege ich probleme
}

void	print_map(t_map *map)
{
	int	index;

	index = 0;
	if (map == NULL)
	{
		printf("map is null!!!\n");
		return ;
	}
	printf("NORTH = \t\t%s\n", style()->north_walls);
	printf("EAST = \t\t\t%s\n", style()->east_walls);
	printf("SOUTH = \t\t%s\n", style()->south_walls);
	printf("WEST = \t\t\t%s\n", style()->west_walls);
	printf("FLOOR COLOUR = \t\t%x\n", style()->floor_color);
	printf("CEILING COLOUR = \t%x\n", style()->ceiling_color);
	printf("x_max = \t\t%d\n", map()->width);
	printf("y_max = \t\t%d\n", map()->len);
	// printf("\n____________________\nPLAYER INFOS\n");
	// printf("Player direction = %f\n", map->player.direction);
	// printf("Player starts at = (%d|%d)\n", map->player.start_x, map->player.start_y);
	// printf("\n___________________\nMAP:\n");
	if (map->data == NULL)
	{
		printf("map->data is null!!!\n");
		return ;
	}
	while (map->data[index] != NULL)
	{
		printf("|%s|\n", map->data[index]);
		index++;
	}
	return ;
}
