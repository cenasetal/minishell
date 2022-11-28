/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:57:14 by fheaton-          #+#    #+#             */
/*   Updated: 2022/11/28 16:23:57 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "minishell.h"
#include "utilities.h"

static void	file_output_instruction(t_cmd *cmd)
{
	if (cmd->in.out)
		g_global.fd_out = file_output(cmd->in.output, cmd->in.append,
				cmd->in.out);
	if (g_global.fd_out == 1)
		g_global.fd_out = dup(g_global.tmp_out);
	if (g_global.fd_out < 0)
		printf("OUTPUT ERROR\n");
}

/*
*   Check for all input files and if one doesn't exist, returns 0, which
*    prevents the command from running and exiting the command loop.
*/
static int	file_input_instruction(t_cmd *cmd)
{
	if (cmd->in.in)
		g_global.fd_in = file_input(cmd->in.input, cmd->in.heredoc, cmd->in.in);
	if (g_global.fd_in < 0)
	{
		dup2(g_global.tmp_in, 0);
		dup2(g_global.tmp_out, 1);
		close(g_global.tmp_in);
		close(g_global.tmp_out);
		return (0);
	}
	if (dup2(g_global.fd_in, 0) > 0)
		close(g_global.fd_in);
	return (1);
}

void	check_pipe(t_cmd *cmd)
{
	if ((cmd->cmd_flags & 0x40) && !cmd->in.out)
	{
		pipe(g_global.fd);
		g_global.fd_in = g_global.fd[0];
		g_global.fd_out = g_global.fd[1];
	}
	if (!(cmd->cmd_flags & 0x40) && !cmd->in.out)
		g_global.fd_out = dup(g_global.tmp_out);
	dup2(g_global.fd_out, 1);
	close(g_global.fd_out);
}

/*
*   Checks all outputs and inputs, pipe usage, sets up the FD and create forks.
*    All commands will be executed at the same time, a list of all child PIDs
*    will be created so all child processes can be closed in case of a
*    successful execute.
*    Will kill all ghost processes.
*/
int	execute_cmd(t_cmd *cmd)
{
	file_output_instruction(cmd);
	if (!file_input_instruction(cmd))
		return (-1);
	check_pipe(cmd);
	g_global.pid = fork();
	g_global.pid_lst[++g_global.pid_counter] = g_global.pid;
	if (g_global.pid == 0)
	{
		cmd_selector(cmd->cmd);
		exit(0);
	}
	return (g_global.exit_status);
}
