/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstsort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:57:49 by fheaton-          #+#    #+#             */
/*   Updated: 2022/11/28 16:24:47 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	lstsort(t_list **l)
{
	t_list	*list;
	void	*tmp;

	list = *l;
	if (!list)
		return ;
	while (list->next)
	{
		if (ft_strncmp(list->content, list->next->content,
				ft_strlen(list->content)) <= 0)
		{
			list = list->next;
			continue ;
		}
		tmp = list->content;
		list->content = list->next->content;
		list->next->content = tmp;
		list = *l;
	}
}
