/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 12:02:34 by irodrigo          #+#    #+#             */
/*   Updated: 2021/03/15 13:54:44 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

int			get_height(char *str)
{
	int	i;
	int	h;

	i = 0;
	h = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			h++;
		i++;
	}
	return (h);
}

int			get_width(char *str)
{
	int		w;
	int		i;
	int		temp;

	w = 0;
	i = 0;
	temp = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]))
			temp++;
		if (str[i] == '\n')
		{
			if (temp > w)
				w = temp;
			temp = 0;
		}
		i++;
	}
	return (w);
}

void		ft_changetab(t_game_draw *mygame)
{
	int	i;

	i = 0;
	while (mygame->mapchar[i] != '\0')
	{
		if (mygame->mapchar[i] == '\t')
			mygame->mapchar[i] = '8';
		if (mygame->mapchar[i] == ' ')
			mygame->mapchar[i] = '9';
		if (mygame->mapchar[i] == 'N' || mygame->mapchar[i] == 'S'
			|| mygame->mapchar[i] == 'W' || mygame->mapchar[i] == 'E')
		{
			mygame->gamer.spr_dir = mygame->mapchar[i];
			mygame->gamer.count++;
			mygame->mapchar[i] = '3';
		}
		if (mygame->mapchar[i] == '2')
			mygame->spr_total++;
		i++;
	}
	mygame->sprite = malloc(mygame->spr_total * sizeof(t_sprite));
}

void		ft_create_matrix(t_game_draw *mygame)
{
	int line;
	int pos;
	int mat_pos;
	int dimen;
	int prueba;

	line = 0;
	dimen = 0;
	pos = 0;
	if (!mygame->worldmap)
		if (!(mygame->worldmap = (char **)malloc(sizeof(char *)
			* mygame->map_dim.h + 1)))
			return ;
	while (line < mygame->map_dim.h && mygame->mapchar[pos])
	{
		if (line == 1)
			prueba = 1;
		dimen = ft_get_line_width(mygame->mapchar, pos);
		if (!(mygame->worldmap[line] = (char *)malloc(sizeof(char) * dimen)))
			return ;
		mat_pos = 0;
		while (mat_pos < (dimen) && mygame->mapchar[pos] != '\n')
		{
			mat_pos = ft_setmap_ch(mygame, mat_pos, line, pos);
			pos++;
		}
		pos++;
		line++;
	}
}

int			ft_setmap_ch(t_game_draw *mygame, int mat_pos, int line, int pos)
{
	int i;

	i = 0;
	if (mygame->mapchar[pos] == '0' || mygame->mapchar[pos] == '1'
		|| mygame->mapchar[pos] == '2' || mygame->mapchar[pos] == '3')
	{
		if (mygame->mapchar[pos] == '3')
			ft_setgamerpos(mygame, mat_pos, line);
		mygame->worldmap[line][mat_pos] = mygame->mapchar[pos];
	}
	else if (mygame->mapchar[pos] == '9')
		mygame->worldmap[line][mat_pos] = '0';
	else if (mygame->mapchar[pos] == '8')
		while (i < 4)
		{
			mygame->worldmap[line][mat_pos] = '0';
			i++;
			mat_pos++;
		}
	if (i == 4)
		mat_pos--;
	mat_pos++;
	return (mat_pos);
}

/*
**Funcion que permite calcular el ancho de la linea actual
*/

int			ft_get_line_width(char *mapchar, int pos)
{
	int count;
	int len;

	count = 0;
	len = 0;
	while (mapchar[pos] != '\n')
	{
		if (mapchar[pos] == '8')
			count++;
		len++;
		pos++;
	}
	count = (count * 4);
	return (len + count + 1);
}
