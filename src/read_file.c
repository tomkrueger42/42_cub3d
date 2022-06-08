#include "cub3d.h"
#include <fcntl.h>
#include <unistd.h>

unsigned int	convert_color(char *value);
char	*extract_value(char *lines, char *identifier);

void	read_file(char *filename)
{
	int		fd;
	char	*lines;
	char	*temp;

	lines = NULL;
	fd = open(filename, O_RDONLY);
	temp = get_next_line(fd);
	while (temp != NULL)
	{
		lines = ft_strjoin_free(lines, temp);
		temp = get_next_line(fd);
	}
	close (fd);
	get_style()->north_walls = extract_value(lines, "NO ");
	get_style()->east_walls = extract_value(lines, "EA ");
	get_style()->south_walls = extract_value(lines, "SO ");
	get_style()->west_walls = extract_value(lines, "WE ");
	get_style()->floor_color = convert_color(extract_value(lines, "F "));
	get_style()->ceiling_color = convert_color(extract_value(lines, "C "));
	get_map()->data = ft_split(find_map(lines), '\n');
	ft_free((void **)(&lines));
}

// This function extracts the value of the identifier from lines
char	*extract_value(char *lines, char *identifier)
{
	int		end;
	char	*origin;

	origin = ft_strnstr(lines, identifier, ft_strlen(lines));
	if (origin == NULL)
		put_error_and_exit("invalid file!", 2);
	while (!ft_iswhitespace(*origin))
		origin++;
	while (ft_iswhitespace(*origin))
		origin++;
	end = 0;
	while (origin[end] != '\0' && !ft_iswhitespace(origin[end]))
		end++;
	return (ft_substr(origin, 0, end));
}

// This function converts the comma seperated rgb values to hex
unsigned int	convert_color(char *value)
{
	if (value == NULL)
		return (0);
	return (create_trgb(0, ft_atoi(value), ft_atoi(ft_strchr(value, ',') + 1),
			ft_atoi(ft_strrchr(value, ',') + 1)));
}
