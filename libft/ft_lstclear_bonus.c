/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irodrigo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 11:56:49 by irodrigo          #+#    #+#             */
/*   Updated: 2019/11/20 11:59:08 by irodrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*list;
	t_list	*tmp;

	tmp = NULL;
	if (lst == NULL || *lst == NULL)
		return ;
	list = *lst;
	while (list)
	{
		tmp = list;
		list = list->next;
		del(tmp->content);
		free(tmp);
	}
	*lst = NULL;
}
