/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:56:37 by fheaton-          #+#    #+#             */
/*   Updated: 2022/11/28 11:56:39 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Deletes the node where the environmental variable is allocated.
static void	node_destroyer(t_dl_list *list)
{
	ft_free(list->name);
	ft_free(list->content);
	list->name = NULL;
	list->content = NULL;
	list = NULL;
}

//Searches the list for the name of the variable we want to unset.
//It's used to make sure we have the variable present on our list.
static int	lst_str_check(t_dl_list *lst, char *str)
{
	t_dl_list	*head;
	char		*name;

	head = lst;
	while (1)
	{
		name = lst->name;
		if (ft_strcmp(name, str))
		{
			lst = head;
			return (1);
		}
		if (lst->next == NULL)
			break ;
		lst = lst->next;
	}
	lst = head;
	return (0);
}

//Unset fuction is used to remove an environmental variable from our internal
//env list.
//The integer 'i' is the index of the command 'unset' on the received args
//table.
void	ft_unset(t_dl_list *env, char **argv, int i)
{
	t_dl_list	*head;
	t_dl_list	*temp;
	t_dl_list	*temp2;

	head = env;
	temp = NULL;
	if (!(lst_str_check(env, argv[i + 1])))
		return ;
	while (!(ft_strcmp(env->name, argv[i + 1])))
	{
		temp = env;
		env = env->next;
	}
	if (env->next != NULL)
		temp2 = env->next;
	else
		temp2 = NULL;
	temp->next = temp2;
	node_destroyer(env);
	env = head;
}
