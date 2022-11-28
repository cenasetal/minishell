/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:59:32 by fheaton-          #+#    #+#             */
/*   Updated: 2022/11/28 16:29:08 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "utilities.h"
#include "minishell.h"

/*
*   Swap function is used to swap 2 nodes position on a dual linked list.
*/
static void	swap(t_dl_list *a, t_dl_list *b, t_dl_list *c)
{
	t_dl_list	*d;

	d = c->next;
	if (a != NULL)
		a->next = c;
	c->next = b;
	b->next = d;
	b->prev = c;
	c->prev = a;
	if (d != NULL)
		d->prev = b;
}

/*
*   Sorts the list alphabetically based on the variable name. If current and
*    next node aren't sorted, swap them and run again.
*/
static void	sorter(t_dl_list *lst)
{
	int	ret;

	while (lst->next != NULL)
	{
		ret = ft_strncmp(lst->name, lst->next->name, ft_strlen(lst->name));
		if (ret > 0 || (ret == 0
				&& ft_strlen(lst->name) > ft_strlen(lst->next->name)))
		{
			swap(lst->prev, lst, lst->next);
			break ;
		}
		lst = lst->next;
	}
}

/*
*   Checks if the list is sorted alphabetically or not. If it gets to the end,
*    returns '1' (true) as all the list is sorted.
*    Returning '0' (false) means it is still not sorted.
*/
static int	checker(t_dl_list *lst)
{
	int	ret;

	while (lst->next != NULL)
	{
		ret = ft_strncmp(lst->name, lst->next->name, ft_strlen(lst->name));
		if (ret > 0)
			return (0);
		lst = lst->next;
	}
	return (1);
}

/*
*   Duplicates any dual linked list provided and returns a pointer to the new
*    list.
*/
static t_dl_list	*duplicate_list(t_dl_list *lst)
{
	t_dl_list	*temp;
	t_dl_list	*dup_lst;

	dup_lst = NULL;
	while (lst)
	{
		temp = ft_lstdup_dl(lst);
		ft_lstadd_back_dl(&dup_lst, temp);
		if (lst->next == NULL)
			break ;
		lst = lst->next;
	}
	return (dup_lst);
}

/*
*   Sort function for our environemntal variables list. It will duplicate and
*    sort alphabetically our list.
*    The list is destroyed after it is printed.
*/
int	env_sorted(void)
{
	t_dl_list	*lst;

	lst = duplicate_list(g_global.env);
	while (!checker(lst))
	{
		sorter(lst);
		lst = ft_lsthead_dl(lst);
	}
	ft_lstprint(lst, 'a');
	if (lst)
		free_list_nodes(lst);
	return (1);
}
