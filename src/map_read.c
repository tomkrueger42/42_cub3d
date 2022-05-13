#include "map_map.h"

t_map	*make_struct(char *lines, int x);
void	fill_struct(char *lines, t_map *map);
t_map	*read_map(char *src);
char	*fill_var(char *lines, char *name);
void	fill_lines(t_map *map);

/* 
	liest alles in einen langen string, der spaeter ausgewertet wird
	kennt ausserdem die groesse der map
	sollte im return t_map aufrufen
*/
t_map	*read_map(char *src)
{
	int		fd;
	int		x;
	char	*lines;
	char	*temp;

	lines = NULL;
	fd = open(src, O_RDONLY);
	temp = get_next_line(fd);
	if (temp == NULL)
	{
		close (fd);
		return (NULL);
	}
	x = ft_strlen(temp);
	while (temp != NULL)
	{
		lines = ft_strjoin_free(lines, temp);
		temp = get_next_line(fd);
		if (ft_strlen(temp) > x)
			x = ft_strlen(temp);
	}
	close (fd);
	return (make_struct(lines, x));
}

/*
	macht einen grundmalloc und setzt die werte per default auf NULL
	das macht die errorpruefung leichter
*/
t_map	*make_struct(char *lines, int x)
{
	t_map	*new;

	new = malloc(sizeof(t_map));
	if (new == NULL)
		return (NULL);
	new->n = NULL;
	new->s = NULL;
	new->e = NULL;
	new->w = NULL;
	new->f = NULL;
	new->c = NULL;
	new->map = NULL;
	fill_struct(lines, new);
	if (new->map == NULL)
		return (NULL);
	new->x_max = x - 1;
	new->y_max = ft_arrlen(new->map) - 1;
	fill_player(new);
	fill_lines(new);
	ft_free((void **)(&lines));
	return (new);
}

/*
	hm, ja, das erklaert sich von selbst, oder?
*/
void	fill_struct(char *lines, t_map *map)
{
	int		ct;
	char	*temp;

	map->n = fill_var(lines, "NO ");
	map->s = fill_var(lines, "SO ");
	map->e = fill_var(lines, "EA ");
	map->w = fill_var(lines, "WE ");
	map->c = fill_var(lines, "C ");
	map->f = fill_var(lines, "F ");
	temp = lines;
	ct = find_map(temp);
	if (ct > -1)
		map->map = ft_split(temp + ct, '\n');
	return ;
}

/*
	der versuch, eine funktion zu schreiben, 
	die mir alle variablen befuellen kann
*/
char	*fill_var(char *lines, char *name)
{
	int		end;
	int		begin;
	char	*temp;

	begin = find_code(lines, name);
	if (begin == -1)
		return (NULL);
	while (ft_iswhitespace(lines[begin]))
		begin++;
	end = begin;
	while (lines[end] != '\0' && lines[end] != '\n')
		end++;
	temp = ft_substr(lines, begin, (end - begin));
	return (temp);
}

/*
	auffuellen der lines mit space, sodass am ende alle gleich lang sind und nicht
	versehentlich auf speicher zugegriffen wird, der nicht existiert
*/
void	fill_lines(t_map *map)
{
	int	ct;

	ct = 0;
	while (map != NULL && map->map != NULL && map->map[ct] != NULL)
	{
		if (ft_strlen(map->map[ct]) < map->x_max)
		{
			map->map[ct] = append_space(map->map[ct], map->x_max);
		}
		ct++;
	}
	return ;
}

/*
					CHECK
1. map auffuellen, damit nicht versehentlich auf speicher zugegriffen werden kann 
-> da wo strlen der map kleiner ist als x_max muss mit leerzeichen aufgefuellt werden


2. player direction und start position  x/y ermitteln
-> beginnt bei 0, tom fragen, ob das so recht ist
-> in pixel umrechnen

3. error handling, pruefen auf valide map 
-> string darf nicht mit 0 oder buchstaben beginnen oder enden
-> neben diesen darf auch kein leerzeichen sein
-> auch nicht nach oben hin!!!!

*/
