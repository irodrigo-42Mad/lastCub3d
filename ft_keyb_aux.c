/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyb_aux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 00:45:13 by irodrigo          #+#    #+#             */
/*   Updated: 2021/03/14 00:52:01 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	kbd_right(t_game_draw *kbd)
{
	kbd->rc.olddirx = kbd->rc.dirx;
	kbd->rc.dirx = kbd->rc.dirx * cos(-kbd->rc.rotspeed)
		- kbd->rc.diry * sin(-kbd->rc.rotspeed);
	kbd->rc.diry = kbd->rc.olddirx * sin(-kbd->rc.rotspeed) +
		kbd->rc.diry * cos(-kbd->rc.rotspeed);
	kbd->rc.oldplanex = kbd->rc.planex;
	kbd->rc.planex = kbd->rc.planex * cos(-kbd->rc.rotspeed)
		- kbd->rc.planey * sin(-kbd->rc.rotspeed);
	kbd->rc.planey = kbd->rc.oldplanex * sin(-kbd->rc.rotspeed)
		+ kbd->rc.planey * cos(-kbd->rc.rotspeed);
}
