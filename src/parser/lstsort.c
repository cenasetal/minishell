/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstsort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgueifao <mgueifao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 17:40:23 by mgueifao          #+#    #+#             */
/*   Updated: 2021/12/25 03:18:33 by mgueifao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include "ft_string.h"

void	lstsort(t_list **l)
{
	t_list	*aux;
	void	*tmp;

	aux = *l;
	if (!aux)
		return ;
	while (aux->next)
	{
		if (ft_strncmp(aux->content, aux->next->content,
				ft_strlen(aux->content)) <= 0)
		{
			aux = aux->next;
			continue ;
		}
		tmp = aux->content;
		aux->content = aux->next->content;
		aux->next->content = tmp;
		aux = *l;
	}
}
