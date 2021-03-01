/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 12:59:55 by irodrigo          #+#    #+#             */
/*   Updated: 2019/11/12 13:01:24 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	uc2;
	unsigned char	*uc_ptr;
	int				i;

	i = 0;
	uc2 = (unsigned char)c;
	uc_ptr = (unsigned char *)str;
	while (n--)
	{
		if (uc_ptr[i] == uc2)
			return (uc_ptr + i);
		i++;
	}
	return (NULL);
}
