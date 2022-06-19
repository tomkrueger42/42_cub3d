/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkruger <tkruger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 17:10:19 by tkruger           #+#    #+#             */
/*   Updated: 2022/06/19 17:10:20 by tkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map	*get_map(void)
{
	static t_map	*map;

	if (map == NULL)
	{
		map = ft_calloc(1, sizeof(t_map));
		if (map == NULL)
			put_error_and_exit("malloc failure in get_map()");
	}
	return (map);
}

void	free_map(void)
{
	t_map	*ptr;

	ptr = get_map();
	ft_free_array(&ptr->data);
	ft_free((void **)&ptr);
}
