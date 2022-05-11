#include"map_map.h"

int		valid_line(char *string, int potenz);
int		find_code(char *origin, char *needle);
int		find_map(char *string);

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
