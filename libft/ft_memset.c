/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 11:34:46 by irodrigo          #+#    #+#             */
/*   Updated: 2019/11/13 10:08:32 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *src, int c, size_t len)
{
	unsigned char	*aux;
	size_t			pos;

	aux = (unsigned char *)src;
	pos = 0;
	while (len > 0 && pos < len)
	{
		aux[pos] = (unsigned char)c;
		pos++;
	}
	return (src);
}
