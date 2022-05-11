#include "map_map.h"

int	player_check(char **map);
int	player_check_line(char *line);

/* 
	checkt ob es zu viele player auf dem feld gibt
	sum muss entsprechend genau 1 sein
*/
int	player_check(char **map)
{
	int	ct;
	int	sum;

	ct = 0;
	sum = 0;
	if (map == NULL)
		return (-1);
	while (map[ct] != NULL)
	{
		sum = sum + (player_check_line(map[ct]));
		ct++;
	}
	return (sum);
}

/*
	code in zwei funktionen wegen platzmangel
*/
int	player_check_line(char *line)
{
	int	ct;
	int	sum;

	ct = 0;
	sum = 0;
	while (line[ct] != '\0')
	{
		if (line[ct] == 'N' || line[ct] == 'E'
			|| line[ct] == 'W' || line[ct] == 'S')
			sum++;
		ct++;
	}
	return (sum);
}
