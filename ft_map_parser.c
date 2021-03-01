/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 11:14:45 by irodrigo          #+#    #+#             */
/*   Updated: 2021/02/27 21:06:53 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

int parsename (const char *text, const char *compare)
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


int		ft_check_gamer(t_game_draw *mygame)
{
	if (mygame->gamer.count == 0)
		return(ft_put_error(TIT_003, MSG1_015,-1));
	if (mygame->gamer.count > 1)
		return(ft_put_error(TIT_003, MSG1_016,-1));
	return (1);
}

int		ft_take_width(char **str, int pos)
{
	int col;
	int len;

	col = 0;
	len = 0;
	while(str[pos][col] != '\0')
	{
		len++;
		col++;
	}
	return (len);
}

/*
** in this function creates a dummy map that check if prime map is closed
*/

int ft_check_close(t_game_draw *mygame)
{
	char	**tmp;
	int		line;

	line = 0;
	tmp = NULL;
	if (!tmp)
		if (!(tmp= ft_calloc(mygame->map_dim.h, sizeof(char *))))
			return (ft_put_error(TIT_004, MSG1_017, -1));
	while (line < mygame->map_dim.h)
	{
		tmp[line] = ft_strdup(mygame->worldmap[line]);
		line++;
	}
	tmp[mygame->gamer.pos.y][mygame->gamer.pos.x] = '0';
	ft_checkborder(mygame->gamer.pos.y, mygame->gamer.pos.x, tmp, mygame);

	//ft_freearray(tmp);  // puede que esto falle algo  deja memoria ocuposa
	if (mygame->map_err == -1)
		ft_put_error(TIT_003, MSG1_018,-1);
	return (0);
}

int	ft_parse_map(t_game_draw *mygame)
{
	if (ft_check_gamer(mygame) == -1)
		return (-1);
	if (ft_check_close(mygame) == -1)
		return (-1);
	return (1);


	/*if (checkborder(mygame->gamer.pos.x, mygame->gamer.pos.y,
		dummymap, mygame->map_err))
		return (-1);*/

}


void	ft_checkborder(int x, int y, char **str, t_game_draw *err)
{
    if (err->map_err != -1)
	{
	if (x == 0 || y == 0 || y == ft_strlen(str[x]) || x == err->map_dim.h - 1
        || y >= ft_strlen(str[x + 1]) || y >= ft_strlen(str[x - 1]))
    {
        //ft_freearray(str);

		// debemos cambiar esto
		err->map_err = -1;
        //error(err->map_err);
        return ;
    }
    str[x][y] = '3';
    if (str[x][y + 1] == '0' || str[x][y + 1] == '2'|| str[x][y + 1] == '9')
        ft_checkborder(x, y + 1, str, err);
    if (str[x][y - 1] == '0' || str[x][y - 1] == '2'|| str[x][y - 1] == '9')
        ft_checkborder(x, y - 1, str, err);
    if (str[x + 1][y] == '0' || str[x + 1][y] == '2'|| str[x + 1][y] == '9')
        ft_checkborder(x + 1, y, str, err);
    if (str[x - 1][y] == '0' || str[x - 1][y] == '2'|| str[x - 1][y] == '9')
        ft_checkborder(x - 1, y, str, err);
	}
}

static void	getdirandpos(t_game_draw *mygame, int x, int y)
{
	mygame->idx_pos++;
	mygame->rc.posx = x + 0.5;
	mygame->rc.posy = y + 0.5;
	//mygame->gamer.x = x;
	//mygame->gamer.y = y;
	if (mygame->gamer.spr_dir == 'N')
	//if (mygame->p_dir == 'N')
	{
		mygame->rc.dirx = -1;
		mygame->rc.diry = 0;
		mygame->rc.planex = 0;
		mygame->rc.planey = 0.66;
	}
	if (mygame->gamer.spr_dir == 'S')
	//if (mygame->p_dir == 'S')
	{
		mygame->rc.dirx = 1;
		mygame->rc.diry = 0;
		mygame->rc.planex = 0;
		mygame->rc.planey = -0.66;
	}
	if (mygame->gamer.spr_dir == 'W')
	//if (mygame->p_dir == 'W')
	{
		mygame->rc.dirx = 0;
		mygame->rc.diry = -1;
		mygame->rc.planex = -0.66;
		mygame->rc.planey = 0;
	}
	if (mygame->gamer.spr_dir == 'E')
	//if (mygame->p_dir == 'E')
	{
		mygame->rc.dirx = 0;
		mygame->rc.diry = 1;
		mygame->rc.planex = 0.66;
		mygame->rc.planey = 0;
	}
}

