/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_textures.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 11:52:44 by irodrigo          #+#    #+#             */
/*   Updated: 2021/03/15 13:30:26 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_prerequisites(t_game_draw *mygame)
{
	if (mygame->stat_txt.north == 1 &&
		mygame->stat_txt.south == 1 &&
		mygame->stat_txt.east == 1 &&
		mygame->stat_txt.west == 1 &&
		mygame->stat_txt.sprite == 1 &&
		mygame->stat_txt.floor != RGB_NONE &&
		mygame->stat_txt.ceil != RGB_NONE)
		return (0);
	return (-1);
}

void	ft_setgamerpos(t_game_draw *mygame, int mat_pos, int line)
{
	mygame->gamer.pos.x = mat_pos;
	mygame->gamer.pos.y = line;
}
