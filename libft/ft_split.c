/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 13:12:32 by irodrigo          #+#    #+#             */
/*   Updated: 2019/11/22 13:05:40 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_word_counter(char const *str, char c)
{
	int		word_len;
	size_t	counter;

	word_len = 0;
	counter = 0;
	while (*str)
	{
		if (!word_len && *str != c)
			counter++;
		word_len = (*str == c) ? 0 : 1;
		str++;
	}
	return (counter);
}

static int		get_word_len(char const *str, char c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i] == c)
		i++;
	while (str[i] != c && str[i] != '\0')
	{
		i++;
		len++;
	}
	return (len);
}

char			**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	**str2;

	if (!s || !(str2 = (char **)malloc(sizeof(*str2) *
		(ft_word_counter(s, c) + 1))))
		return (NULL);
	i = -1;
	j = 0;
	while (++i < ft_word_counter(s, c))
	{
		k = 0;
		if (!(str2[i] = ft_calloc(get_word_len(&s[j], c) + 1, 1)))
			str2[i] = NULL;
		while (s[j] == c)
			j++;
		while (s[j] != c && s[j])
			str2[i][k++] = s[j++];
		str2[i][k] = '\0';
	}
	str2[i] = 0;
	return (str2);
}
