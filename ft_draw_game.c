/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 11:36:05 by irodrigo          #+#    #+#             */
/*   Updated: 2021/03/10 10:56:04 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void	ft_texturing_calc(t_game_draw *mygame)
{
	if (mygame->rc.side == 0)
		mygame->rc.wallx = mygame->rc.posy + mygame->rc.perpwalldist *
			mygame->rc.raydiry;
	else
		mygame->rc.wallx = mygame->rc.posx + mygame->rc.perpwalldist *
			mygame->rc.raydirx;
	mygame->rc.wallx -= floor(mygame->rc.wallx);
	mygame->rc.texx = (int)(mygame->rc.wallx *
		(double)mygame->tx.width[mygame->tx.id]);
	if (mygame->rc.side == 0 && mygame->rc.raydirx > 0)
		mygame->rc.texx = mygame->tx.width[mygame->tx.id] - mygame->rc.texx - 1;
	if (mygame->rc.side == 1 && mygame->rc.raydiry < 0)
		mygame->rc.texx = mygame->tx.width[mygame->tx.id] - mygame->rc.texx - 1;
}

void	ft_mlx_pixel_put(t_game_draw *mygame, int x, int y, int color)
{
	char	*dst;

	dst = mygame->canvas_ptr + (y * mygame->c_sline + x * (mygame->c_bpp / 8));
	*(unsigned int *)dst = color;
}

int		ft_getpixel(t_game_draw *map, int x, int y)
{
	char	*dst;

	dst = map->tx.wdata[map->tx.id] + y * map->tx.wsl[map->tx.id]
	+ x * (map->tx.wbpp[map->tx.id] / 8);
	return (*(unsigned int*)dst);
}

void	ft_draw_vertline(t_game_draw *mygame)
{
	int		y;

	y = 0;
	mygame->tx.step = 1.0 * mygame->tx.height[mygame->tx.id]
		/ mygame->rc.lineheight;
	mygame->tx.texpos = (mygame->rc.drawstart - mygame->win.h / 2 +
		mygame->rc.lineheight / 2) * mygame->tx.step;
	while (y < mygame->win.h)
	{
		if (y < mygame->rc.drawstart)
			ft_mlx_pixel_put(mygame, mygame->rc.x, y, mygame->stat_txt.ceil);
		else if (y >= mygame->rc.drawstart && y <= mygame->rc.drawend)
		{
			mygame->rc.texy = (int)mygame->tx.texpos &
				(mygame->tx.height[mygame->tx.id] - 1);
			mygame->tx.texpos += mygame->tx.step;
			ft_mlx_pixel_put(mygame, mygame->rc.x, y,
				ft_getpixel(mygame, mygame->rc.texx, mygame->rc.texy));
		}
		else if (y > mygame->rc.drawend)
			ft_mlx_pixel_put(mygame, mygame->rc.x, y, mygame->stat_txt.floor);
		y++;
	}
}
