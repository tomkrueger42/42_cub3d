#include "cub3d.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int		blanks_nearby(char **data, int x, int y);
int		player_check(char **data);
void	populate_player(int x, int y, char heading);

int	map_check(char **data)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (data[y] != NULL)
	{
		while (data[y][x] != '\0')
		{
			if (data[y][x] == '0' && blanks_nearby(data, x, y))
			{
				printf("unclosed walls near map[%d][%d]\n", y, x);
				put_error_and_exit("unclosed walls", 3);
				return (EXIT_FAILURE);
			}
			x++;
		}
		x = 0;
		y++;
	}
	return (EXIT_SUCCESS);
}

int	blanks_nearby(char **data, int x, int y) // segfault when longest map->data line ends with 0 and no blanks nearby
{
	if (x == 0 || y == 0
		|| data[y - 1][x - 1] == ' '
		|| data[y - 1][x] == ' '
		|| data[y - 1][x + 1] == ' '
		|| data[y][x - 1] == ' '
		|| data[y][x] == ' '
		|| data[y][x + 1] == ' '
		|| data[y + 1][x - 1] == ' '
		|| data[y + 1][x] == ' '
		|| data[y + 1][x + 1] == ' ')
	{
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	player_check(char **data)
{
	int	x;
	int	y;
	int	sum;

	y = 0;
	sum = 0;
	while (data[y] != NULL)
	{
		x = 0;
		while (data[y][x] != '\0')
		{
			if (data[y][x] == 'N' || data[y][x] == 'E'
				|| data[y][x] == 'S' || data[y][x] == 'W')
			{
				if (y == map()->len || x == map()->width || blanks_nearby(data, x, y))
					put_error_and_exit("incorrect player positioning", 3);
				populate_player(x, y, data[y][x]);
				sum++;
			}
			x++;
		}
		y++;
	}
	if (sum != 1)
		put_error_and_exit("wrong amount of players", 3);
	return (EXIT_SUCCESS);
}

void	populate_player(int x, int y, char heading)
{
	player()->y_pos = y + 0.5;
	player()->x_pos = x + 0.5;
	if (heading == 'N')
		player()->direction = 1.5 * PI;
	else if (heading == 'E')
		player()->direction = 0;
	else if (heading == 'S')
		player()->direction = 0.5 * PI;
	else if (heading == 'W')
		player()->direction = PI;
	player()->size = map()->tile_size * 2 / 3;
	player()->x_delta = cos(player()->direction);
	player()->y_delta = sin(player()->direction);
	player()->speed = 1 / MOVEMENT_SPEED;
}
