/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 10:37:11 by irodrigo          #+#    #+#             */
/*   Updated: 2019/11/18 11:19:14 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	count;

	if (dest == 0)
		return (0);
	if (size == 0)
		return (ft_strlen(src));
	count = 0;
	while (size > 1 && *src)
	{
		*dest = *src;
		++dest;
		++src;
		--size;
		++count;
	}
	*dest = '\0';
	while (*dest || *src)
	{
		if (*src)
		{
			++src;
			++count;
		}
	}
	return (count);
}
