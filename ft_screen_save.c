/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_screen_save.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 03:24:19 by irodrigo          #+#    #+#             */
/*   Updated: 2021/02/27 19:22:41 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void	set_int_in_char(unsigned char *start, int value)
{
	start[0] = (unsigned char)(value);
	start[1] = (unsigned char)(value >> 8);
	start[2] = (unsigned char)(value >> 16);
	start[3] = (unsigned char)(value >> 24);
}

int		get_color(t_game_draw *mygame, int x, int y)
{
	int	rgb;
	int	color;

	color = *(int*)(mygame->canvas_ptr
			+ (4 * (int)mygame->win.w * ((int)mygame->win.h - 1 - y))
			+ (4 * x));
	rgb = (color & 0xFF0000) | (color & 0x00FF00) | (color & 0x0000FF);
	return (rgb);
}

int		write_bmp_header(int fd, int filesize, t_game_draw *mygame)
{
	int				i;
	unsigned char	bmpfileheader[60];

	i = 0;
	while (i < 60)
		bmpfileheader[i++] = (unsigned char)(0);
	bmpfileheader[0] = (unsigned char)('B');
	bmpfileheader[1] = (unsigned char)('M');
	set_int_in_char(bmpfileheader + 2, filesize);
	bmpfileheader[10] = (unsigned char)(60);
	bmpfileheader[14] = (unsigned char)(40);
	set_int_in_char(bmpfileheader + 18, mygame->win.w);
	set_int_in_char(bmpfileheader + 22, mygame->win.h);
	bmpfileheader[27] = (unsigned char)(1);
	bmpfileheader[28] = (unsigned char)(24);
	return (!(write(fd, bmpfileheader, 60) < 0));
}

int		write_bmp_data(int file, t_game_draw *mygame, int pad)
{
	const unsigned char	zero[3] = {0, 0, 0};
	int					i;
	int					j;
	int					color;

	i = 0;
	while (i < (int)mygame->win.h)
	{
		j = 0;
		while (j < (int)mygame->win.w)
		{
			color = get_color(mygame, j, i);
			if (write(file, &color, 3) < 0)
				return (0);
			if (pad > 0 && write(file, &zero, pad) < 0)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
