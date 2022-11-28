/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:59:04 by fheaton-          #+#    #+#             */
/*   Updated: 2022/11/28 11:59:06 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

int	word_split(t_tree *t)
{
	t_cmd	*cmd;
	int		i;

	cmd = (t_cmd *)t->content;
	if (cmd)
		cmd->cmd = ft_split(cmd->line, ' ');
	i = 0;
	while (i < t->lcount)
		if (!word_split(t->leaves[i++]))
			return (0);
	return (1);
}
