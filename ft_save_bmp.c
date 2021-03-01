/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save_bmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 12:09:19 by irodrigo          #+#    #+#             */
/*   Updated: 2021/02/27 19:17:50 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

int		doscreenshot(t_game_draw *mygame)
{
	int file;
	int filesize;
	int	pad;

	pad = (4 - ((int)mygame->win.w * 3) % 4) % 4;
	filesize = 60 + (3 * ((int)mygame->win.w + pad) * (int)mygame->win.h);
	remove("screenshot.bmp");
	if ((file = open("screenshot.bmp", O_WRONLY | O_CREAT
		| O_TRUNC | O_APPEND, 777)) < 0)
		return (0);
	if (!write_bmp_header(file, filesize, mygame))
		return (0);
	if (!write_bmp_data(file, mygame, pad))
		return (0);
	close(file);
	return (1);
}

void	to_img(t_game_draw *mygame)
{
	mlx_put_image_to_window(mygame->mlx_ptr, mygame->mlx_win,
		mygame->canvas, 0, 0);
	if (mygame->screenshot == 1)
	{
		doscreenshot(mygame);
		exit(1);
	}
	mlx_destroy_image(mygame->mlx_ptr, mygame->canvas);
}

/*
**	//extra personaje tras put_image_to_window proceso to_img
**	//mlx_put_image_to_window(mygame->mlx_ptr, mygame->mlx_win,
**	//	mygame->wlone[5], mygame->fr_pos.x, mygame->fr_pos.y);
*/
