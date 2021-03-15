/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 16:26:41 by irodrigo          #+#    #+#             */
/*   Updated: 2021/03/13 16:50:01 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void	ft_write_error(char *err_tit, char *errmsg)
{
	write(2, "Error\n", 7);
	write(2, "\n", 2);
	write(2, err_tit, ft_strlen(err_tit));
	write(2, errmsg, ft_strlen(errmsg));
}

int		ft_put_error(char *err_tit, char *errmsg, int err_n)
{
	write(2, "Error\n", 7);
	write(2, "\n", 2);
	write(2, err_tit, ft_strlen(err_tit));
	write(2, errmsg, ft_strlen(errmsg));
	return (err_n);
}

int		ft_file_error(int fd)
{
	if (fd < 0)
	{
		if (fd == -1)
			ft_write_error(TIT_003, MSG1_003);
		if (fd == -2)
			ft_write_error(TIT_003, MSG1_004);
		return (0);
	}
}
