/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 10:23:14 by irodrigo          #+#    #+#             */
/*   Updated: 2019/11/19 14:14:12 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		i;
	int			j;
	size_t		dst_ln;
	size_t		src_ln;

	j = 0;
	if (dst == NULL && src == NULL)
		return (0);
	i = ft_strlen(dst);
	src_ln = ft_strlen(src);
	dst_ln = i;
	j = 0;
	if (size < dst_ln + 1)
		return (src_ln + size);
	if (size > dst_ln + 1)
	{
		while (i < size - 1 && *src != '\0')
			*(dst + i++) = *src++;
		*(dst + i) = '\0';
	}
	return (src_ln + dst_ln);
}
