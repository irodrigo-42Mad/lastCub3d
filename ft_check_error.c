/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 16:26:41 by irodrigo          #+#    #+#             */
/*   Updated: 2021/01/12 21:00:27 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void	ft_write_error(char *err_tit, char *errmsg)
{
		write(2, "Error\n", 7);
		write(2, "\n",2);
		write(2, err_tit, ft_strlen(err_tit));
		write(2, errmsg, ft_strlen(errmsg));
}

int		ft_put_error (char *err_tit, char *errmsg, int err_n)
{
		write(2, "Error\n", 7);
		write(2, "\n",2);
		write(2, err_tit, ft_strlen(err_tit));
		write(2, errmsg, ft_strlen(errmsg));
		return err_n;
}







int	error(int i)
{
	write(1, "Error\n", 7);
	if (i == 0)
		write(1, "Incorrect file entered\n", 24);
	else if (i == 1)
		write(1, "Check the map, it´s wrong\n", 28);
	else if (i == 2)
		write(1, "Wrong arguments, leaving CUB3D\n", 32);
	else if (i == 3)
		write(1, "Malloc error\n", 14);
	else if (i == 4)
		write(1, "Bad argument\n", 14);
	else if (i == 5)
		write(1, "Two or more players in the map\n", 32);
	else if (i == 6)
		write(1, "Wrong map, close walls\n", 23);
	else if (i == 7)
		write(1, "The border´s map are wrong\n", 29);
	else if (i == 8)
		write(1, "File reading failure\n", 21);
	else if (i == 9)
		write(1, "No players on the map\n", 23);
	else if (i == 10)
		write(1, "Incorrect program name\n",24);  //en revision
	else if (i == 11)
		write(1, "player outside or over wall\n", 30);
	else if (i == 12)
		write(1, "solid horizontal wall divide map\n", 34);
	else if (i == 13)
		write(1, "solid vertical wall divide map\n", 32);

	return (-1);
}
