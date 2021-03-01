/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 12:02:34 by irodrigo          #+#    #+#             */
/*   Updated: 2021/02/26 14:47:46 by irodrigo         ###   ########.fr       */
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
	mygame->sprite = malloc(mygame->spr_total * sizeof(t_sprite)); // todavia no dibujamos
	//mygame->spr_total = 0;
}

/*void		stringtoarray(t_game_draw *mygame)
{
	if (mygame->mapchar[mygame->n] == '8')
	{
		// ver como se puede dejar esto más corto.
		mygame->worldmap[mygame->mtx.x][mygame->mtx.y++] = '9';
		mygame->worldmap[mygame->mtx.x][mygame->mtx.y++] = '9';
		mygame->worldmap[mygame->mtx.x][mygame->mtx.y++] = '9';
		mygame->worldmap[mygame->mtx.x][mygame->mtx.y] = '9';
	}
	else if (mygame->mapchar[mygame->n] == '9')
		mygame->worldmap[mygame->mtx.x][mygame->mtx.y] = '9';
	else if (mygame->mapchar[mygame->n] == '\n' || mygame->mapchar[mygame->n] == '\0')
	{
		while (mygame->mtx.y <= get_width(mygame->mapchar))
		{
			mygame->worldmap[mygame->mtx.x][mygame->mtx.y] = '9';
			mygame->mtx.y++;
		}
		mygame->n -= 1;
	}
	else
		mygame->worldmap[mygame->mtx.x][mygame->mtx.y] = mygame->mapchar[mygame->n] - 48;
	mygame->n++;
	mygame->mtx.y++;
}*/

void		ft_create_matrix(t_game_draw *mygame)
{
	int line;
	int colum;
	int pos;
	int mat_pos;
	int dimen;
	int prueba;

	line = 0;
	dimen = 0;
	pos = 0;
	if (!mygame->worldmap)
		if (!(mygame->worldmap = ft_calloc(mygame->map_dim.h, sizeof(char *))))
			return ;
	while (line < mygame->map_dim.h && mygame->mapchar[pos])
	{
		if (line == 1 )
			prueba = 1;
		dimen = ft_get_line_width(mygame->mapchar, pos);
		if (!(mygame->worldmap[line] = ft_calloc(dimen, sizeof(char *))))
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
		{
			mygame->gamer.pos.x = mat_pos;
			mygame->gamer.pos.y = line;
		}
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
	if(i == 4)
		mat_pos--;
	mat_pos++;
	// revisar a ver que pasa cuando hay tabulaciones
	return (mat_pos);

/*	{
		f->map[i][j] = (int)f->buff[k] - '0';
		if (f->buff[k] == '2')
			f->sprite_num++;
	}
	else if (f->buff[k] == ' ')
		f->map[i][j] = 4;
	else if ((f->buff[k] == 'N' || f->buff[k] == 'S' || f->buff[k] == 'E'
		|| f->buff[k] == 'W') && f->dir == '\0')
	{
		f->map[i][j] = 0;
		f->dir = f->buff[k];
		f->pos[0] = i;
		f->ml.pos.x = i + 0.5;
		f->pos[1] = j;
		f->ml.pos.y = j + 0.5;
		ft_cast_init_dir(f);
	}
	else
		ft_handle_error_ptr("ERROR IN MAP\n", (void *)f->map);*/
}




	/*int pos;
	int auxpos;
	int line;
	int act_line;
	int pos_ini;
	int pos_fin;


	pos = 0;
	auxpos = 0;
	line = 0;
	act_line = 0;

	while(line < mygame->map_dim.h)
	{
		ft_get_line_width(*mygame->mapchar, &pos_ini, &pos_fin);
		printf("%d",ft_get_line_tabs(*mygame->mapchar,pos_ini,pos_fin));
		//pos_fin = pos + len;
	}*/



int		ft_get_line_width(char *mapchar, int pos)
{
	// funcion que permite calcular el ancho de la linea actual
	int count;
	int len;

	count = 0;
	len = 0;
	while(mapchar[pos] != '\n')
	{
		if(mapchar[pos] == '8')
			count++;
		len++;
		pos++;
	}
	count = (count * 4);
	return (len + count + 1);
}
/*
int get_line_tabs()
{


}*/


/*void		matrix(t_game_draw *mygame)
{

	mygame->mtx.x = 0;
	mygame->n = 0;
	if (!mygame->worldmap)
		if (!(mygame->worldmap = (char **)malloc(sizeof(char *) *
			get_height(mygame->mapchar) + 1)))
			return ;
	mygame->worldmap = ft_split(mygame->mapchar, '\n');

/*
	while (mygame->mtx.x <= get_height(mygame->mapchar))
	{
		if (!(mygame->worldmap[mygame->mtx.x] = malloc(sizeof(int) *
			(get_width(mygame->mapchar) + 1))))
			return ;
		mygame->mtx.y = 0;
		while (mygame->mtx.y <= get_width(mygame->mapchar))
		{
			stringtoarray(mygame);
			//printf("%d \t",mygame->worldmap[mygame->mtx.x][mygame->mtx.y]);
		}
		mygame->n++;
		mygame->mtx.y = 0;
		mygame->mtx.x++;
	}
}*/
