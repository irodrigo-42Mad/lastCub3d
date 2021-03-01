/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 10:44:57 by irodrigo          #+#    #+#             */
/*   Updated: 2019/11/19 13:58:00 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content)
{
	t_list	*list;

	if (!(list = (t_list *)malloc(sizeof(*list))))
		return (NULL);
	list->content = (void *)content;
	list->next = NULL;
	return (list);
}
