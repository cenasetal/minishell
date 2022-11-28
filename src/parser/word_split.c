/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fletcher <mgueifao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 02:43:06 by fletcher          #+#    #+#             */
/*   Updated: 2021/10/25 02:43:11 by fletcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
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
		if (!word_split(t->leafs[i++]))
			return (0);
	return (1);
}
