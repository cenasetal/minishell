/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fferreir <fferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 01:27:47 by fferreir          #+#    #+#             */
/*   Updated: 2022/02/09 01:41:13 by fferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "minishell.h"
#include "utilities.h"

/*
*   It will check for all the input file requests and set the FD for them.
*/
static void	file_output_instruction(t_cmd *cmd)
{
	if (cmd->in.out)
		g_mini.fd_out = file_output(cmd->in.output, cmd->in.append,
				cmd->in.out);
	if (g_mini.fd_out == 1)
		g_mini.fd_out = dup(g_mini.tmp_out);
	if (g_mini.fd_out < 0)
		printf("OUTPUT ERROR\n");
}

/*
*   It will check for all input files, and, in case of the file not existing,
*    it will return 0, which will prevent the command to run and exiting the
*    command loop.
*/
static int	file_input_instruction(t_cmd *cmd)
{
	if (cmd->in.in)
		g_mini.fd_in = file_input(cmd->in.input, cmd->in.heredoc, cmd->in.in);
	if (g_mini.fd_in < 0)
	{
		dup2(g_mini.tmp_in, 0);
		dup2(g_mini.tmp_out, 1);
		close(g_mini.tmp_in);
		close(g_mini.tmp_out);
		return (0);
	}
	if (dup2(g_mini.fd_in, 0) > 0)
		close(g_mini.fd_in);
	return (1);
}

/*
*   Check pipe will check for the pipe flag and, if so, it will pipe the fd so
*    it can successuly save and forward the correct FD's.
*/
void	check_pipe(t_cmd *cmd)
{
	if ((cmd->cmd_flags & 0x40) && !cmd->in.out)
	{
		pipe(g_mini.fd);
		g_mini.fd_in = g_mini.fd[0];
		g_mini.fd_out = g_mini.fd[1];
	}
	if (!(cmd->cmd_flags & 0x40) && !cmd->in.out)
		g_mini.fd_out = dup(g_mini.tmp_out);
	dup2(g_mini.fd_out, 1);
	close(g_mini.fd_out);
}

/*
*   Execute cmd will is responsible for check all outputs and inputs, check for
*    for pipe usage, set up the FD, and create forks. Since all commands will
*    be executed at the same time, a list of all child PIDs will be create so
*    all child process that are running will be close in case of a successful
*    execute, ie, will kill all ghost processes.
*/
int	execute_cmd(t_cmd *cmd)
{
	file_output_instruction(cmd);
	if (!file_input_instruction(cmd))
		return (-1);
	check_pipe(cmd);
	g_mini.pid = fork();
	g_mini.pid_lst[++g_mini.pid_counter] = g_mini.pid;
	if (g_mini.pid == 0)
	{
		cmd_selector(cmd->cmd);
		exit(0);
	}
	return (g_mini.exit_status);
}
