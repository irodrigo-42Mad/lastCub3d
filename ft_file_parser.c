/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 16:28:12 by irodrigo          #+#    #+#             */
/*   Updated: 2021/03/02 10:11:59 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_chk_texture(t_game_draw *mygame, char *line, char *elmt)
{
	int		status;
	char	*path;
	int		len;
	int		pos;

	pos = 0;
	status = 0;
	while (!ft_isspace(line[pos]) == 1)
		pos++;
	ft_skip_spaces(line, &pos);
	len = ft_strlen(line) - pos;
	path = ft_substr(line, pos, len);
	if (parsename(path, "xpm") != -1)
	{
		status = ft_chk_read(path);
		if (status > 0)
			ft_set_txt_path(path, elmt, mygame);
		free(path);
		path = NULL;
		return (ft_checkfilestatus(status, elmt, mygame));
	}
	free(path);
	path = NULL;
	return (ft_put_error(TIT_006, MSG1_011, -1));
}

int		ft_checkfilestatus(int status, char *elmt, t_game_draw *mygame)
{
	if (status > 0)
	{
		close(status);
		if (elmt[0] == 'N' && elmt[1] == 'O' && mygame->stat_txt.north == 0)
			mygame->stat_txt.north = 1;
		else if (elmt[0] == 'S' && elmt[1] == 'O'
			&& mygame->stat_txt.south == 0)
			mygame->stat_txt.south = 1;
		else if (elmt[0] == 'E' && elmt[1] == 'A' && mygame->stat_txt.east == 0)
			mygame->stat_txt.east = 1;
		else if (elmt[0] == 'W' && elmt[1] == 'E' && mygame->stat_txt.west == 0)
			mygame->stat_txt.west = 1;
		else if (elmt[0] == 'S' && elmt[1] == 'P'
			&& mygame->stat_txt.sprite == 0)
			mygame->stat_txt.sprite = 1;
		else
			return (ft_put_error(TIT_006, MSG1_008, -1));
		return (0);
	}
	if (status == -1)
		return (ft_put_error(TIT_006, MSG1_009, -1));
	else if (status == -2)
		return (ft_put_error(TIT_006, MSG1_010, -1));
}

void	ft_set_txt_path(char *path, char *elmt, t_game_draw *mygame)
{
	if (elmt[0] == 'N' && elmt[1] == 'O' && mygame->stat_txt.north == 0)
		mygame->stat_txt.path_no = ft_strdup(path);
	else if (elmt[0] == 'S' && elmt[1] == 'O' && mygame->stat_txt.south == 0)
		mygame->stat_txt.path_so = ft_strdup(path);
	else if (elmt[0] == 'E' && elmt[1] == 'A' && mygame->stat_txt.east == 0)
		mygame->stat_txt.path_ea = ft_strdup(path);
	else if (elmt[0] == 'W' && elmt[1] == 'E' && mygame->stat_txt.west == 0)
		mygame->stat_txt.path_we = ft_strdup(path);
	else if (elmt[0] == 'S' && elmt[1] == 'P' && mygame->stat_txt.sprite == 0)
		mygame->stat_txt.path_spr = ft_strdup(path);
}
