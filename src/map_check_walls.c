#include "cub3d.h"

#include <stdio.h>

bool		closed_walls(char **map);
bool		check_wall(char **map, int y, int x);



// blanks on outer corners!
// zeros on inner corners


/*
	check auf unclosed walls
*/
bool	closed_walls(char **map)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (map[y] != NULL)
	{
		while (map[y][x] != '\0')
		{
			if (map[y][x] != '1' && !ft_iswhitespace(map[y][x]))
			{
				if (check_wall(map, y, x) == false)
				{
					printf("Annahme unclosed walls bei:\n[%d][%d] == %c\n", y, x, map[y][x]);
					return (false);
				}
			}
			x++;
		}
		x = 0;
		y++;
	}
	return (true);
}

/*
	aufgerufen, wenn nicht 1 oder space,
	dann wird auf unclosed gecheckt
*/
bool	check_wall(char **map, int y, int x)
{
	int	size;
	int	len;

	size = ft_arrlen(map) - 1;
	len = ft_strlen(map[0]);
	if (y == 0 || y == size || x == len || x == 0)
		return (false);
	if (map[y - 1][x] == ' ' || map[y + 1][x] == ' ')
		return (false);
	if (map[y - 1][x] == '\0' || map[y + 1][x] == '\0')
		return (false);
	if (map[y][x - 1] == ' ' || map[y][x + 1] == ' ')
		return (false);
	if (map[y][x - 1] == '\0' || map[y][x + 1] == '\0')
		return (false);
	return (true);
}

/*

0	012
1	0X2
2	012

x = [1][1]


3. error handling, pruefen auf valide map 
-> string darf nicht mit 0 oder buchstaben beginnen oder enden
-> neben diesen darf auch kein leerzeichen sein
-> auch nicht nach oben hin!!!!

*/