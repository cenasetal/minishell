/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:59:54 by fheaton-          #+#    #+#             */
/*   Updated: 2022/11/28 11:59:56 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	delete_temp(char *path)
{
	char	*file_path;
	char	*nbr;
	int		i;

	if (!path)
		return ;
	i = -1;
	while (++i < (g_global.file_counter + 1))
	{
		nbr = ft_itoa(i);
		if (ft_strcmp(g_global.hdoc_files[i], nbr) != 1)
		{
			file_path = ft_strjoin(path, g_global.hdoc_files[i]);
			unlink(file_path);
			ft_free(file_path);
			ft_free(g_global.hdoc_files[i]);
			g_global.hdoc_files[i] = ft_itoa(i);
		}
		ft_free(nbr);
	}
}

//The free list node will receive a dual linked list and it will free up all its
//nodes. No malloc used on the nodes content will be freed.
void	free_list_nodes(t_dl_list *lst)
{
	t_dl_list	*temp;

	if (!lst)
		return ;
	while (lst)
	{
		temp = lst->next;
		ft_free(lst);
		lst = NULL;
		lst = temp;
	}
}

//The free_argv function will free up all the variable on the arguments array
//created by the split function. Also free's up the table itself.
void	free_argv(void)
{
	int	x;
	int	y;

	x = 0;
	while (g_global.argv[x] != NULL)
		x++;
	y = -1;
	while (++y < x)
	{
		ft_free(g_global.argv[y]);
		g_global.argv[y] = NULL;
	}
	ft_free(g_global.argv);
}

//The free dl list function will receive and destroy all nodes on a dual linked
//list. It will also free up the content on each node that so make sure all
//the content is set on the heap.
void	free_dl_list(t_dl_list *lst)
{
	t_dl_list	*temp;

	while (lst)
	{
		temp = lst->next;
		ft_free(lst->content);
		ft_free(lst->name);
		ft_free(lst);
		lst = temp;
	}
}

/*
*   Frees up an array of strings that was malloced.
*/
void	free_table(char **array)
{
	int	i;

	i = -1;
	if (!array)
		return ;
	while (array[++i])
	{
		ft_free(array[i]);
		array[i] = NULL;
	}
	ft_free(array);
	array = NULL;
}
