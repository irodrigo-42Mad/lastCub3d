/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 02:23:23 by irodrigo          #+#    #+#             */
/*   Updated: 2021/03/10 11:24:54 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

int		pulsed(int key, t_game_draw *mygame)
{
	if (key == KEY_W)
		mygame->key.w_status = 1;
	if (key == KEY_S)
		mygame->key.s_status = 1;
	if (key == KEY_A)
		mygame->key.a_status = 1;
	if (key == KEY_D)
		mygame->key.d_status = 1;
	if (key == KEY_LEFT)
		mygame->key.lf_status = 1;
	if (key == KEY_RIGHT)
		mygame->key.rg_status = 1;
	if (key == KEY_DOWN)
		mygame->key.dw_status = 1;
	if (key == KEY_ESC)
		mygame->key.esc_status = 1;
	if (key == KEY_SHIFT)
		mygame->rc.movespeed = 0.12;
	return (0);
}

int		nopulsed(int key, t_game_draw *mygame)
{
	if (key == KEY_W)
		mygame->key.w_status = 0;
	if (key == KEY_S)
		mygame->key.s_status = 0;
	if (key == KEY_A)
		mygame->key.a_status = 0;
	if (key == KEY_D)
		mygame->key.d_status = 0;
	if (key == KEY_LEFT)
		mygame->key.lf_status = 0;
	if (key == KEY_RIGHT)
		mygame->key.rg_status = 0;
	if (key == KEY_DOWN)
		mygame->key.dw_status = 0;
	if (key == KEY_ESC)
		mygame->key.esc_status = 0;
	if (key == KEY_SHIFT)
		mygame->rc.movespeed = 0.35;
	return (0);
}

int		main(int argc, char **argv)
{
	t_game_draw	*mygame;

	if (argc == 2 || argc == 3)
	{
		if (parsename(argv[0], "cub3D") == -1)
			return (ft_put_error(TIT_001, MSG1_001, 1));
		if (parsename(argv[1], ".cub") == -1)
			return (ft_put_error(TIT_002, MSG1_002, 3));
		if (argc == 3)
			if (parsename(argv[2], "--save") == -1)
				return (ft_put_error(TIT_002, MSG1_002, 2));
		if (!(mygame = malloc(sizeof(t_game_draw))))
			return (ft_put_error(TIT_004, MSG1_005, 4));
		ft_pre_var(mygame);
		if (read_file(argc, argv[1], mygame) != 0)
			return (-1); // problema al cargar los datos
		if (read_map(mygame) != -1)
		{
			if (ft_parse_map(mygame) == 1)
			// parse_map tiene un fallo y no libera bien el temporal, revisar
			{
				ft_init_game(mygame);
			}
		}
		//ft_clean_aux(mygame);
		// una vez leido el mapa se puede limpiar del todo el auxiliar
		// aqui tengo que limpiar el auxiliar del mapa
		// por aqui ando corrigiendo ahora
		// debes liberar las rutas de las texturas  // NEW
		// Lectura del mapa sin leaks guarda posicion
		system("leaks cub3D");

		//hay que limpiar del todo la estructura mapchar
		//ya que en caso contrario, produce leaks
		if (mygame->mapchar != NULL)
		{
			ft_clean_arr(mygame->mapchar);
			free(mygame->mapchar);
			mygame->mapchar = NULL;
		}
		if (mygame->sprite != NULL)
		{
			free(mygame->sprite);
			mygame->sprite = NULL;
		}

		system("leaks cub3D");
		// necesario para limpiar el mapa
		int act_pos;
		act_pos = mygame->map_dim.h - 1;
		if (mygame->worldmap != NULL)
			while (act_pos >= 0)
			{
				ft_clean_arr(mygame->worldmap[act_pos]);
				free(mygame->worldmap[act_pos]);
				mygame->worldmap[act_pos] = NULL;
				act_pos--;
			}
		free(mygame->worldmap);
		mygame->worldmap = NULL;
		free(mygame);
		mygame = NULL;
	}
	else
		return (ft_put_error(TIT_002, MSG1_002, 2));
}
