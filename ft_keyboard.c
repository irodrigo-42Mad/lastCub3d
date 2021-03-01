/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyboard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 02:44:05 by irodrigo          #+#    #+#             */
/*   Updated: 2021/02/27 14:35:19 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

/*
**en todos los procedimientos se cambia x e y, ya que el primer valor
**de la tabla es la altura y el segundo la anchura en todos los proce
**dimientos de movimiento.
*/

void	w_and_s(t_game_draw *mygame)
{
	if (mygame->key.w_status == 1)
	{
		if ((mygame->worldmap[(int)mygame->rc.posy][(int)(mygame->rc.posx +
			mygame->rc.dirx * (mygame->rc.movespeed))]) == '0')
			mygame->rc.posx += mygame->rc.dirx * mygame->rc.movespeed;
		if ((mygame->worldmap[(int)(mygame->rc.posy + mygame->rc.diry *
			(mygame->rc.movespeed))][(int)mygame->rc.posx]) == '0')
			mygame->rc.posy += mygame->rc.diry * mygame->rc.movespeed;
	}
	if (mygame->key.s_status == 1)
	{
		if ((mygame->worldmap[(int)mygame->rc.posy][(int)(mygame->rc.posx -
			mygame->rc.dirx * (mygame->rc.movespeed))]) == '0')
			mygame->rc.posx -= mygame->rc.dirx * mygame->rc.movespeed;
		if ((mygame->worldmap[(int)(mygame->rc.posy - mygame->rc.diry *
			(mygame->rc.movespeed))][(int)mygame->rc.posx]) != '1')
			mygame->rc.posy -= mygame->rc.diry * mygame->rc.movespeed;
	}
}

void	a_and_d(t_game_draw *mygame)
{
	if (mygame->key.d_status == 1)
	{
		if ((mygame->worldmap[(int)mygame->rc.posy][(int)(mygame->rc.posx -
			mygame->rc.diry * (mygame->rc.movespeed))]) != '1')
			mygame->rc.posx -= mygame->rc.diry * mygame->rc.movespeed;
		if ((mygame->worldmap[(int)(mygame->rc.posy + mygame->rc.dirx *
			(mygame->rc.movespeed))][(int)mygame->rc.posx]) != '1')
			mygame->rc.posy += mygame->rc.dirx * mygame->rc.movespeed;
	}
	if (mygame->key.a_status == 1)
	{
		if ((mygame->worldmap[(int)mygame->rc.posy][(int)(mygame->rc.posx +
			mygame->rc.diry * (mygame->rc.movespeed))]) != '1')
			mygame->rc.posx += mygame->rc.diry * mygame->rc.movespeed;
		if ((mygame->worldmap[(int)(mygame->rc.posy - mygame->rc.dirx *
			(mygame->rc.movespeed))][(int)mygame->rc.posx]) != '1')
			mygame->rc.posy -= mygame->rc.dirx * mygame->rc.movespeed;
	}
}

void	l_and_r(t_game_draw *mygame)
{
	mygame->rc.olddirx = mygame->rc.dirx;
	if (mygame->key.rg_status == 1)
	{
		mygame->rc.dirx = mygame->rc.dirx * cos(mygame->rc.rotspeed)
			- mygame->rc.diry * sin(mygame->rc.rotspeed);
		mygame->rc.diry = mygame->rc.olddirx * sin(mygame->rc.rotspeed) +
					mygame->rc.diry * cos(mygame->rc.rotspeed);
		mygame->rc.oldplanex = mygame->rc.planex;
		mygame->rc.planex = mygame->rc.planex * cos(-mygame->rc.rotspeed)
			- mygame->rc.planey * sin(mygame->rc.rotspeed);
		mygame->rc.planey = mygame->rc.oldplanex * sin(mygame->rc.rotspeed)
			+ mygame->rc.planey * cos(-mygame->rc.rotspeed);
	}
	if (mygame->key.lf_status == 1)
	{
		mygame->rc.dirx = mygame->rc.dirx * cos(-mygame->rc.rotspeed)
			- mygame->rc.diry * sin(-mygame->rc.rotspeed);
		mygame->rc.diry = mygame->rc.olddirx * sin(-mygame->rc.rotspeed) +
					mygame->rc.diry * cos(-mygame->rc.rotspeed);
		mygame->rc.oldplanex = mygame->rc.planex;
		mygame->rc.planex = mygame->rc.planex * cos(-mygame->rc.rotspeed) -
			mygame->rc.planey * sin(-mygame->rc.rotspeed);
		mygame->rc.planey = mygame->rc.oldplanex * sin(-mygame->rc.rotspeed)
			+ mygame->rc.planey * cos(-mygame->rc.rotspeed);
	}
}

int		ft_close(t_game_draw *mygame, int win)
{
	free(mygame->worldmap);
	free(mygame);
	if (win == 1)
		mlx_destroy_window(mygame->mlx_ptr, mygame->mlx_win);
	free(mygame->mlx_ptr);
	exit(0);
}

int		deal_key(t_game_draw *mygame)
{
	raycasting(mygame);
	w_and_s(mygame);
	a_and_d(mygame);
	l_and_r(mygame);
	if (mygame->key.esc_status == 1)
		ft_close(mygame, 1);
	return (1);
}
