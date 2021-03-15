/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aux_fnc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 13:55:28 by irodrigo          #+#    #+#             */
/*   Updated: 2021/03/13 23:24:22 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_atoi_cub(char *line, int *pos)
{
	int	num;

	num = 0;
	ft_skip_spaces(line, pos);
	while (line[*pos] >= '0' && line[*pos] <= '9')
	{
		num = num * 10 + (line[*pos] - 48);
		(*pos)++;
	}
	return (num);
}
