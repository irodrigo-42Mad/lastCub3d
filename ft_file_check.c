/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 16:27:52 by irodrigo          #+#    #+#             */
/*   Updated: 2021/01/13 18:59:35 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

int			ft_chk_read(char *fname)
{
	int fd;
	int errno;

	fd = open(fname, O_RDONLY);
	if (fd < 0)
		return (errno == ENOENT) ? -1 : -2;
	return (fd);
}

void 		prepare_line(char *line)
{
	int i;
	int c;
	int auxp;
	char *aux;

	aux = (char *) malloc(ft_strlen(line) * 5);
	i = 0;
	auxp = 0;
	while(line[i] != '\0')
	{
		if(line[i] == '\t')
		{
			c = 0;
			while (c < 3)
			{
				aux[auxp] = ' ';
				auxp++;
				c++;
			}
		}
		else
		{
			aux[auxp] = line[i];
		}
		i++;
		auxp++;
	}
	aux[auxp] = '\0';
	strlcpy(line,aux,auxp);
}
