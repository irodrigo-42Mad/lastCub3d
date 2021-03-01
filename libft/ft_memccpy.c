/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 12:18:12 by irodrigo          #+#    #+#             */
/*   Updated: 2019/11/25 12:05:14 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*uc_dst;
	unsigned char	*uc_src;

	uc_dst = (unsigned char*)dst;
	uc_src = (unsigned char*)src;
	i = 0;
	while (i < n)
	{
		uc_dst[i] = uc_src[i];
		if (uc_dst[i] == (unsigned char)c)
			return ((void*)(dst + i + 1));
		++i;
	}
	return (NULL);
}
