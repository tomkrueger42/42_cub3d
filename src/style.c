/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   style.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomkrueger <tomkrueger@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 17:10:34 by tkruger           #+#    #+#             */
/*   Updated: 2022/06/27 16:18:09 by tomkrueger       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// This function returns the pointer to our style-struct
t_style	*get_style(void)
{
	static t_style	*style;

	if (style == NULL)
	{
		style = ft_calloc(1, sizeof(t_style));
		if (style == NULL)
			put_error_and_exit("malloc failure in style()");
		style->texture[NORTH] = NULL;
		style->texture[EAST] = NULL;
		style->texture[SOUTH] = NULL;
		style->texture[WEST] = NULL;
	}
	return (style);
}

void	free_style(void)
{
	int		i;
	t_style	*ptr;

	i = NORTH;
	ptr = get_style();
	while (i <= WEST)
	{
		if (ptr->texture[i] != NULL)
			ft_free((void **)&ptr->texture[i]->pixels);
		ft_free((void **)&ptr->texture[i]);
		i++;
	}
	ft_free((void **)&ptr->texture);
	ft_free((void **)&ptr);
}
