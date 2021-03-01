/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_textures.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 11:52:44 by irodrigo          #+#    #+#             */
/*   Updated: 2021/02/23 12:27:53 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_init_textures(t_game_draw mygame, char *path)
{
	int		fd;

	if ((fd = open(path, O_RDONLY)) == -1)
		return (-1);
}

