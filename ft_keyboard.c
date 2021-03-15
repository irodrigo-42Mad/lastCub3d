/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyboard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 02:44:05 by irodrigo          #+#    #+#             */
/*   Updated: 2021/03/14 00:51:57 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void	w_and_s(t_game_draw *mygame)
{
	if (mygame->key.w_status == 1)
	{
		if (mygame->worldmap[(int)(mygame->rc.posx + mygame->rc.dirx *
			mygame->rc.movespeed)][(int)mygame->rc.posy] == 48)
			mygame->rc.posx += mygame->rc.dirx * mygame->rc.movespeed;
		if (mygame->worldmap[(int)mygame->rc.posx][(int)(mygame->rc.posy +
			mygame->rc.diry * mygame->rc.movespeed)] == 48)
			mygame->rc.posy += mygame->rc.diry * mygame->rc.movespeed;
	}
	if (mygame->key.s_status == 1)
	{
		if (mygame->worldmap[(int)(mygame->rc.posx - mygame->rc.dirx *
			mygame->rc.movespeed)][(int)mygame->rc.posy] == 48)
			mygame->rc.posx -= mygame->rc.dirx * mygame->rc.movespeed;
		if (mygame->worldmap[(int)mygame->rc.posx][(int)(mygame->rc.posy -
			mygame->rc.diry * mygame->rc.movespeed)] == 48)
			mygame->rc.posy -= mygame->rc.diry * mygame->rc.movespeed;
	}
}

void	a_and_d(t_game_draw *mygame)
{
	if (mygame->key.d_status == 1)
	{
		if (mygame->worldmap[(int)(mygame->rc.posx + mygame->rc.planex *
			mygame->rc.movespeed)][(int)mygame->rc.posy] == '0')
			mygame->rc.posx += mygame->rc.planex * mygame->rc.movespeed;
		if (mygame->worldmap[(int)mygame->rc.posx][(int)(mygame->rc.posy +
			mygame->rc.planey * mygame->rc.movespeed)] == '0')
			mygame->rc.posy += mygame->rc.planey * mygame->rc.movespeed;
	}
	if (mygame->key.a_status == 1)
	{
		if (mygame->worldmap[(int)(mygame->rc.posx - mygame->rc.planex *
			mygame->rc.movespeed)][(int)mygame->rc.posy] == '0')
			mygame->rc.posx -= mygame->rc.planex * mygame->rc.movespeed;
		if (mygame->worldmap[(int)mygame->rc.posx][(int)(mygame->rc.posy -
			mygame->rc.planey * mygame->rc.movespeed)] == '0')
			mygame->rc.posy -= mygame->rc.planey * mygame->rc.movespeed;
	}
}

void	l_and_r(t_game_draw *kbd)
{
	if (kbd->key.rg_status == 1)
	{
		kbd_right(kbd);
	}
	if (kbd->key.lf_status == 1)
	{
		kbd->rc.olddirx = kbd->rc.dirx;
		kbd->rc.dirx = kbd->rc.dirx * cos(kbd->rc.rotspeed)
			- kbd->rc.diry * sin(kbd->rc.rotspeed);
		kbd->rc.diry = kbd->rc.olddirx * sin(kbd->rc.rotspeed) +
					kbd->rc.diry * cos(kbd->rc.rotspeed);
		kbd->rc.oldplanex = kbd->rc.planex;
		kbd->rc.planex = kbd->rc.planex * cos(kbd->rc.rotspeed) -
			kbd->rc.planey * sin(kbd->rc.rotspeed);
		kbd->rc.planey = kbd->rc.oldplanex * sin(kbd->rc.rotspeed)
			+ kbd->rc.planey * cos(kbd->rc.rotspeed);
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
	w_and_s(mygame);
	a_and_d(mygame);
	l_and_r(mygame);
	raycasting(mygame);
	if (mygame->key.esc_status == 1)
		ft_close(mygame, 1);
	return (1);
}
