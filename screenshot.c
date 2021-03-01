

#include "./cub3d.h"

int		doscreenshot(t_map *tab)
{
	int file;
	int filesize;
	int	pad;

	pad = (4 - ((int)tab->winx * 3) % 4) % 4;
	filesize = 60 + (3 * ((int)tab->winx + pad) * (int)tab->winy);
	remove("screenshot.bmp");
	if ((file = open("screenshot.bmp", O_WRONLY | O_CREAT
		| O_TRUNC | O_APPEND, 777)) < 0)
		return (0);
	if (!write_bmp_header(file, filesize, tab))
		return (0);
	if (!write_bmp_data(file, tab, pad))
		return (0);
	close(file);
	return (1);
}

void	to_img(t_map *tab)
{
	mlx_put_image_to_window(tab->mlx_ptr, tab->win_ptr, tab->img, 0, 0);
	if (tab->screenshot == 1)
	{
		doscreenshot(tab);
		exit(1);
	}
	mlx_destroy_image(tab->mlx_ptr, tab->img);
}

void	set_int_in_char(unsigned char *start, int value)
{
	start[0] = (unsigned char)(value);
	start[1] = (unsigned char)(value >> 8);
	start[2] = (unsigned char)(value >> 16);
	start[3] = (unsigned char)(value >> 24);
}

int		get_color(t_map *tab, int x, int y)
{
	int	rgb;
	int	color;

	color = *(int*)(tab->img_ptr
			+ (4 * (int)tab->winx * ((int)tab->winy - 1 - y))
			+ (4 * x));
	rgb = (color & 0xFF0000) | (color & 0x00FF00) | (color & 0x0000FF);
	return (rgb);
}

int		write_bmp_header(int fd, int filesize, t_map *tab)
{
	int				i;
	unsigned char	bmpfileheader[60];

	i = 0;
	while (i < 60)
		bmpfileheader[i++] = (unsigned char)(0);
	bmpfileheader[0] = (unsigned char)('B');
	bmpfileheader[1] = (unsigned char)('M');
	set_int_in_char(bmpfileheader + 2, filesize);
	bmpfileheader[10] = (unsigned char)(60);
	bmpfileheader[14] = (unsigned char)(40);
	set_int_in_char(bmpfileheader + 18, tab->winx);
	set_int_in_char(bmpfileheader + 22, tab->winy);
	bmpfileheader[27] = (unsigned char)(1);
	bmpfileheader[28] = (unsigned char)(24);
	return (!(write(fd, bmpfileheader, 60) < 0));
}                                                  //revisar

int		write_bmp_data(int file, t_map *tab, int pad)
{
	const unsigned char	zero[3] = {0, 0, 0};
	int					i;
	int					j;
	int					color;

	i = 0;
	while (i < (int)tab->winy)
	{
		j = 0;
		while (j < (int)tab->winx)
		{
			color = get_color(tab, j, i);
			if (write(file, &color, 3) < 0)
				return (0);
			if (pad > 0 && write(file, &zero, pad) < 0)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
