/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 02:23:23 by irodrigo          #+#    #+#             */
/*   Updated: 2021/02/27 16:32:57 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

/*
void	more_texture(t_game_draw *mygame)
{
	mygame->wlone[5] = mlx_xpm_file_to_image(mygame->mlx_ptr,
		"./textures/pistol.xpm", &mygame->width[5], &mygame->height[5]);
	mygame->wdata[5] = mlx_get_data_addr(mygame->wlone[5],
		&mygame->wbpp[5], &mygame->wsl[5], &mygame->wendian[5]);
	/*mygame->wlone[7] = mlx_xpm_file_to_image(mygame->mlx_ptr,
		mygame->s, &mygame->width[7], &mygame->height[7]);
	mygame->wdata[7] = mlx_get_data_addr(mygame->wlone[7],
		&mygame->wbpp[7], &mygame->wsl[7], &mygame->wendian[7]);
	free(mygame->we);
	free(mygame->so);
	free(mygame->ea);
	free(mygame->no);
	free(mygame->s);
}
*/

/*int		wall_texture(t_game_draw *mygame, char *path, unsigned int **elmt, int elm)
{
	int		fd;
	void	*img;
	int		tab[5];

	if ((fd = open(path, O_RDONLY)) == -1)
		return (-1);
	close(fd);
	mygame->wlone[elm] = mlx_xpm_file_to_image(mygame->mlx_ptr, path,
					&mygame->width[elm], &mygame->height[elm]);*/
	//if (mygame->wlone[elm] == NULL /*|| tab[0] != 64 || tab[1] != 64*/) // revisar
	/*	return (-1);
	mygame->wdata[elm] = mlx_get_data_addr(mygame->wlone[elm],
		&mygame->wbpp[elm], &mygame->wsl[elm], &mygame->wendian[elm]);



	img = mlx_xpm_file_to_image(mygame->mlx_ptr, path, &tab[0], &tab[1]);
	if (img == NULL || tab[0] != 64 || tab[1] != 64)
		return (-1);

	*elmt = (unsigned int *)mlx_get_data_addr(img, &tab[2], &tab[3], &tab[4]);
	free(img);
	return (0);
}*/



	/*mygame->wlone[0] = mlx_xpm_file_to_image(mygame->mlx_ptr, mygame->we,
					&mygame->width[0], &mygame->height[0]);
	mygame->wdata[0] = mlx_get_data_addr(mygame->wlone[0],
		&mygame->wbpp[0], &mygame->wsl[0], &mygame->wendian[0]);

	mygame->wlone[2] = mlx_xpm_file_to_image(mygame->mlx_ptr, mygame->so,
					&mygame->width[2], &mygame->height[2]);
	mygame->wdata[2] = mlx_get_data_addr(mygame->wlone[2],
		&mygame->wbpp[2], &mygame->wsl[2], &mygame->wendian[2]);
	mygame->wlone[3] = mlx_xpm_file_to_image(mygame->mlx_ptr, mygame->no,
					&mygame->width[3], &mygame->height[3]);
	mygame->wdata[3] = mlx_get_data_addr(mygame->wlone[3],
		&mygame->wbpp[3], &mygame->wsl[3], &mygame->wendian[3]);
	mygame->wlone[4] = mlx_xpm_file_to_image(mygame->mlx_ptr, mygame->ea,
					&mygame->width[4], &mygame->height[4]);
	mygame->wdata[4] = mlx_get_data_addr(mygame->wlone[4],
		&mygame->wbpp[4], &mygame->wsl[4], &mygame->wendian[4]);
	more_texture(mygame);
	write(1,"ok",1);
}*/

int		pulsed(int key, t_game_draw *mygame)
{
	if (key == KEY_W)
		mygame->key.w_status = 0;
	if (key == KEY_S)
		mygame->key.s_status = 0;
	if (key == KEY_A)
		mygame->key.a_status = 0;
	if (key == KEY_D)
		mygame->key.d_status = 0;
	if (key == KEY_UP)
		mygame->key.up_status = 0;
	if (key == KEY_LEFT)
		mygame->key.lf_status = 0;
	if (key == KEY_RIGHT)
		mygame->key.rg_status = 0;
	if (key == KEY_DOWN)
		mygame->key.dw_status = 0;
	if (key == KEY_ESC)
		mygame->key.esc_status = 0;
	if (key == KEY_SHIFT)
		mygame->rc.movespeed = 0.12;
	return (0);
}

