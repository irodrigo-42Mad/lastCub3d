/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_raycast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 10:42:41 by irodrigo          #+#    #+#             */
/*   Updated: 2021/03/12 13:04:39 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

/*
**pendiente
**0  north texture
**1  south texture
**2  east texture
**3  west texture
*/

void	ft_id_texture(t_game_draw *mygame)
{
	if (mygame->rc.side == 0 && mygame->rc.raydirx > 0)
		mygame->tx.id = 0;
	if (mygame->rc.side == 0 && mygame->rc.raydirx <= 0)
		mygame->tx.id = 1;
	if (mygame->rc.side == 1 && mygame->rc.raydiry > 0)
		mygame->tx.id = 2;
	if (mygame->rc.side == 1 && mygame->rc.raydiry <= 0)
		mygame->tx.id = 3;
}

void	raycasting(t_game_draw *mygame)
{
	mygame->rc.x = 0;
	mygame->canvas = mlx_new_image(mygame->mlx_ptr,
		mygame->win.w, mygame->win.h);
	mygame->canvas_ptr = mlx_get_data_addr(mygame->canvas,
		&mygame->c_bpp, &mygame->c_sline, &mygame->c_endian);
	while (mygame->rc.x < mygame->win.w)
	{
		mygame->rc.camerax = 2 * mygame->rc.x / (double)(mygame->win.w) - 1;
		mygame->rc.raydirx = mygame->rc.dirx +
			mygame->rc.planex * mygame->rc.camerax;
		mygame->rc.raydiry = mygame->rc.diry +
			mygame->rc.planey * mygame->rc.camerax;
		mygame->rc.mapx = (int)mygame->rc.posx;
		mygame->rc.mapy = (int)mygame->rc.posy;
		mygame->rc.deltadistx = fabs(1 / mygame->rc.raydirx);
		mygame->rc.deltadisty = fabs(1 / mygame->rc.raydiry);
		mygame->rc.hit = 0;
		ft_calc_step(mygame);
		mygame->zbuffer[mygame->rc.x] = mygame->rc.perpwalldist;
		mygame->rc.x++;
	}
	draw_sprite(mygame);
	to_img(mygame);
}

void	ft_calc_step(t_game_draw *mygame)
{
	if (mygame->rc.raydirx < 0)
	{
		mygame->rc.stepx = -1;
		mygame->rc.sidedistx = (mygame->rc.posx - mygame->rc.mapx)
				* mygame->rc.deltadistx;
	}
	else
	{
		mygame->rc.stepx = 1;
		mygame->rc.sidedistx = (mygame->rc.mapx + 1.0 - mygame->rc.posx)
				* mygame->rc.deltadistx;
	}
	if (mygame->rc.raydiry < 0)
	{
		mygame->rc.stepy = -1;
		mygame->rc.sidedisty = (mygame->rc.posy - mygame->rc.mapy)
				* mygame->rc.deltadisty;
	}
	else
	{
		mygame->rc.stepy = 1;
		mygame->rc.sidedisty = (mygame->rc.mapy + 1.0 - mygame->rc.posy)
				* mygame->rc.deltadisty;
	}
	ft_perf_dda(mygame);
}

void	ft_perf_dda(t_game_draw *mygame)
{
	while (mygame->rc.hit == 0)
	{
		if (mygame->rc.sidedistx < mygame->rc.sidedisty)
		{
			mygame->rc.sidedistx += mygame->rc.deltadistx;
			mygame->rc.mapx += mygame->rc.stepx;
			mygame->rc.side = 0;
		}
		else
		{
			mygame->rc.sidedisty += mygame->rc.deltadisty;
			mygame->rc.mapy += mygame->rc.stepy;
			mygame->rc.side = 1;
		}
		if (mygame->worldmap[mygame->rc.mapx][mygame->rc.mapy] == 49)
			mygame->rc.hit = 1;
		ft_perp_dist(mygame);
	}
}

void	ft_perp_dist(t_game_draw *mygame)
{
	if (mygame->rc.side == 0)
		mygame->rc.perpwalldist = (mygame->rc.mapx - mygame->rc.posx +
			(1 - mygame->rc.stepx) / 2) / mygame->rc.raydirx;
	else
		mygame->rc.perpwalldist = (mygame->rc.mapy - mygame->rc.posy +
			(1 - mygame->rc.stepy) / 2) / mygame->rc.raydiry;
	mygame->rc.lineheight = (int)(mygame->win.h / mygame->rc.perpwalldist);
	mygame->rc.drawstart = -mygame->rc.lineheight / 2 + mygame->win.h / 2;
	if (mygame->rc.drawstart < 0)
		mygame->rc.drawstart = 0;
	mygame->rc.drawend = mygame->rc.lineheight / 2 + mygame->win.h / 2;
	if (mygame->rc.drawend >= mygame->win.h)
		mygame->rc.drawend = mygame->win.h - 1;
	ft_id_texture(mygame);
	ft_texturing_calc(mygame);
	ft_draw_vertline(mygame);
}
