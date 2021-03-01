/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 03:05:32 by jdiaz-co          #+#    #+#             */
/*   Updated: 2021/02/26 23:53:23 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void		put_spr(t_game_draw *mygame)
{
	mygame->sprite[mygame->el_count].spr_texture.y = fabs((mygame->aux_elcount -
		mygame->sprite[mygame->el_count].spr_initial.y) / (mygame->sprite[mygame->el_count].spr_dimens.h /
		(double)mygame->tx.height[7]));
	if (mygame->tx.wdata[7][mygame->sprite[mygame->el_count].spr_texture.y * mygame->tx.wsl[7] +
		mygame->sprite[mygame->el_count].spr_texture.x * mygame->tx.wbpp[7] / 8] != 0)
		ft_memcpy(mygame->canvas_ptr + (mygame->tx.wbpp[7] / 8) * mygame->win.w * mygame->aux_elcount +
			mygame->segment * (mygame->tx.wbpp[7] / 8),
			&mygame->tx.wdata[7][mygame->sprite[mygame->el_count].spr_texture.y * mygame->tx.wsl[7] +
			mygame->sprite[mygame->el_count].spr_texture.x * mygame->tx.wbpp[7] / 8], sizeof(int));
	mygame->aux_elcount++;

	/*mygame->sprite[mygame->el_count].spr_texture.y = fabs((mygame->aux_elcount -
		mygame->sprite[mygame->el_count].spr_initial.y) / (mygame->sprite[mygame->el_count].spr_dimens.h /
		(double)mygame->height[7]));
	if (mygame->wdata[7][mygame->sprite[mygame->el_count].spr_texture.y * mygame->wsl[7] +
		mygame->sprite[mygame->el_count].spr_texture.x * mygame->wbpp[7] / 8] != 0)
		ft_memcpy(mygame->img_ptr + (mygame->wbpp[7] / 8) * mygame->win.w * mygame->aux_elcount +
			mygame->segment * (mygame->wbpp[7] / 8),
			&mygame->wdata[7][mygame->sprite[mygame->el_count].spr_texture.y * mygame->wsl[7] +
			mygame->sprite[mygame->el_count].spr_texture.x * mygame->wbpp[7] / 8], sizeof(int));
	mygame->aux_elcount++;
	*/
}

void		dy(t_game_draw *mygame)
{
	mygame->segment = mygame->sprite[mygame->el_count].spr_initial.x - 1;
	while (mygame->segment < mygame->sprite[mygame->el_count].spr_trace.x)
	{
		mygame->sprite[mygame->el_count].spr_texture.x = (int)((mygame->segment -
			mygame->sprite[mygame->el_count].spr_initial.x) / (mygame->sprite[mygame->el_count].spr_dimens.w /
			(double)mygame->tx.width[7]));
		mygame->aux_elcount = mygame->sprite[mygame->el_count].spr_initial.y;
		if (mygame->sprite[mygame->el_count].transform.y > 0 && mygame->segment > 0 &&
			mygame->segment < mygame->win.w
			&& mygame->sprite[mygame->el_count].transform.y < mygame->zbuffer[mygame->segment])
		{
			while (mygame->aux_elcount < mygame->sprite[mygame->el_count].spr_trace.y)
				put_spr(mygame);
		}
		mygame->segment++;
	}
	mygame->obj = 0;
}

