/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 11:36:05 by irodrigo          #+#    #+#             */
/*   Updated: 2021/02/27 18:30:41 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

/*void	put_pxl_to_img(t_game_draw *mygame, int x, int y) //este procedimiento está fallando GRRRR

{
	int n;

	if (x < mygame->win.x && y < mygame->win.y)
	{
		n = abs((((y * (mygame->height[mygame->id] * 4) - mygame->win.y * (mygame->height[mygame->id] * 2)
			+ mygame->lineheight * (mygame->height[mygame->id] * 2)) * mygame->height[mygame->id])
					/ mygame->lineheight) / (mygame->height[mygame->id] * 4));
		ft_memcpy(mygame->img_ptr + (mygame->wbpp[mygame->id] / 8) * mygame->win.x * y
			+ x * (mygame->wbpp[mygame->id] / 8),
			&mygame->wdata[mygame->id][n % mygame->height[mygame->id] * mygame->wsl[mygame->id] +
			mygame->x_text % mygame->width[mygame->id] *
			mygame->wbpp[mygame->id] / 8], sizeof(int));
	}
}*/

void	ft_texturing_calc(t_game_draw *mygame)
{
	if (mygame->rc.side = 0)
		mygame->rc.wallx = mygame->rc.posy + mygame->rc.perpwalldist * mygame->rc.raydiry;
	else
		mygame->rc.wallx = mygame->rc.posy + mygame->rc.perpwalldist * mygame->rc.raydirx;
	mygame->rc.wallx -= floor(mygame->rc.wallx);
	mygame->rc.texx = (int)mygame->rc.wallx * (double)mygame->tx.width[mygame->tx.id];
	if (mygame->rc.side == 0 && mygame->rc.raydirx > 0)
		mygame->rc.texx = mygame->tx.width[mygame->tx.id] - mygame->rc.texx - 1;
	if (mygame->rc.side == 1 && mygame->rc.raydiry < 0)
		mygame->rc.texx = mygame->tx.width[mygame->tx.id] - mygame->rc.texx - 1;
}

// pendiente de cambiar
/*void	auxline(t_game_draw *mygame)
{
	if (mygame->side == 0)
	   mygame->x_wall = mygame->pos.y + mygame->perpwalldist * mygame->raydir.y;
    else
        mygame->x_wall = mygame->pos.x + mygame->perpwalldist * mygame->raydir.x;
    mygame->x_wall -= floor(mygame->x_wall);
    mygame->x_text = (int)(mygame->x_wall * (double)mygame->width[mygame->id]);

    if (mygame->side == 0 && mygame->raydir.x > 0)
        mygame->x_text = mygame->width[mygame->id] - mygame->x_text - 1;
    if (mygame->side == 1 && mygame->raydir.y < 0)
        mygame->x_text = mygame->width[mygame->id] - mygame->x_text - 1;
}*/

void            ft_mlx_pixel_put(t_game_draw *mygame, int x, int y, int color)
{
    char    *dst;
    dst = mygame->canvas_ptr + (y * mygame->c_sline + x * (mygame->c_bpp / 8));
    *(unsigned int *)dst = color;
}

int             ft_getpixel(t_game_draw *map, int x, int y)
{
    char    *dst;
    dst = map->tx.wdata[map->tx.id] + y * map->tx.wsl[map->tx.id]
		+ x * (map->tx.wbpp[map->tx.id] /8);
	return (*(unsigned int*)dst);
}

void	ft_draw_vertline(t_game_draw *mygame)
{
	int 	y;

	y = 0;
	mygame->tx.step = 1.0 * mygame->tx.height[mygame->tx.id]
		/ mygame->rc.lineheight;
	mygame->tx.texpos = (mygame->rc.drawstart - mygame->win.h / 2 +
		mygame->rc.lineheight / 2) * mygame->tx.step;
	while (y < mygame->win.h)
	{
		mygame->rc.texy = (int)mygame->tx.texpos & (mygame->tx.height[mygame->tx.id] - 1);
		if (y < mygame->rc.drawstart)
			ft_mlx_pixel_put(mygame, mygame->rc.x, y, mygame->stat_txt.ceil);
		else if (y >= mygame->rc.drawstart && y <= mygame->rc.drawend)
			// falla al colocar la textura sobre la imágen.
			ft_mlx_pixel_put(mygame, mygame->rc.x, y, ft_getpixel(mygame, mygame->rc.texx, mygame->rc.texy));
		else if (y > mygame->rc.drawend)
			ft_mlx_pixel_put(mygame, mygame->rc.x, y, mygame->stat_txt.floor);
		y++;
	}
}



// funcion antigua
/*void	ft_verline(t_game_draw *mygame)
{
	int     y;

    y = 0;
	mygame->tex_stp = 1.0 * mygame->height[mygame->id]
		/ mygame->lineheight;
    mygame->tex_pos = (mygame->drawstart - mygame->win.h / 2 +
		mygame->lineheight / 2) * mygame->tex_stp;
	while (y < mygame->win.h)
    {
		mygame->y_text = (int)mygame->tex_pos & (mygame->height[mygame->id] - 1);
        if (y < mygame->rc.drawstart)
			//ft_mlx_pixel_put(mygame, mygame->rc.x, y, );
            ft_mlx_pixel_put(mygame, mygame->rc.x, y, mygame->maptx.c);
        else if (y >= mygame->drawstart && y <= mygame->drawend)

			//ft_mlx_pixel_put(mygame, mygame->col, y, ft_getpixel(mygame, mygame->x_text, mygame->y_text));
            ft_mlx_pixel_put(mygame, mygame->col, y, 0);
        else if (y > mygame->drawend)
            ft_mlx_pixel_put(mygame, mygame->col, y, mygame->maptx.f);
        y++;
    }
    y = mygame->drawstart;
    //ft_painttexb(map, x, y);




	/*mygame->j = 0;
	while (mygame->j < mygame->drawstart)
	{
		ft_memcpy(mygame->img_ptr + 4 * mygame->win.x *
			mygame->j + mygame->col * 4,
			&mygame->f, sizeof(int));
		mygame->j++;
	}
	mygame->j = mygame->drawstart;
	if (mygame->sidehit == 0)
	{
		mygame->id = 3;
		mygame->x_wall = mygame->pos.y + mygame->perpwalldist * mygame->ray.y;
	}
	else
	{
		mygame->id = 4;
		mygame->x_wall = mygame->pos.x + mygame->perpwalldist * mygame->ray.x;
	}
	if (mygame->sidehit == 0 && mygame->ray.x > 0)
		mygame->id = 2;
	auxline(mygame);
}*/