int		nopulsed(int key, t_game_draw *mygame)
{
	if (key == KEY_W)
		mygame->key.w_status = 1;
	if (key == KEY_S)
		mygame->key.s_status = 1;
	if (key == KEY_A)
		mygame->key.a_status = 1;
	if (key == KEY_D)
		mygame->key.d_status = 1;
	if (key == KEY_UP)
		mygame->key.up_status = 1;
	if (key == KEY_LEFT)
		mygame->key.lf_status = 1;
	if (key == KEY_RIGHT)
		mygame->key.rg_status = 1;
	if (key == KEY_DOWN)
		mygame->key.dw_status = 1;
	if (key == KEY_ESC)
		mygame->key.esc_status = 1;
	if (key == KEY_SHIFT)
		mygame->rc.movespeed = 0.35;
	return (0);
}


// toesto es nuevo

int		main(int argc, char **argv)
{
	t_game_draw	*mygame;
	int status;
	int count;

	if (argc == 2 || argc == 3)
	{
		if (parsename(argv[0], "cub3D") == -1)
			return (ft_put_error(TIT_001, MSG1_001, 1));
		if (argc == 3)
			if (parsename(argv[2], "--save") == -1)
				return (ft_put_error(TIT_002, MSG1_002, 2));
		if (parsename(argv[1], "cub") == -1)
			return (ft_put_error(TIT_002, MSG1_002, 3));
		if (!(mygame = malloc(sizeof(t_game_draw))))
			return (ft_put_error(TIT_004, MSG1_005, 4));
		ft_pre_var(mygame);
		status = read_file(argc, argv[1], mygame);
		read_map(mygame);
		// una vez leido el mapa se puede limpiar del todo el auxiliar
		// aqui tengo que limpiar el auxiliar del mapa

		// por aqui ando corrigiendo ahora
		if (ft_parse_map(mygame) == 1) // tengo que comenzar a ver si el mapa es válido
		// parse_map tiene un fallo y no libera bien el temporal, revisar
		{
			ft_init_game(mygame);
		}
		// debes liberar las rutas de las texturas  // NEW




		// Lectura del mapa sin leaks guarda posicion
		system ("leaks cub3D");


		// separar el mapa en lineas
		// cambiar los \t por 4 ochos
		// comprobar que solamente hay caracteres validos en el mapa
		// contar los sprites
		// guardar la posicion del jugador
		// comprobar que el mapa es válido



		//hay que limpiar del todo la estructura mapchar
		//ya que en caso contrario, produce leaks
		if(mygame->mapchar != NULL);
		{
			ft_clean_arr(mygame->mapchar);
			free(mygame->mapchar);
			mygame->mapchar = NULL;
		}
		if(mygame->sprite != NULL)
		{
			free(mygame->sprite);
			mygame->sprite = NULL;
		}



		system ("leaks cub3D");
		// necesario para limpiar el mapa
		int act_pos;
		act_pos == mygame->map_dim.h - 1;
		if (mygame->worldmap != NULL)
			while(act_pos >= 0)
			{
				ft_clean_arr(mygame->worldmap[act_pos]);
				free(mygame->worldmap[act_pos]);
				mygame->worldmap[act_pos] == NULL;
				act_pos--;
			}
		free(mygame->worldmap);
		mygame->worldmap = NULL;

		free(mygame);
		mygame = NULL;

		// probando los leaks hasta aqui.....

	}

			//return (error(0));
/*
		// hasta aqui los nombres del programa se comparan correctamente
		if (!(mygame = malloc(sizeof(t_game_draw))))
			return (error(3));



		initvar(mygame);
		mygame->mlx_ptr = mlx_init();
		read_file(argc, argv, mygame); //revisar el error y salir
		read_map(mygame);
		if (checkmap(mygame) == -1)
		{
			return (error(1));
			exit(0);
		}
		free(mygame->mapchar);
		openall(mygame);
		return (0);
	}
	return (error(2));*/

}
