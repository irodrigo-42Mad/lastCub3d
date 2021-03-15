/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 16:27:52 by irodrigo          #+#    #+#             */
/*   Updated: 2021/03/14 00:30:01 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_chk_read(char *fname)
{
	int fd;
	int errno;

	fd = open(fname, O_RDONLY);
	if (fd < 0)
		return (errno == ENOENT) ? -1 : -2;
	return (fd);
}

/*
**return -1	 es error al cargar la textura en la matriz de texturas
*/

int		ft_charge_txt(t_game_draw *mygame, int elm, char *path)
{
	mygame->tx.wlone[elm] = mlx_xpm_file_to_image(mygame->mlx_ptr, path,
		&mygame->tx.width[elm], &mygame->tx.height[elm]);
	if (mygame->tx.wlone[elm] == NULL || mygame->tx.width[elm] != 64
		|| mygame->tx.height[elm] != 64)
		return (-1);
	mygame->tx.wdata[elm] = mlx_get_data_addr(mygame->tx.wlone[elm],
		&mygame->tx.wbpp[elm], &mygame->tx.wsl[elm], &mygame->tx.wendian[elm]);
	return (0);
}

int		ft_load_txt(t_game_draw *mygame)
{
	int i;
	int status;

	i = 0;
	while (i < 5 && status == 0)
	{
		if (i == 0)
			status = ft_charge_txt(mygame, i, mygame->stat_txt.path_no);
		if (i == 1)
			status = ft_charge_txt(mygame, i, mygame->stat_txt.path_so);
		if (i == 2)
			status = ft_charge_txt(mygame, i, mygame->stat_txt.path_ea);
		if (i == 3)
			status = ft_charge_txt(mygame, i, mygame->stat_txt.path_we);
		if (i == 4)
			status = ft_charge_txt(mygame, i, mygame->stat_txt.path_spr);
		i++;
	}
	if (status < 0)
		return (-1);
	else
		return (0);
}
