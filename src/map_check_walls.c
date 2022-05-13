#include "map_map.h"

int		closed_walls(char **map);
int		check_wall(char **map, int ct, int ct2);

/*
	check auf unclosed walls
*/
int	closed_walls(char **map)
{
	int	ct;
	int	ct2;

	ct = 0;
	ct2 = 0;
	while (map[ct] != NULL)
	{
		while (map[ct][ct2])
		{
			if (map[ct][ct2] != '1' && !ft_iswhitespace(map[ct][ct2]))
			{
				if (check_wall(map, ct, ct2) == -1)
				{
					printf("Annahme unclosed walls bei:\n[%d][%d] == %c\n", ct, ct2, map[ct][ct2]);
					return (-1);
				}
			}
			ct2++;
		}
		ct2 = 0;
		ct++;
	}
	return (1);
}

/*
	aufgerufen, wenn nicht 1 oder space,
	dann wird auf unclosed gecheckt
*/
int	check_wall(char **map, int ct, int ct2)
{
	int	size;
	int	len;

	size = ft_arrlen(map) - 1;
	len = ft_strlen(map[0]);
	if (ct == 0 || ct == size || ct2 == len || ct2 == 0)
		return (-1);
	if (map[ct - 1][ct2] == ' ' || map[ct + 1][ct2] == ' ')
		return (-1);
	if (map[ct - 1][ct2] == '\0' || map[ct + 1][ct2] == '\0')
		return (-1);
	if (map[ct][ct2 - 1] == ' ' || map[ct][ct2 + 1] == ' ')
		return (-1);
	if (map[ct][ct2 - 1] == '\0' || map[ct][ct2 + 1] == '\0')
		return (-1);
	return (1);
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