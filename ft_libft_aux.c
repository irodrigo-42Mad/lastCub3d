/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_libft_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 10:41:14 by irodrigo          #+#    #+#             */
/*   Updated: 2021/03/13 23:42:57 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

char	*ft_extract_text(char *line, char c)
{
	while (*line != c)
		line++;
	return (line);
}

int		ft_get_sign(char ch)
{
	if (ch == '-' || ch == '+')
	{
		if (ch == '-')
			return (-1);
	}
	return (1);
}

int		ft_atoi_color(char *line, int *i)
{
	int n;
	int val;
	int pos;
	int sign;

	n = 0;
	ft_skip_spaces(line, i);
	sign = ft_get_sign(line[*i]);
	if (line[*i] == '-')
		(*i)++;
	pos = *i;
	while (ft_isdigit(line[pos]))
	{
		val = (line[pos] - 48);
		n = n * 10 + val;
		pos++;
	}
	*i = pos;
	return (n * sign);
}

int		ft_isspace(char ch)
{
	return ((ch == ' ' || ch == '\t' || ch == '\n' ||
		ch == '\r' || ch == '\v' || ch == '\f') ? 1 : 0);
}

int		ft_skip_spaces(char *line, int *i)
{
	while (ft_isspace(line[*i]))
		(*i)++;
	return (1);
}
