/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:12:50 by fheaton-          #+#    #+#             */
/*   Updated: 2022/11/28 11:17:41 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_treeadd(t_tree *tree, void *content)
{
	t_tree	*new;

	new = ft_treenew(content);
	if (!new)
		return (0);
	tree->leaves = ft_realloc(tree->leaves, tree->lcount * sizeof(t_tree),
			(tree->lcount + 1) * sizeof(t_tree));
	tree->leaves[tree->lcount++] = new;
	return (1);
}

int	ft_treeclear(t_tree *t, void (*del)(void *))
{
	if (!t)
		return (0);
	del(t->content);
	while (t->lcount)
		ft_treeclear(t->leaves[--t->lcount], del);
	free(t->leaves);
	free(t);
	return (1);
}

t_tree	*ft_treenew(void *content)
{
	t_tree	*ret;

	ret = ft_calloc(1, sizeof(t_tree));
	if (!ret)
		return (NULL);
	ret->content = content;
	return (ret);
}