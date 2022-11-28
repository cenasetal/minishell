/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fferreir <fferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 01:47:57 by fferreir          #+#    #+#             */
/*   Updated: 2022/02/09 21:41:14 by fferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "minishell.h"
#include "utilities.h"

static void	end_flag_condition(void)
{
	if (g_mini.and_flag > 0 && (g_mini.es_flag || g_mini.exit_status))
	{
		if (g_mini.exit_status)
			g_mini.stop = 3;
	}
	else if (g_mini.or_flag > 0 && (!g_mini.es_flag || !g_mini.exit_status))
	{
		if (g_mini.exit_status)
			g_mini.stop = 4;
		else
			g_mini.stop = -2;
	}
}

/*
*   Modifies the STOP, AND, OR and ES flags if the command flag && or || was
*    flagged.
*/
static void	and_or_flag(t_cmd *cmd)
{
	if ((cmd->cmd_flags & 0x04))
	{
		if (g_mini.exit_status != 0)
		{
			g_mini.es_flag = g_mini.exit_status;
			g_mini.and_flag++;
			g_mini.stop = 1;
		}
		else
			g_mini.and_flag++;
	}
	else
		g_mini.and_flag = 1;
	if (cmd->cmd_flags & 0x08)
	{
		if (!g_mini.exit_status)
		{
			g_mini.es_flag = g_mini.exit_status;
			g_mini.or_flag++;
			g_mini.stop = 2;
		}
		else
			g_mini.or_flag++;
	}
}

/*
*   It checks the AND and OR flag in case there is a command so it can call the
*    tree_loop function and so it can execute the next command. This is necessa-
*    ry because the commands work inside a while loop that is forked and we
*    we only have access to the Exit Status of the command after it resolves.
*   It will also modifies the STOP variable at this stage so that the next
*    command will not resolve in case the STOP is > 0.
*/
void	check_and_or_flag(t_cmd *cmd, t_tree *t, int i)
{
	if (cmd && !(cmd->cmd_flags & 0x40))
	{
		if (cmd->cmd[0])
		{
			and_or_flag(cmd);
			if (cmd->cmd_flags & 0x10)
				end_flag_condition();
			else if ((cmd->cmd_flags & 0x20))
				g_mini.stop = -10;
		}
		tree_loop(t, i);
	}
}

int	dup_init_and_close(char type)
{
	if (type == 'i')
	{
		g_mini.tmp_in = dup(0);
		g_mini.tmp_out = dup(1);
		g_mini.fd_in = dup(g_mini.tmp_in);
	}
	if (type == 'c')
	{
		dup2(g_mini.tmp_in, 0);
		dup2(g_mini.tmp_out, 1);
		close(g_mini.tmp_in);
		close(g_mini.tmp_out);
	}
	return (0);
}
