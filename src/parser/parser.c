/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgueifao <mgueifao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 22:03:59 by mgueifao          #+#    #+#             */
/*   Updated: 2021/12/07 03:37:18 by mgueifao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_stdlib.h>

#include "ft_string.h"
#include "ft_stdlib.h"

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
