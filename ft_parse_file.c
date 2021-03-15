/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 02:35:13 by irodrigo          #+#    #+#             */
/*   Updated: 2021/03/15 13:13:13 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

static int		ft_resolution(t_game_draw *mygame, char *line, int *pos)
{
	if (mygame->map_read == 1)
		return (ft_put_error(TIT_009, MSG1_019, -9));
	if (mygame->win.w != 0 || mygame->win.h != 0)
		return (ft_put_error(TIT_005, MSG1_006, -3));
	(*pos)++;
	mygame->win.w = ft_atoi_cub(line, pos);
	mygame->win.h = ft_atoi_cub(line, pos);
	if (mygame->win.w > MAXWIDTH)
		mygame->win.w = MAXWIDTH;
	if (mygame->win.h > MAXHEIGHT)
		mygame->win.h = MAXHEIGHT;
	ft_skip_spaces(line, pos);
	if (mygame->win.w <= 0 || mygame->win.h <= 0 || line[*pos] != '\0')
		return (ft_put_error(TIT_005, MSG1_007, -4));
	return (0);
}

static char		*getstr(char *temp)
{
	while (*temp != '.')
		temp++;
	return (temp);
}

static int		getcolor(unsigned int *color, char *line,
						int *pos, t_game_draw *mygame)
{
	int	r;
	int	g;
	int	b;

	if (mygame->map_read == 1)
		return (ft_put_error(TIT_009, MSG1_022, -1));
	if (*color != RGB_NONE)
		return (ft_put_error(TIT_007, MSG1_012, -1));
	(*pos)++;
	ft_skip_spaces(line, pos);
	r = ft_atoi_cub(line, pos);
	(*pos)++;
	ft_skip_spaces(line, pos);
	g = ft_atoi_cub(line, pos);
	(*pos)++;
	ft_skip_spaces(line, pos);
	b = ft_atoi_cub(line, pos);
	ft_skip_spaces(line, pos);
	if (line[*pos] != '\0' || r > 255 || g > 255 || b > 255)
		return (ft_put_error(TIT_007, MSG1_013, -1));
	*color = r * 256 * 256 + g * 256 + b;
	return (0);
}

static int		takeline(t_game_draw *mygame, char *temp, char *line)
{
	char *temp2;

	if (mygame->map_read != 1)
	{
		mygame->map_read = 1;
		if (ft_prerequisites(mygame) == -1)
			return (ft_put_error(TIT_008, MSG1_014, -1));
	}
	temp = ft_strjoin(line, "\n");
	temp2 = mygame->mapchar;
	mygame->mapchar = ft_strjoin(mygame->mapchar, temp);
	free(temp);
	temp = NULL;
	free(temp2);
	temp2 = NULL;
	return (0);
}

/*
**free(temp); // pendiente de probar posibles leaks
*/

int				get_info(t_game_draw *mygame, char *line)
{
	int		pos;

	pos = 0;
	ft_skip_spaces(line, &pos);
	if (line[0] == 'R' && line[1] == ' ')
		mygame->n_err = ft_resolution(mygame, line, &pos);
	else if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
		mygame->n_err = ft_chk_texture(mygame, line, "NO");
	else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
		mygame->n_err = ft_chk_texture(mygame, line, "SO");
	else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
		mygame->n_err = ft_chk_texture(mygame, line, "WE");
	else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
		mygame->n_err = ft_chk_texture(mygame, line, "EA");
	else if (line[0] == 'S' && line[1] == ' ')
		mygame->n_err = ft_chk_texture(mygame, line, "SP");
	else if (line[0] == 'F' && line[1] == ' ')
		mygame->n_err = getcolor(&mygame->stat_txt.floor, line, &pos, mygame);
	else if (line[0] == 'C' && line[1] == ' ')
		mygame->n_err = getcolor(&mygame->stat_txt.ceil, line, &pos, mygame);
	else if ((line[pos] == '1' || mygame->n_err == 1) && line[pos] != '\0')
		mygame->n_err = takeline(mygame, pos, line);     // revision desde aqui....
	//if (ft_skip_spaces(line, &pos) && mygame->n_err == 0 && line[pos] != '\0')
		/*return (error(-10));*/
	return (mygame->n_err < 0 ? -1 : 0);
}
