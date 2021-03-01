/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_libft_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <irodrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 10:41:14 by irodrigo          #+#    #+#             */
/*   Updated: 2021/01/27 14:33:13 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

// funcion con leaks
char	*ft_right(const char *mystr, int len)  //revisar los leaks
{
	size_t	pos_fin;
	size_t	pos_ini;
	int		act_char;
	char	*result;

	if (*mystr == '\0')
		return (0);
	pos_fin = ft_strlen(mystr);
	pos_ini = pos_fin - len;
	act_char = 0;
	result = ft_calloc(len, sizeof(char));
	while (act_char < len)
	{
		result[act_char] = mystr[pos_ini + act_char];
		act_char++;
	}
	return (result);
}
// hay que revisar el por qué

char	*ft_extract_text(char *line, char c)
{
	while (*line != c)
		line++;
	return (line);
}

void	ft_swap_int(int *a, int *b)
{
	int		iaux;

	iaux = *a;
	*a = *b;
	*b = iaux;
}

void	ft_swap_float(double *a, double *b)
{
	double faux;

	faux = *a;
	*a = *b;
	*b = faux;
}


int		ft_get_sign(char ch)
{
	return (ch == '-' || ch == '+') ?
	       1 :((ch == '-') ? -1 : 1);
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
	while(ft_isspace(line[*i]))
		(*i)++;
	return (1);
}

void ft_freearray(char **str)
{
	int elm;

	elm = 0;
	if (str )
	{
		while (str[elm])
		{
			if (str[elm] != '\0')
				free(str[elm]);
			elm++;
		}
		free(str);
	}
}
