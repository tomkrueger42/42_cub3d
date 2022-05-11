#include"map_map.h"

int		valid_line(char *string, int potenz);
int		find_code(char *origin, char *needle);
int		find_map(char *string);
char	*append_space(char *line, int len);

/* 
	sucht nach den codewoertern wie zb NO 
	und gibt die stelle im string zurueck, an der sie sich befinden
*/
int	find_code(char *origin, char *needle)
{
	int	ct;
	int	ct2;

	ct = 0;
	ct2 = 0;
	if (origin == NULL || needle == NULL)
		return (-1);
	while (origin[ct] != '\0')
	{
		while (origin[ct] == needle[ct2])
		{
			ct++;
			ct2++;
			if (needle[ct2] == '\0')
				return (ct);
			if (origin[ct] == '\0')
				return (-1);
		}
		ct++;
	}
	return (-1);
}

/*
	sucht den anfang der map
	anfang == erste valide line
*/
int	find_map(char *string)
{
	int	potenz;
	int	ct;
	int	out;

	potenz = 0;
	ct = 0;
	out = 0;
	if (!string)
		return (-1);
	while (string[ct] != '\0')
	{
		if (string[ct] == '\n' && string[ct + 1] != '\0')
			potenz = ct + 1;
		if (valid_line(string, potenz) > -1)
			return (potenz);
		if (string[ct] != '\0')
			ct++;
	}
	return (-1);
}

/*
	sucht die erste valide line
*/
int	valid_line(char *string, int potenz)
{
	int	ct;

	ct = potenz;
	while (string[ct] != '\0' && string[ct] != '\n')
	{
		if (!ft_isdigit(string[ct]) && !ft_iswhitespace(string[ct]))
			return (-1);
		ct++;
	}
	if ((string[ct] == '\0' || string[ct] == '\n') && ct != potenz)
		return (1);
	else
		return (-1);
}

/*
	erweitert den string line
	auf die laenge len und befuellt ihn
	nach dem ende mit spaces
*/
char	*append_space(char *line, int len)
{
	char	*new;
	int		ct;

	ct = 0;
	new = malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	new[len] = '\0';
	while (line[ct] != '\0')
	{
		new[ct] = line[ct];
		ct++;
	}
	while (ct < len)
	{
		new[ct] = ' ';
		ct++;
	}
	ft_free((void **)(&line));
	return (new);
}
