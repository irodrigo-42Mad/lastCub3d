/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 03:05:32 by irodrigo          #+#    #+#             */
/*   Updated: 2021/03/14 00:10:48 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void		put_spr(t_game_draw *mygame)
{
	int				i;
	int				d;
	unsigned int	color;

	i = mygame->draw_starty;
	while (i < mygame->draw_endy)
	{
		d = (i) * 256 - mygame->win.h * 128 + mygame->spr_height * 128;
		mygame->tex_y = ((d * mygame->tx.height[4]) / mygame->spr_height) / 256;
		color = *(unsigned int *)(mygame->tx.wdata[4] +
			(mygame->tex_y * mygame->tx.wsl[4] + mygame->tex_x *
			(mygame->tx.wbpp[4] / 8)));
		if ((color & 0x0FFFFFF) != 0)
			ft_mlx_pixel_put(mygame, mygame->stripe, i, color);
		i++;
	}
}

void		dy(t_game_draw *mygame)
{
	while (mygame->stripe < mygame->draw_endx)
	{
		mygame->tex_x = (int)(256 * (mygame->stripe - (-mygame->spr_width / 2
			+ mygame->scrnx)) * mygame->tx.width[4] / mygame->spr_width) / 256;
		if (mygame->transformy > 0 && mygame->stripe > 0 && mygame->stripe <
			mygame->win.w && mygame->transformy < mygame->zbuffer
			[mygame->stripe])
			put_spr(mygame);
		mygame->stripe++;
	}
}

void		calc_transf(t_game_draw *mygame)
{
	double	calc_det;

	calc_det = (mygame->rc.planex * mygame->rc.diry -
		mygame->rc.dirx * mygame->rc.planey);
	mygame->inv_det = 1.0 / calc_det;
	mygame->transformx = mygame->inv_det * (mygame->rc.diry *
		mygame->spritex - mygame->rc.dirx * mygame->spritey);
	mygame->transformy = mygame->inv_det * (-mygame->rc.planey *
		mygame->spritex + mygame->rc.planex *
		mygame->spritey);
	mygame->scrnx = (int)((mygame->win.w / 2) * (1 +
		mygame->transformx / mygame->transformy));
	mygame->spr_height = abs((int)(mygame->win.h / mygame->transformy));
	mygame->draw_starty = -mygame->spr_height / 2 + mygame->win.h / 2;
	mygame->draw_endy = mygame->spr_height / 2 + mygame->win.h / 2;
	if (mygame->draw_starty < 0)
		mygame->draw_starty = 0;
	if (mygame->draw_endy >= mygame->win.h)
		mygame->draw_endy = mygame->win.h - 1;
}

void		calc_transf2(t_game_draw *mygame)
{
	mygame->spr_width = abs((int)(mygame->win.h / mygame->transformy));
	mygame->draw_startx = -mygame->spr_width / 2 + mygame->scrnx;
	mygame->draw_endx = mygame->spr_width / 2 + mygame->scrnx;
	if (mygame->draw_startx < 0)
		mygame->draw_startx = 0;
	if (mygame->draw_endx >= mygame->win.w)
		mygame->draw_endx = mygame->win.w - 1;
	mygame->stripe = mygame->draw_startx;
}

void		raysprite(t_game_draw *mygame)
{
	mygame->el_count = 0;
	while (mygame->el_count < mygame->spr_total)
	{
		mygame->spritex = mygame->sprite[mygame->el_count].spr_pos.x -
		(mygame->rc.posx - 0.5);
		mygame->spritey = mygame->sprite[mygame->el_count].spr_pos.y -
		(mygame->rc.posy - 0.5);
		calc_transf(mygame);
		calc_transf2(mygame);
		dy(mygame);
		mygame->el_count++;
	}
}
