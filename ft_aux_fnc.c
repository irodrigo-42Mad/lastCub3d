#include "cub3d.h"

int		ft_atoi_cub(char *line, int *pos)
{
	int	num;

	num = 0;
	ft_skip_spaces(line, pos);
	while (line[*pos] >= '0' && line[*pos] <= '9')
	{
		num = num * 10 + (line[*pos] - 48);
		(*pos)++;
	}
	return (num);
}

void		ft_freemap(t_game_draw *mygame)
{
	int		pos;

	pos = -1;
	while (mygame->worldmap[++pos] != NULL)
	{
		free(mygame->worldmap[pos]);
		mygame->worldmap[pos] = NULL;
	}
	free(mygame->worldmap);
	mygame->worldmap = NULL;
}

void		ft_fretable(char **fra)
{
	int		pos;

	pos = -1;
	while (fra[++pos] != NULL)
	{
		free(fra[pos]);
		fra[pos] = NULL;
	}
	free(fra[pos]);
	fra[pos] = NULL;
	free(fra);
	fra = NULL;
}

	//while (map->mapa[x] != NULL)
		//map->mapa);
	//map->mapa = NULL;

		//free(map->mapa[x]);
		//map->mapa[x] = NULL;
		//x++;



