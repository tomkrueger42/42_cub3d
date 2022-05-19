#include "cub3d.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

unsigned int	convert_color(char *value);
char			*extract_value(char *lines, char *name);
int				find_map(char *string);
int				valid_line(char *string, int potenz);

void	read_file(char *filename)
{
	int		fd;
	char	*lines;
	char	*temp;

	fd = open(filename, O_RDONLY);
	temp = get_next_line(fd);
	while (temp != NULL)
	{
		lines = ft_strjoin_free(lines, temp);
		temp = get_next_line(fd);
	}
	close (fd);
	style()->north_walls = extract_value(lines, "NO ");
	style()->east_walls = extract_value(lines, "EA ");
	style()->south_walls = extract_value(lines, "SO ");
	style()->west_walls = extract_value(lines, "WE ");
	style()->floor_color = convert_color(extract_value(lines, "F "));
	style()->ceiling_color = convert_color(extract_value(lines, "C "));
	if (find_map(lines) == -1)
		put_error_and_exit("couldn't find map", 2);
	map()->data = ft_split(lines + find_map(lines), '\n');
	ft_free((void **)(&lines));
}

t_style	*style(void)
{
	static t_style	*style;

	if (style == NULL)
	{
		style = ft_calloc(1, sizeof(t_style));
		if (style == NULL)
			put_error_and_exit("malloc failure in style()", 1);
	}
	return (style);
}

unsigned int	convert_color(char *value)
{
	if (value == NULL)
		return (0);
	return (create_trgb(255, ft_atoi(value), ft_atoi(ft_strchr(value, ',') + 1),
			ft_atoi(ft_strrchr(value, ',') + 1)));
}

char	*extract_value(char *lines, char *name)
{
	int		end;
	char	*origin;

	origin = ft_strnstr(lines, name, ft_strlen(lines));
	if (origin == NULL)
		put_error_and_exit("invalid file!", 2);
	while (!ft_iswhitespace(*origin))
		origin++;
	while (ft_iswhitespace(*origin))
		origin++;
	end = origin - lines;
	printf("name: %s, origin: %s\n\n", name, ft_substr(origin, 0, 20));
	while (lines[end] != '\0' && !ft_iswhitespace(lines[end]))
		end++;
	return (ft_substr(origin, 0, end));
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
