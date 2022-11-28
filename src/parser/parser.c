/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:58:20 by fheaton-          #+#    #+#             */
/*   Updated: 2022/11/28 11:58:22 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "parser.h"
#include "utilities.h"

static void	free_cmd(void *v)
{
	t_cmd	*cmd;
	int		i;

	if (!v)
		return ;
	cmd = (t_cmd *)v;
	if (cmd->line)
		ft_free(cmd->line);
	i = -1;
	if (cmd->cmd)
	{
		while (cmd->cmd[++i])
			ft_free(cmd->cmd[i]);
		ft_free(cmd->cmd);
	}
	if (cmd->in.input)
		ft_lstclear(&cmd->in.input, ft_free);
	if (cmd->in.heredoc)
		ft_lstclear(&cmd->in.heredoc, ft_free);
	if (cmd->in.output)
		ft_lstclear(&cmd->in.output, ft_free);
	if (cmd->in.append)
		ft_lstclear(&cmd->in.append, ft_free);
	ft_free(v);
}

void	free_command(t_commands *cmd)
{
	ft_free(cmd->line);
	ft_treeclear(cmd->tree, free_cmd);
	ft_free(cmd);
}

t_commands	*parse(const char *str)
{
	t_commands	*cmd;

	cmd = validate(str);
	if (!cmd || cmd->error)
		return (cmd);
	cmd->tree = ft_treenew(NULL);
	cmd->line = proc_q(ft_strdup(str), cmd);
	if ((split_cmd(cmd->tree, cmd->line, 0) - 1) == (int)ft_strlen(cmd->line))
		if (!cmd->error)
			cmd->error = 10;
	if (cmd->error)
		return (cmd);
	if (!parse_op(cmd->tree))
		cmd->error = 100;
	if (cmd->error)
		return (cmd);
	if (!expand(cmd->tree))
		cmd->error = 1000;
	if (cmd->error)
		return (cmd);
	if (!word_split(cmd->tree))
		cmd->error = 10000;
	if (!cmd->error)
		unmask(cmd->tree);
	return (cmd);
}
