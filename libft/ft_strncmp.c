/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 10:34:00 by irodrigo          #+#    #+#             */
/*   Updated: 2019/11/23 12:16:22 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t				i;
	const unsigned char	*c_s1;
	const unsigned char	*c_s2;

	c_s1 = (unsigned char *)s1;
	c_s2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (c_s1[i] == c_s2[i] && c_s1[i] != '\0'
			&& c_s2[i] != '\0' && i < n - 1)
		i++;
	return (c_s1[i] - c_s2[i]);
}
