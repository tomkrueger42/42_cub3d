#include "map_map.h"

int		valid_check(t_map *map);
int		invalid_char(char **map);
int		invalid_char_line(char *line);
int		no_value(t_map *map);

/*
	zusammenfassung aller notwendiger checks
*/
int	valid_check(t_map *map)
{
	if (no_value(map) == -1 || invalid_char(map->map) == -1)
		return (-1);
	if (player_check(map->map) != 1)
	{
		ft_putstr_fd("Wrong nbr of players!\n", 2);
		return (-1);
	}
	if (closed_walls(map->map) == -1)
	{
		ft_putstr_fd("Unclosed Walls in map!\n", 2);
		return (-1);		
	}
	return (1);
}

/*
	checkt ob es iwo keinen wert gibt
	ACHTUNG
	die datei pfade muessen spaeter gesondert noch mal geprueft werden!
*/
int	no_value(t_map *map)
{
	if (map->n == NULL || map->s == NULL || map->w == NULL || map->e == NULL)
	{
		ft_putstr_fd("No Value for picture path!\n", 2);
		return (-1);
	}
	if (map->f == NULL || map->c == NULL)
	{
		ft_putstr_fd("No colour for floor or ceiling!\n", 2);
		return (-1);
	}
	if (map->player.direction < 0
		|| map->player.start_x < 0 || map->player.start_y < 0)
	{
		ft_putstr_fd("Wrong player information!\n", 2);
		return (-1);
	}
	if (map->map == NULL)
	{
		ft_putstr_fd("Couldn't read map!\n", 2);
		return (-1);
	}
	return (1);
}

/*
	checkt auf invalid chars in der map
*/
int	invalid_char(char **map)
{
	int	ct;
	int	ret;

	ct = 0;
	ret = 1;
	while (ret == 1 && map[ct] != NULL)
	{
		if (invalid_char_line(map[ct]) == -1)
		{
			ret = -1;
			ft_putstr_fd("Invalid char in map!\n", 2);
		}
		ct++;
	}
	return (ret);
}

/*
	hilfsfunktion wegen laenge
*/
int	invalid_char_line(char *line)
{
	char	*valid;
	int		ct;
	int		ret;

	valid = ft_strdup("10CNESW ");
	if (valid == NULL)
		return (-1);
	ct = 0;
	ret = 1;
	while (ret == 1 && line[ct] != '\0')
	{
		if (ft_strchr_int(valid, line[ct]) == -1)
			ret = -1;
		ct++;
	}
	free(valid);
	return (ret);
}

/*
ich muss die farbwerte auch noch checken ... 
ach fuck ey
*/
