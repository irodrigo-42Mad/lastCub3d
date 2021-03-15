/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 11:57:05 by irodrigo          #+#    #+#             */
/*   Updated: 2021/03/13 23:32:10 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_clean_arr(char *data)
{
	int i;

	i = (ft_strlen(data) - 1);
	while (data[i] != NULL && i >= 0)
	{
		data[i] = NULL;
		i--;
	}
}

void	ft_fretable(char **fra)
{
	int		pos;

	pos = -1;
	while (fra[++pos] != NULL)
	{
		free(fra[pos]);
		fra[pos] = NULL;
	}
	free(fra[pos]);
	fra[pos] = NULL;
	free(fra);
	fra = NULL;
}

void	ft_freemap(t_game_draw *mygame)
{
	int		pos;

	pos = -1;
	while (mygame->worldmap[++pos] != NULL)
	{
		free(mygame->worldmap[pos]);
		mygame->worldmap[pos] = NULL;
	}
	free(mygame->worldmap);
	mygame->worldmap = NULL;
}

void	ft_freearray(char **str)
{
	int elm;

	elm = 0;
	if (str)
	{
		while (str[elm])
		{
			if (str[elm] != '\0')
				free(str[elm]);
			elm++;
		}
		free(str);
	}
}
