/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 20:34:24 by irodrigo          #+#    #+#             */
/*   Updated: 2020/10/11 12:23:54 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

static int		ft_new_line(char **line, char **read_line)
{
	int		len;
	char	*data;

	len = 0;
	while ((*read_line)[len] != L_EOF && (*read_line)[len] != '\0')
		len++;
	if ((*read_line)[len] == L_EOF)
	{
		*line = ft_substr(*read_line, 0, len);
		data = ft_strdup(&(*read_line)[len + 1]);
		free(*read_line);
		*read_line = data;
	}
	else if ((*read_line)[len] == '\0')
	{
		*line = ft_strdup(*read_line);
		ft_memfree(read_line);
		return (0);
	}
	return (1);
}

static int		ft_check_line(int fd, int ret, char **line, char **read_line)
{
	if (ret < 0)
		return (-1);
	else if (ret == 0 && !read_line[fd])
	{
		*line = ft_strdup("");
		ft_memfree(read_line);
		return (0);
	}
	else
		return (ft_new_line(line, &read_line[fd]));
}

/*
**FUNCION: get_next_line    Obtendrá una linea de texto de uno o varios fd
**
**	IN params
**		int	fd: 	recibirá el descriptor del fichero a leer
**		char		**line:	matriz de líneas de un fichero
**
**	OUT params
**		int:		Devolverá el estado de la lectura de un fichero
**
**	function Variables
**		int		res:    	read function returns
**		char 	tmp_buff[]	guarda los elementos leidos del fichero
**		char     *s_buff     buffer temporal de lectura hasta llenado
**		st char  *sc_file    guarda los contenidos de los descriptors
**
**	Function trace
**
**	The get_next_line function reads a file and returns the line ending
**	with a newline character from a file descriptor. A static variable is
**	used, to use the value of the previous function call.
**
**	When get_next_line is first called, checks if the static variable is
**	is empty. In this case, we allocate memory for it using our tmp_buff var
**	In the loop, we will continue to read more of the line and join them
**	together in a temporaty string. Then, this string will replace stored
**	data keeping track about how much is read and delete previous stored
**	data.
**
**	This is needed because we are only reading so many  n-bytes at a time
**	decided by our BUFF_SIZE. If we read at each iteration without freeing
**	memory, then we would have memory leaks.
**
**	The loop breaks when a newline is encountered. Finally, we call output
**	the result of unction to check what should be returned.
*/

int				get_next_line(int fd, char **line)
{
	int			res;
	char		tmp_buff[BUFFER_SIZE + 1];
	char		*s_buffer;
	static char *sc_file[FILE_DSC];

	if (fd < 0 || !line || BUFFER_SIZE <= 0 || read(fd, tmp_buff, 0))
		return (-1);
	while ((res = read(fd, tmp_buff, BUFFER_SIZE)) > 0)
	{
		tmp_buff[res] = '\0';
		if (sc_file[fd] == NULL)
			sc_file[fd] = ft_strdup(tmp_buff);
		else
		{
			s_buffer = ft_strjoin(sc_file[fd], tmp_buff);
			free(sc_file[fd]);
			sc_file[fd] = s_buffer;
		}
		if (ft_strchr(sc_file[fd], L_EOF))
			break ;
	}
	return (ft_check_line(fd, res, line, sc_file));
}

void			ft_memfree(char **str_line)
{
	if (str_line != NULL && *str_line != NULL)
	{
		free(*str_line);
		*str_line = NULL;
	}
}
