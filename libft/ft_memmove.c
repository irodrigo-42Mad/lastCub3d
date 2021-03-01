/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 11:58:46 by irodrigo          #+#    #+#             */
/*   Updated: 2019/11/18 14:31:31 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	unsigned char		*ptr_dst;
	const unsigned char	*ptr_src;

	ptr_dst = (unsigned char*)dst;
	ptr_src = (unsigned char*)src;
	i = 0;
	if (src == NULL && dst == NULL)
		return (NULL);
	if (ptr_src < ptr_dst)
		while (++i <= len)
			ptr_dst[len - i] = ptr_src[len - i];
	else
		while (len-- > 0)
			*(ptr_dst++) = *(ptr_src++);
	return (dst);
}
