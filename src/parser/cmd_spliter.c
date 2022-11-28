/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_spliter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:57:30 by fheaton-          #+#    #+#             */
/*   Updated: 2022/11/28 11:57:32 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

static void	*newcmd(char *key, char *c)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->line = c;
	((!ft_strncmp(key, "&&", 2)) && (cmd->cmd_flags |= 0x04))
	|| ((!ft_strncmp(key, "||", 2)) && (cmd->cmd_flags |= 0x08))
	|| (((*key == ')') || (*key == '\0')) && (cmd->cmd_flags |= 0x10))
	|| ((*key == ';') && (cmd->cmd_flags |= 0x20))
	|| ((*key == '|') && (cmd->cmd_flags |= 0x40));
	return (cmd);
}

int	split_cmd(t_tree *t, char *c, int i)
{
	int	j;

	j = i;
	while (j >= 0 && c[i] && c[i] != ')')
		((((c[i] == '&') || (c[i] == '|')) && (c[i] == c[i + 1]))
			&& (ft_treeadd(t, newcmd(c + i, ft_substr(c, j, i - j))))
			&& (i += 2) && (j = i))
		|| ((c[i] == '(') && (ft_treeadd(t, NULL))
			&& (i = split_cmd(t->leaves[t->lcount - 1], c, i + 1)) && (j = i))
		|| ((c[i] == ';')
			&& (ft_treeadd(t, newcmd(c + i, ft_substr(c, j, i - j))))
			&& (i = split_cmd(t, c, i + 1)) && (j = -1))
		|| ((c[i] == '|')
			&& (ft_treeadd(t, newcmd(c + i, ft_substr(c, j, i - j))))
			&& (j = ++i))
		|| (i++);
	if (j >= 0 && i - j > 0)
		ft_treeadd(t, newcmd(c + i, ft_substr(c, j, i - j)));
	if (j == -1 || !c[i])
		return (i);
	return (i + 1);
}
