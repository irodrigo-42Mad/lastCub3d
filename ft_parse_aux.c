/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 12:26:56 by irodrigo          #+#    #+#             */
/*   Updated: 2021/03/15 14:13:20 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			checkmap(t_game_draw *mygame)
{
	char **tmp;
	int i;

	if (!(tmp = (char**)malloc(sizeof(char *) *
			mygame->map_dim.h + 1)))
			return (-1);
	i = 0;
	while (i < mygame->map_dim.h)
	{
		tmp[i] = ft_strdup(mygame->worldmap[i]);
		i++;
	}
	if (ft_check_content(mygame) == -1)
		return (ft_put_error(TIT_003, MSG1_018, -1));


	if (mygame->idx_pos > 1)
		return (ft_put_error(TIT_003, MSG1_016, -1));
	if (mygame->idx_pos == 0)
		return (ft_put_error(TIT_003, MSG1_015, -1));

	/*if (gamerpos(mygame) == -1)
		return (error(11));*/
	//chequeos de muros cerrados en el mapa
	tmp[mygame->gamer.pos.y][mygame->gamer.pos.x] = '0';
	//a partir de aqui ahora se realiza el chequeo de
	//mapa cerrado
	//ft_checkborder(mygame->gamer.pos.x, mygame->gamer.pos.x, tmp, mygame);
	i = 0;
	while (i < mygame->map_dim.h)
	{
		free(tmp[i]);
		tmp[i] = NULL;
		i++;
	}
	free(tmp);
	tmp = NULL;
	if (mygame->stat_txt.path_no == NULL || mygame->stat_txt.path_so == NULL
		|| mygame->stat_txt.path_ea == NULL || mygame->stat_txt.path_we == NULL)
		return (-1);
	return (1);
}

int			parsename(const char *text, const char *compare)
{
	int len1;
	int len2;
	int cont;
	int act;

	len1 = ft_strlen(text) - 1;
	len2 = ft_strlen(compare);
	act = len2 - 1;
	cont = 0;
	while (cont < len2)
	{
		if (text[len1] != compare[act])
			return (-1);
		cont++;
		act--;
		len1--;
	}
	return (1);
}

int			ft_check_gamer(t_game_draw *mygame)
{
	if (mygame->gamer.count == 0)
		return (ft_put_error(TIT_003, MSG1_015, -1));
	if (mygame->gamer.count > 1)
		return (ft_put_error(TIT_003, MSG1_016, -1));
	return (1);
}


