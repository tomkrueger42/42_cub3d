/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   style.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkruger <tkruger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 17:10:34 by tkruger           #+#    #+#             */
/*   Updated: 2022/06/19 17:10:35 by tkruger          ###   ########.fr       */
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
	t_style	*ptr;

	ptr = get_style();
	ft_free((void **)&ptr->texture[NORTH]->pixels);
	ft_free((void **)&ptr->texture[NORTH]);
	ft_free((void **)&ptr->texture[EAST]->pixels);
	ft_free((void **)&ptr->texture[EAST]);
	ft_free((void **)&ptr->texture[SOUTH]->pixels);
	ft_free((void **)&ptr->texture[SOUTH]);
	ft_free((void **)&ptr->texture[WEST]->pixels);
	ft_free((void **)&ptr->texture[WEST]);
	ft_free((void **)&ptr->texture);
	ft_free((void **)&ptr);
}
