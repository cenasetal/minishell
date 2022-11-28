/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dl_list2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:19:13 by fheaton-          #+#    #+#             */
/*   Updated: 2022/11/28 13:25:56 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dl_list	*ft_lstdup_dl(t_dl_list *lst)
{
	t_dl_list	*new;

	new = (t_dl_list *)malloc(sizeof(t_dl_list));
	if (!new)
		return (NULL);
	new->name = lst->name;
	new->content = lst->content;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void	ft_lstnode_print_dl(t_dl_list *lst)
{
	printf("C= |%s - %p|", (char *)lst->name, lst->name);
	if (lst->prev != NULL)
		printf(" , P= |%s - %p|", (char *)lst->prev->name, lst->prev->name);
	else
		printf(" , P= |null|");
	if (lst->next != NULL)
		printf(" , N= |%s - %p|", (char *)lst->next->name, lst->next->name);
	else
		printf(" , N= |null|");
	printf("\n");
}

void	ft_lstnode_print(t_dl_list *lst, char *name)
{
	t_dl_list	*head;

	head = lst;
	while (1)
	{
		if (ft_strcmp(lst->name, name))
			printf("Content=|%s|, Name=|%s|, PREV=|%p| ADD=|%p| Next=|%p|\n",
				(char *)lst->content, (char *)lst->name, (void *)lst->prev,
				(void *)lst, (void *)lst->next);
		if (lst->next == NULL)
			break ;
		lst = lst->next;
	}
	lst = head;
}

void	ft_lstprint(t_dl_list *lst, char type)
{
	t_dl_list	*head;

	head = lst;
	while (lst)
	{
		if (type == 'n' || type == 'a')
			printf("%s", (char *)lst->name);
		if (type == 'a')
			printf("=");
		if (type == 'c' || type == 'a')
			printf("%s\n", (char *)lst->content);
		if (type == 'd')
			ft_lstnode_print_dl(lst);
		lst = lst->next;
	}
	lst = head;
}
