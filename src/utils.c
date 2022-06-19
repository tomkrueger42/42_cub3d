/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkruger <tkruger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 17:10:41 by tkruger           #+#    #+#             */
/*   Updated: 2022/06/19 17:18:47 by tkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

void	put_error_and_exit(char *msg)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(msg, 2);
	free_graphics();
	free_map();
	free_player();
	free_style();
	exit(EXIT_FAILURE);
}

long	now_ms(void)
{
	struct timeval	tval;

	gettimeofday(&tval, NULL);
	return ((long)(tval.tv_sec * 1000 + tval.tv_usec / 1000));
}

int	create_rgbt(unsigned char r, unsigned char g,
		unsigned char b, unsigned char t)
{
	return (*(int *)(unsigned char [4]){t, b, g, r});
}
