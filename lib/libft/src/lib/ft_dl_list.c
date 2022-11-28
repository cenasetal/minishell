/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dl_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:23:02 by fheaton-          #+#    #+#             */
/*   Updated: 2022/11/28 11:25:39 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_listget_dl(const char *key, t_dl_list *l)
{
	while (l && !ft_strcmp(key, l->name))
		l = l->next;
	if (l)
		return (l->content);
	return (NULL);
}

t_dl_list	*ft_lsthead_dl(t_dl_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->prev != NULL)
		lst = lst->prev;
	return (lst);
}

t_dl_list	*ft_lstlast_dl(t_dl_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_dl(t_dl_list **lst, t_dl_list *new)
{
	t_dl_list	*temp;

	if (!new || !lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	else
	{
		temp = ft_lstlast_dl(*lst);
		temp->next = new;
		new->prev = temp;
	}
}

t_dl_list	*ft_lstnew_dl(char **content)
{
	t_dl_list	*new;

	new = (t_dl_list *)malloc(sizeof(t_dl_list));
	if (!new)
		return (NULL);
	new->name = content[0];
	new->content = content[1];
	new->next = NULL;
	return (new);
}