void		calc_transf(t_game_draw *mygame)
{
	double	inv_det;
	double	calc_det;

	calc_det = (mygame->rc.planex * mygame->rc.diry - mygame->rc.dirx * mygame->rc.planey);
	inv_det = 1.0 / calc_det;
	mygame->sprite[mygame->el_count].transform.x = inv_det * (mygame->rc.diry *
		mygame->sprite[mygame->el_count].spr_pos.x - mygame->rc.dirx *
		mygame->sprite[mygame->el_count].spr_pos.y);
	mygame->sprite[mygame->el_count].transform.y = inv_det * (-mygame->rc.planey *
		mygame->sprite[mygame->el_count].spr_pos.x + mygame->rc.planex *
		mygame->sprite[mygame->el_count].spr_pos.y);
	mygame->sprite[mygame->el_count].scrn = (int)((mygame->win.w / 2) *
		(1 + mygame->sprite[mygame->el_count].transform.x /
		mygame->sprite[mygame->el_count].transform.y));
	mygame->sprite[mygame->el_count].spr_dimens.h = abs((int)(mygame->win.h /
		mygame->sprite[mygame->el_count].transform.y));
	mygame->sprite[mygame->el_count].spr_dimens.w = abs((int)(mygame->win.h /
		mygame->sprite[mygame->el_count].transform.y));

	/*calc_det = (mygame->plane.x * mygame->dir.y - mygame->dir.x * mygame->plane.y);
	inv_det = 1.0 / calc_det;
	mygame->sprite[mygame->el_count].transform.x = inv_det * (mygame->dir.y *
		mygame->sprite[mygame->el_count].spr_pos.x - mygame->dir.x *
		mygame->sprite[mygame->el_count].spr_pos.y);
	mygame->sprite[mygame->el_count].transform.y = inv_det * (-mygame->plane.y *
		mygame->sprite[mygame->el_count].spr_pos.x + mygame->plane.x *
		mygame->sprite[mygame->el_count].spr_pos.y);
	mygame->sprite[mygame->el_count].scrn = (int)((mygame->win.w / 2) *
		(1 + mygame->sprite[mygame->el_count].transform.x /
		mygame->sprite[mygame->el_count].transform.y));
	mygame->sprite[mygame->el_count].spr_dimens.h = abs((int)(mygame->win.h /
		mygame->sprite[mygame->el_count].transform.y));
	mygame->sprite[mygame->el_count].spr_dimens.w = abs((int)(mygame->win.h /
		mygame->sprite[mygame->el_count].transform.y));*/
}

void		calc_sprite_place(t_game_draw *mygame)
{
	mygame->sprite[mygame->el_count].spr_initial.y = -mygame->sprite[mygame->el_count].spr_dimens.h / 2 +
		mygame->win.h / 2;
	if (mygame->sprite[mygame->el_count].spr_initial.y < 0)
		mygame->sprite[mygame->el_count].spr_initial.y = 0;
	mygame->sprite[mygame->el_count].spr_trace.y = mygame->sprite[mygame->el_count].spr_dimens.h / 2 +
		mygame->win.h / 2;
	if (mygame->sprite[mygame->el_count].spr_trace.y >= mygame->win.h)
		mygame->sprite[mygame->el_count].spr_trace.y = mygame->win.h - 1;
	mygame->sprite[mygame->el_count].spr_initial.x = -1 * mygame->sprite[mygame->el_count].spr_dimens.w / 2 +
		mygame->sprite[mygame->el_count].scrn;
	if (mygame->sprite[mygame->el_count].spr_initial.x < 0)
		mygame->sprite[mygame->el_count].spr_initial.x = 0;
	mygame->sprite[mygame->el_count].spr_trace.x = mygame->sprite[mygame->el_count].spr_dimens.w / 2 +
		mygame->sprite[mygame->el_count].scrn;
	if (mygame->sprite[mygame->el_count].spr_trace.x >= mygame->win.w)
		mygame->sprite[mygame->el_count].spr_trace.x = mygame->win.w - 1;
}

void		raysprite(t_game_draw *mygame)
{
	mygame->el_count = 0;
	while (mygame->el_count < mygame->spr_total)
	{
		mygame->sprite[mygame->el_count].spr_pos.x =
			mygame->sprite[mygame->allspr_pos[mygame->el_count]].sp_act_pos.x - mygame->rc.posx;
		mygame->sprite[mygame->el_count].spr_pos.y =
			mygame->sprite[mygame->allspr_pos[mygame->el_count]].sp_act_pos.y - mygame->rc.posy;
		calc_transf(mygame);
		calc_sprite_place(mygame);
		dy(mygame);
		mygame->el_count++;
	}
}
