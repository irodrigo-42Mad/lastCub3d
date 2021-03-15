/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 11:14:45 by irodrigo          #+#    #+#             */
/*   Updated: 2021/03/13 22:19:12 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

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

int			ft_take_width(char **str, int pos)
{
	int col;
	int len;

	col = 0;
	len = 0;
	while (str[pos][col] != '\0')
	{
		len++;
		col++;
	}
	return (len);
}

/*
** in this function creates a dummy map that check if prime map is closed
*/

int			ft_check_close(t_game_draw *mygame)
{
	char	**tmp;
	int		line;

	line = 0;
	tmp = NULL;
	if (!tmp)
		if (!(tmp = ft_calloc(mygame->map_dim.h, sizeof(char *))))
			return (ft_put_error(TIT_004, MSG1_017, -1));
	while (line < mygame->map_dim.h)
	{
		tmp[line] = ft_strdup(mygame->worldmap[line]);
		line++;
	}
	tmp[mygame->gamer.pos.y][mygame->gamer.pos.x] = '0';
	ft_checkborder(mygame->gamer.pos.y, mygame->gamer.pos.x, tmp, mygame);
	//al terminar el chequeo de borde limpiar el array revisar lectura,
	//si se produce fallo al leer el mapa no hay que hacer todo esto.
	//ft_freearray(tmp);  // puede que esto falle algo  deja memoria ocuposa
	if (mygame->map_err == -1)
		ft_put_error(TIT_003, MSG1_018, -1);
	return (0);
}

int			ft_parse_map(t_game_draw *mygame)
{
	if (ft_check_gamer(mygame) == -1)
		return (-1);
	if (ft_check_close(mygame) == -1)
		return (-1);
	if (ft_check_content(mygame) == -1)
		return (-1);
	return (1);
}

/*
**if (checkborder(mygame->gamer.pos.x, mygame->gamer.pos.y,
**	dummymap, mygame->map_err))
**	return (-1);
*/

void		ft_checkborder(int x, int y, char **str, t_game_draw *err)
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
		if (str[x][y + 1] == '0' || str[x][y + 1] == '2'
			|| str[x][y + 1] == '9')
			ft_checkborder(x, y + 1, str, err);
		if (str[x][y - 1] == '0' || str[x][y - 1] == '2'
			|| str[x][y - 1] == '9')
			ft_checkborder(x, y - 1, str, err);
		if (str[x + 1][y] == '0' || str[x + 1][y] == '2'
			|| str[x + 1][y] == '9')
			ft_checkborder(x + 1, y, str, err);
		if (str[x - 1][y] == '0' || str[x - 1][y] == '2'
			|| str[x - 1][y] == '9')
			ft_checkborder(x - 1, y, str, err);
	}
}

static void	getdirandpos(t_game_draw *mygame, int x, int y)
{
	mygame->idx_pos++;
	mygame->rc.posx = x + 0.5;
	mygame->rc.posy = y + 0.5;
	if (mygame->gamer.spr_dir == 'N')
	{
		mygame->rc.dirx = -1;
		mygame->rc.planey = 0.66;
	}
	if (mygame->gamer.spr_dir == 'S')
	{
		mygame->rc.dirx = 1;
		mygame->rc.planey = -0.66;
	}
	if (mygame->gamer.spr_dir == 'W')
	{
		mygame->rc.diry = -1;
		mygame->rc.planex = -0.66;
	}
	if (mygame->gamer.spr_dir == 'E')
	{
		mygame->rc.diry = 1;
		mygame->rc.planex = 0.66;
	}
	mygame->dirok = 1;
}

int			ft_check_content(t_game_draw *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map_dim.h)
	{
		j = 0;
		while (j < game->map_dim.w && !((game->worldmap[i][j]) == NULL))
		{
			if (game->dirok == 0 && game->worldmap[i][j] == '3')
			{
				getdirandpos(game, i, j);
				game->worldmap[i][j] = '0';
			}
			if (game->worldmap[i][j] == '2')
				spritepos(game, i, j);
			if (((game->worldmap[i][j] == '0') || (game->worldmap[i][j] == '2')
			|| (game->worldmap[i][j] == '3'))  && ((game->worldmap[i - 1][j]
			== '9') || (game->worldmap[i + 1][j] == '9') ||
			(game->worldmap[i][j - 1] == '9') || (game->worldmap[i][j + 1]
			== '9')))
				return (-1);
			j++;
		}
		i++;
	}
	return (1);
}

int			checkmap(t_game_draw *mygame)
{
	char **tmp;
	int i;

	// hay que hacer aqui la asignacion de memoria de
	// la segunda estructura, cambiar la primera y
	// comprobar el resto para asignar cada elemento y
	// hacer la structura temporal.
	if (!(tmp = (char**)malloc(sizeof(char *) *  //ojo, es un char
			mygame->map_dim.h + 1)))
			return (-1);
	i = 0;
	while (i < mygame->map_dim.h)
	{
		tmp[i] = ft_strdup(mygame->worldmap[i]);
		i++;
	}
	//chequea que los simbolos y jugador sean ok
	if (ft_check_content(mygame) == -1)
		return (ft_put_error(TIT_003, MSG1_018, -1));
	if (mygame->idx_pos > 1)
		return (ft_put_error(TIT_003, MSG1_016, -1));
	if (mygame->idx_pos == 0)
		return (ft_put_error(TIT_003, MSG1_015, -1));

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
