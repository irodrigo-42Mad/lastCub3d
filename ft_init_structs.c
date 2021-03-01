/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_structs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 09:44:20 by irodrigo          #+#    #+#             */
/*   Updated: 2021/02/27 18:50:20 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void	ft_pre_var(t_game_draw *mygame)
{
	mygame->win.w = 0;
	mygame->win.h = 0;
	mygame->screenshot = 0;
	mygame->stat_txt.ceil = RGB_NONE;
	mygame->stat_txt.floor = RGB_NONE;
}

void 	ft_init_rc(t_game_draw *mygame)
{
	mygame->rc.posx = mygame->gamer.pos.x;
	mygame->rc.posy = mygame->gamer.pos.y;
	mygame->rc.dirx = -1;
	mygame->rc.diry = 0;
	mygame->rc.planex = 0;
	mygame->rc.planey = -((double)mygame->win.w / (double)mygame->win.h) / 2.0;
	mygame->canvas = NULL;
	mygame->canvas_ptr = NULL;
	mygame->tx.id = 0;
	mygame->rc.movespeed = 0.13;
	mygame->rc.rotspeed = 0.09;
}

void	read_map(t_game_draw *mygame)
{
	mygame->map_dim.h = get_height(mygame->mapchar);
	mygame->map_dim.w = get_width(mygame->mapchar);
	ft_changetab(mygame);
	ft_create_matrix(mygame);
}

int	read_file(int argc, char *pathname, t_game_draw *mygame)
{
	int		fd;
	char	*line;
	int		ret;

	ret = 1;
	fd = ft_chk_read(pathname);
	if (fd < 0)
	{
		if (fd == -1)
			ft_write_error(TIT_003, MSG1_003);
		if (fd == -2)
			ft_write_error(TIT_003, MSG1_004);
		return(0);
	}
	mygame->mapchar = ft_strdup("");
	while (ret == 1)
	{
		ret = get_next_line(fd, &line);
		if (get_info(mygame, line) == -1)
			ret = -1;
		free(line);
	}
	close(fd);
	if(line != NULL)
		line = NULL;
	if (argc == 3 && ret != -1)
		mygame->screenshot = 1;
	return (ret);
}


/*
**	wall_texture(mygame);
*/

int		ft_charge_txt(t_game_draw *mygame, int elm, char *path)
{
	mygame->tx.wlone[elm] = mlx_xpm_file_to_image(mygame->mlx_ptr, path,
		&mygame->tx.width[elm], &mygame->tx.height[elm]);
	if (mygame->tx.wlone[elm] == NULL || mygame->tx.width[elm] != 64
		|| mygame->tx.height[elm] != 64)
		return (-1); // error al leer la textura
	mygame->tx.wdata[elm] = mlx_get_data_addr(mygame->tx.wlone[elm],
		&mygame->tx.wbpp[elm], &mygame->tx.wsl[elm], &mygame->tx.wendian[elm]);
	return (0);
}

int		ft_load_txt(t_game_draw *mygame)
{
	int i;
	int status;

	i = 0;
	while (i < 5 && status == 0)
	{
		if (i == 0)
			status = ft_charge_txt(mygame, i, mygame->stat_txt.path_no);
		if (i == 1)
			status = ft_charge_txt(mygame, i, mygame->stat_txt.path_so);
		if (i == 2)
			status = ft_charge_txt(mygame, i, mygame->stat_txt.path_ea);
		if (i == 3)
			status = ft_charge_txt(mygame, i, mygame->stat_txt.path_we);
		if (i == 4)
			status = ft_charge_txt(mygame, i, mygame->stat_txt.path_spr);
		i++;
	}
	if(status < 0)
		return (-1);
	else
		return (0);
}

/*
** function that inits game behaviour
*/
void	ft_init_game(t_game_draw *mygame)
{
	mygame->mlx_ptr = mlx_init();
	ft_init_rc(mygame);
	if (ft_load_txt(mygame) == 0)
	{
	// debemos de cargar las estructuras varias
	/*if (ft_init_textures(mygame) == -1)
		ft_write_error("Error al cargar texturas", "compruebe la memoria");
		return;*/
		// error al iniciar la textura, salir


	mygame->mlx_win = mlx_new_window(mygame->mlx_ptr, mygame->win.w,
		mygame->win.h, "cub3D");
	mlx_hook(mygame->mlx_win, 2, 1L << 0, nopulsed, mygame);
	mlx_hook(mygame->mlx_win, 3, 1L << 1, pulsed, mygame);
	mlx_hook(mygame->mlx_win, 17, 1L << 17, ft_close, mygame);
	mlx_loop_hook(mygame->mlx_ptr, deal_key, mygame);
	mlx_loop(mygame->mlx_ptr);
	}
	else
	{
		//clean data structures
	}
}
