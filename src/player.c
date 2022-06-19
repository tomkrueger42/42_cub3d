/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkruger <tkruger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 17:10:25 by tkruger           #+#    #+#             */
/*   Updated: 2022/06/19 17:10:26 by tkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void	draw_ray(t_player *player, t_map *map);

t_player	*get_player(void)
{
	static t_player	*player;

	if (player == NULL)
	{
		player = ft_calloc(1, sizeof(t_player));
		if (player == NULL)
			put_error_and_exit("malloc failure in player()");
	}
	return (player);
}

void	free_player(void)
{
	t_player	*ptr;

	ptr = get_player();
	ft_free((void **)&ptr);
}

void	move_player(double add_to_x_pos, double add_to_y_pos)
{
	t_player	*player;

	player = get_player();
	if (wall_hit(player->x_pos + add_to_x_pos * MVT_SPEED,
			player->y_pos, 0, 0) == 0)
		player->x_pos += add_to_x_pos * MVT_SPEED;
	if (wall_hit(player->x_pos,
			player->y_pos + add_to_y_pos * MVT_SPEED, 0, 0) == 0)
		player->y_pos += add_to_y_pos * MVT_SPEED;
}

void	rotate_player(double add_to_direction)
{
	t_player	*player;

	player = get_player();
	player->direction += add_to_direction * ROT_SPEED;
	if (player->direction < 0 * PI)
		player->direction += 2 * PI;
	else if (player->direction >= 2 * PI)
		player->direction -= 2 * PI;
	player->x_delta = cos(player->direction);
	player->y_delta = sin(player->direction);
}
