/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprite_draw.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 04:29:02 by jdiaz-co          #+#    #+#             */
/*   Updated: 2021/02/27 20:30:26 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void			spritepos(t_game_draw *mygame, int x, int y)
{
	mygame->sprite[mygame->spr_total].sp_act_pos.x = x + 0.5;
	mygame->sprite[mygame->spr_total].sp_act_pos.y = y + 0.5;
	mygame->spr_total++;
}

static	void	how_gap(int *gap)
{
	*gap = (*gap * 10) / 13;
	if (*gap == 9 || *gap == 10)
		*gap = 11;
	if (*gap < 1)
		*gap = 1;
}

static void		sortsprite(t_game_draw *mygame)
{
	int		gap;
	int		swapped;
	int		i;
	int		j;

	gap = mygame->spr_total;
	while (gap > 1 || swapped)
	{
		how_gap(&gap);
		swapped = 0;
		i = 0;
		while (i < mygame->spr_total - gap)
		{
			j = i + gap;
			if (mygame->allspr_dist[i] < mygame->allspr_dist[j])
			{
				ft_swap_double(&mygame->allspr_dist[i],
					&mygame->allspr_dist[j]);
				ft_swap_int(&mygame->allspr_pos[i], &mygame->allspr_pos[j]);
				swapped = 1;
			}
			i++;
		}
	}
}

void			sprite_order(t_game_draw *mygame)
{
	int		i;

	i = 0;
	mygame->allspr_pos = malloc(mygame->spr_total * sizeof(int));
	mygame->allspr_dist = malloc(mygame->spr_total * sizeof(double));
	while (i < mygame->spr_total)
	{
		mygame->allspr_pos[i] = i;
		mygame->allspr_dist[i] = ((mygame->rc.posx -
			mygame->sprite[i].spr_pos.x) *
			(mygame->rc.posx - mygame->sprite[i].spr_pos.x) +
			(mygame->rc.posy - mygame->sprite[i].spr_pos.y) *
			(mygame->rc.posy - mygame->sprite[i].spr_pos.y));
		i++;
	}
	sortsprite(mygame);
}

void			draw_sprite(t_game_draw *mygame)
{
	sprite_order(mygame);
	raysprite(mygame);
}
