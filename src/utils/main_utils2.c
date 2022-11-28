/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:00:30 by fheaton-          #+#    #+#             */
/*   Updated: 2022/11/28 13:24:26 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "utilities.h"

static void	end_flag_condition(void)
{
	if (g_global.and_flag > 0 && (g_global.es_flag || g_global.exit_status))
	{
		if (g_global.exit_status)
			g_global.stop = 3;
	}
	else if (g_global.or_flag > 0 && \
		(!g_global.es_flag || !g_global.exit_status))
	{
		if (g_global.exit_status)
			g_global.stop = 4;
		else
			g_global.stop = -2;
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
		if (g_global.exit_status != 0)
		{
			g_global.es_flag = g_global.exit_status;
			g_global.and_flag++;
			g_global.stop = 1;
		}
		else
			g_global.and_flag++;
	}
	else
		g_global.and_flag = 1;
	if (cmd->cmd_flags & 0x08)
	{
		if (!g_global.exit_status)
		{
			g_global.es_flag = g_global.exit_status;
			g_global.or_flag++;
			g_global.stop = 2;
		}
		else
			g_global.or_flag++;
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
				g_global.stop = -10;
		}
		tree_loop(t, i);
	}
}

int	dup_init_and_close(char type)
{
	if (type == 'i')
	{
		g_global.tmp_in = dup(0);
		g_global.tmp_out = dup(1);
		g_global.fd_in = dup(g_global.tmp_in);
	}
	if (type == 'c')
	{
		dup2(g_global.tmp_in, 0);
		dup2(g_global.tmp_out, 1);
		close(g_global.tmp_in);
		close(g_global.tmp_out);
	}
	return (0);
}
