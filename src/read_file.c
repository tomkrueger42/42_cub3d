/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkruger <tkruger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 17:10:31 by tkruger           #+#    #+#             */
/*   Updated: 2022/06/19 17:19:02 by tkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <unistd.h>

unsigned int	convert_color(char *value);
char			*extract_value(char *lines, char *identifier);
mlx_texture_t	*load_texture(char *value);

void	read_file(int fd, t_style *style, t_map *map)
{
	char	*lines;
	char	*temp;

	if (fd == -1)
		put_error_and_exit("file not found");
	lines = NULL;
	temp = get_next_line(fd);
	while (temp != NULL)
	{
		lines = ft_strjoin_free(lines, temp);
		temp = get_next_line(fd);
	}
	close (fd);
	style->texture[NORTH] = load_texture(extract_value(lines, "NO"));
	style->texture[EAST] = load_texture(extract_value(lines, "EA"));
	style->texture[SOUTH] = load_texture(extract_value(lines, "SO"));
	style->texture[WEST] = load_texture(extract_value(lines, "WE"));
	style->floor_color = convert_color(extract_value(lines, "F"));
	style->ceiling_color = convert_color(extract_value(lines, "C"));
	map->data = ft_split(find_map(lines), '\n');
	if (map->data == NULL)
		put_error_and_exit("no map!");
	ft_free((void **)(&lines));
}

int	texture_given(char *lines, char *identifier)
{
	bool	sw;

	sw = false;
	while (true)
	{
		lines = ft_strnstr(lines, identifier, ft_strlen(lines));
		if (lines == NULL)
			break ;
		else if (sw == true)
			return (1);
		sw = true;
		lines += ft_strlen(identifier);
	}
	return (0);
}

// This function extracts the value of the identifier from lines
char	*extract_value(char *lines, char *identifier)
{
	int		end;
	char	*origin;

	if (texture_given(lines, identifier))
		put_error_and_exit("invalid identifiers");
	origin = ft_strnstr(lines, identifier, ft_strlen(lines));
	if (origin == NULL)
		put_error_and_exit("invalid file");
	while (!ft_iswhitespace(*origin))
		origin++;
	while (ft_iswhitespace(*origin))
		origin++;
	end = 0;
	while (origin[end] != '\0' && !ft_iswhitespace(origin[end]))
		end++;
	return (ft_substr(origin, 0, end));
}

mlx_texture_t	*load_texture(char *value)
{
	mlx_texture_t	*texture;

	if (value == NULL)
		put_error_and_exit("missing texture path");
	texture = mlx_load_png(value);
	ft_free((void **)&value);
	if (texture == NULL)
		put_error_and_exit("incorrect texture path");
	return (texture);
}

// This function converts the comma seperated rgb values to hex
unsigned int	convert_color(char *value)
{
	unsigned int	color;
	int				i;

	i = -1;
	if (value == NULL)
		put_error_and_exit("missing floor/ceiling color");
	while (value[++i] != '\0')
	{
		if ((!ft_isdigit(value[i]) && value[i] != ',')
			|| (i == 0 && (ft_count_char(value, ',') > 2
					|| ft_atoi(value) > 255 || ft_atoi(value) < 0
					|| ft_atoi(ft_strchr(value, ',') + 1) > 255
					|| ft_atoi(ft_strchr(value, ',') + 1) < 0
					|| ft_atoi(ft_strrchr(value, ',') + 1) > 255
					|| ft_atoi(ft_strrchr(value, ',') + 1) < 0)))
		{
			ft_free((void **)&value);
			put_error_and_exit("incorrect color code formatting");
		}
	}
	color = create_rgbt(ft_atoi(value), ft_atoi(ft_strchr(value, ',') + 1),
			ft_atoi(ft_strrchr(value, ',') + 1), 255);
	ft_free((void **)&value);
	return (color);
}
