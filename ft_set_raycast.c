/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_raycast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 10:42:41 by irodrigo          #+#    #+#             */
/*   Updated: 2021/02/27 19:20:58 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

/*void	ft_draw_rc(t_game_draw *mygame)
{
	int y;

	y = 0;
	while (y < mygame->win.h)
    {
		if (y < mygame->drawstart)
            ft_mlx_pixel_put(mygame, mygame->rc.x, y, mygame->stat_txt.ceil);
        else if (y >= mygame->drawstart && y <= mygame->drawend)
			//ft_mlx_pixel_put(mygame, mygame->col, y, ft_getpixel(mygame, mygame->x_text, mygame->y_text));
            ft_mlx_pixel_put(mygame, mygame->rc.x, y, 0x00ff00);
        else if (y > mygame->drawend)
            ft_mlx_pixel_put(mygame, mygame->rc.x, y, mygame->stat_txt.floor);
        y++;
	}
}*/


/*pendiente*/
void	ft_id_texture(t_game_draw *mygame)
{
	if (mygame->rc.side == 0 && mygame->rc.raydirx > 0)
		mygame->tx.id = 2;
		//mygame->id = 3; // texture.id o tx.id
	if (mygame->rc.side == 0 && mygame->rc.raydirx <= 0)
		mygame->tx.id = 1;
		//mygame->id = 2;
	if (mygame->rc.side == 1 && mygame->rc.raydiry > 0)
		mygame->tx.id = 3;
		//mygame->id = 4;
	if (mygame->rc.side == 1 && mygame->rc.raydiry <= 0)
		mygame->tx.id = 0;
		//mygame->id = 0;
}


/*void	raycauxtwo(t_game_draw *mygame)
{
	if (mygame->rc.side == 0 && mygame->rc.raydirx > 0)
		mygame->id = 3;
	if (mygame->rc.side == 0 && mygame->rc.raydirx <= 0)
		mygame->id = 2;
	if (mygame->rc.side == 1 && mygame->rc.raydiry > 0)
		mygame->id = 4;
	if (mygame->rc.side == 1 && mygame->rc.raydiry <= 0)
		mygame->id = 0;
}*/

void	raycasting(t_game_draw *mygame)
{
	mygame->rc.x = 0;
	mygame->canvas = mlx_new_image(mygame->mlx_ptr, mygame->win.w, mygame->win.h);
	mygame->canvas_ptr = mlx_get_data_addr(mygame->canvas, &mygame->c_bpp, &mygame->c_sline,
		&mygame->c_endian);
	while (mygame->rc.x < mygame->win.w)
	{
		mygame->rc.camerax = 2 * mygame->rc.x / (double)(mygame->win.w) - 1;
		mygame->rc.raydirx = mygame->rc.dirx + mygame->rc.planex * mygame->rc.camerax;
		mygame->rc.raydiry = mygame->rc.diry + mygame->rc.planey * mygame->rc.camerax;
		mygame->rc.mapx = (int) mygame->rc.posx;
		mygame->rc.mapy = (int) mygame->rc.posy;
		mygame->rc.deltadistx = fabs(1 / mygame->rc.raydirx);
		mygame->rc.deltadisty = fabs(1 / mygame->rc.raydiry);
		mygame->rc.hit = 0;
		ft_calc_step(mygame);

		mygame->rc.x++;
	}
	to_img(mygame);





	//mygame->col = 0;
	//mygame->img = mlx_new_image(mygame->mlx_ptr, mygame->win.w, mygame->win.h);
	//mygame->img_ptr = mlx_get_data_addr(mygame->img, &mygame->bpp, &mygame->sl,
	//	&mygame->endian);
	//while (mygame->col < mygame->win.w)
	//{
		//mygame->camerax = 2 * mygame->col / (double)(mygame->win.w) - 1
		//mygame->raydir.x = mygame->dir.x + mygame->plane.x * mygame->camerax;
		//mygame->raydir.y = mygame->dir.y + mygame->plane.y * mygame->camerax;
		//mygame->map.x = (int)mygame->pos.x;
		//mygame->map.y = (int)mygame->pos.y;
		//mygame->deltadist.x = fabs((1 / mygame->raydir.x));
		//mygame->deltadist.y = fabs((1 / mygame->raydir.y));
		//mygame->hit = 0;
		//ft_calc_step(mygame);




	/*	mygame->zbuffer[mygame->col] = mygame->perpwalldist;
	}
	to_img(mygame);*/
	/*if (mygame->obj == 1)
		//draw_sprite(mygame);
	to_img(mygame);*/
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
		mygame->rc.sidedisty = (mygame->rc.mapy  + 1.0 - mygame->rc.posy)
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
		if (mygame->worldmap[mygame->rc.mapy][mygame->rc.mapx] > '0')
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
			(1 - mygame->rc.stepy) / 2) /mygame->rc.raydiry;
	mygame->rc.lineheight = (int) (mygame->win.h / mygame->rc.perpwalldist);
	mygame->rc.drawstart = -mygame->rc.lineheight / 2 + mygame->win.h / 2;
	if (mygame->rc.drawstart < 0)
		mygame->rc.drawstart = 0;
	mygame->rc.drawend = mygame->rc.lineheight / 2 + mygame->win.h / 2;
	if (mygame->rc.drawend >= mygame->win.h)
		mygame->rc.drawend = mygame->win.h - 1;
	ft_id_texture(mygame); //funcion nueva



	// recien quitadas
	//raycauxtwo(mygame);
	//ft_draw_rc(mygame);

	// codigo original
	//if (mygame->side == 0)
	//	mygame->perpwalldist = (mygame->map.x - mygame->pos.x +
	//	(1 - mygame->step.x) / 2) / mygame->raydir.x;
	//else

	//	mygame->perpwalldist = (mygame->map.y - mygame->pos.y +
	//		(1 - mygame->step.y) / 2) / mygame->raydir.y;

	//mygame->lineheight = (int)(mygame->win.h / mygame->perpwalldist);
	//mygame->drawstart = -mygame->lineheight / 2 + mygame->win.h / 2;
	//if (mygame->drawstart < 0)
	//	mygame->drawstart = 0;
	//mygame->drawend = mygame->lineheight / 2 + mygame->win.h / 2;
	//if (mygame->drawend >= mygame->win.h)
	//	mygame->drawend = mygame->win.h - 1;
	//raycauxtwo(mygame);

	ft_texturing_calc(mygame);
	ft_draw_vertline(mygame);

	//auxline(mygame);
	//ft_verline(mygame);
	//mygame->col++;
}