static int	checkcontent(t_game_draw *mygame)
{
	int	i;
	int	j;

	i = 0;
	while (i < mygame->map_dim.h)
	{
		j = 0;
		while (j < mygame->map_dim.w/*screen.w*/ && !(mygame->worldmap[i][j]) == NULL)
		{
			mygame->worldmap[i][j] == '3' ? getdirandpos(mygame, i, j) : 0;
			mygame->worldmap[i][j] == '2' ? spritepos(mygame, i, j) : 0;
			if (((mygame->worldmap[i][j] == '0') || (mygame->worldmap[i][j] == '2')
			|| (mygame->worldmap[i][j] == '3'))
			&& ((mygame->worldmap[i - 1][j] == '9')
				|| (mygame->worldmap[i + 1][j] == '9') ||
				(mygame->worldmap[i][j - 1] == '9') ||
				(mygame->worldmap[i][j + 1] == '9')))
				return (-1);
			j++;
		}
		i++;
	}
	return (1);
}

static int checkimvalid_hwall(t_game_draw *mygame)
{
	int i;
	int j;
	int pos;
	int chkwall;

	i = 1;
	while (i < (mygame->map_dim.h/*screen.h*/ - 1))
	{
		chkwall = 1;
		pos = 1;
		j = ft_strlen(mygame->worldmap[i]) - 2;
		while (pos < j && chkwall == 1)
		{
			if (mygame->worldmap[i][pos] == '0' ||
				mygame->worldmap[i][pos] == '2' ||
				mygame->worldmap[i][pos] == '9')
				chkwall = 0;
			pos++;
		}
		if (chkwall	== 1)
			return (-1);
		i++;
	}
	return (0);
}

static int checkimvalid_vwall(t_game_draw *mygame)
{
	int i;
	int j;
	int pos;
	int chkwall;

	i = 1;
	while (i < (mygame->map_dim.w/*screen.w*/ - 1))
	{
		chkwall = 1;
		pos = 1;
		j = mygame->map_dim.h/*screen.h*/ - 1;
		while (pos < j && chkwall == 1)
		{
			if (mygame->worldmap[pos][i] == '0' ||
				mygame->worldmap[pos][i] == '2' ||
				mygame->worldmap[pos][i] == '9')
				chkwall = 0;
			pos++;
		}
		if (chkwall	== 1)
			return (-1);
		i++;
	}
	return (0);
}

//gamer inside map
static int	gamerpos(t_game_draw *mygame)
{
	int i;
	int j;

	i = 0;  // fila 1
	while (mygame->worldmap[0][i])
	{
		if (mygame->worldmap[0][i] == '3')
			return (-1);
		i++;
	}
	i = 0;  // ultima fila
	while(mygame->worldmap[mygame->map_dim.h/*screen.h*/ - 1][i])
	{
		if (mygame->worldmap[mygame->map_dim.h/*screen.h*/ - 1][i] == '3')
			return (-1);
		i++;
	}
	i = 0;  // primera y ultima columna
	while (i < mygame->map_dim.h/*screen.h*/ )
	{
		if (mygame->worldmap[i][0] == '3')
			return (-1);
		j = ft_strlen(mygame->worldmap[i]) - 1;
		if (mygame->worldmap[i][j] == '3')
			return (-1);
		i++;
	}
	return (0);
}

int			checkmap(t_game_draw *mygame)
{
	char **tmp;
	int i;
	int j;
	int pos;

	// hay que hacer aqui la asignacion de memoria de
	// la segunda estructura, cambiar la primera y
	// comprobar el resto para asignar cada elemento y
	// hacer la structura temporal.
	if (!(tmp =(char**)malloc(sizeof(char *) *  //ojo, es un char
			mygame->map_dim.h + 1)))
			return -1;
	i = 0;
	while (i < mygame->map_dim.h)
	{
		tmp[i] = ft_strdup(mygame->worldmap[i]);
		i++;
	}
	//chequea que los simbolos y jugador sean ok
	if (checkcontent(mygame) == -1)
		return (error(6));
	if (mygame->idx_pos > 1)
		return (error(5));
	if (mygame->idx_pos == 0)
		return (error(9));
	/*if (gamerpos(mygame) == -1)
		return (error(11));*/
	//chequeos de muros cerrados en el mapa
	/*if (checkimvalid_hwall(mygame) == -1)
		return (error(12));*/
/*	if (checkimvalid_vwall(mygame) == -1)
		return (error(13));*/
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
