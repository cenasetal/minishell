/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:57:02 by fheaton-          #+#    #+#             */
/*   Updated: 2022/11/28 16:12:29 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.h"
#include "execution.h"
#include "minishell.h"

/*
*   Check the input files flags. If the file does not exist, it will
*    return 0, which will make the execute to stop and exit the command loop.
*/
static int	file_input_instruction(t_cmd *cmd, int input)
{
	input = file_input(cmd->in.input, cmd->in.heredoc, cmd->in.in);
	if (input > 0)
	{
		if (dup2(input, 0) != -1)
			return (EXIT_SUCCESS);
	}
	return (-1);
}

int	bultin_exec(t_cmd *cmd)
{
	int	output;
	int	input;

	input = 0;
	if (cmd->in.in)
	{
		if (file_input_instruction(cmd, input) < 0)
			return (-1);
	}
	if (cmd->in.out)
	{
		output = file_output(cmd->in.output, cmd->in.append, cmd->in.out);
		if (output < 0)
			dup2(output, 1);
	}
	screening_one(cmd->cmd);
	return (EXIT_SUCCESS);
}

/*
*   Checks for the END (;) flag so it can reset the First_cmd variable;
*    Also, it modifies the STOP variable in case it detects the OR flag;
*    Also, stops the cmd to be executed in case STOP variable is > 0.
*/
static int	stop_check(t_cmd *cmd)
{
	if (g_global.stop > 0)
		return (g_global.exit_status);
	return (execute_cmd(cmd));
}

/*
*   Modifies STOP variable when there is a &&/|| flag with no command which
*    means we are in between a parentesis and a command.
*/
static void	no_cmd_flagged(t_cmd *cmd)
{
	if (cmd->cmd_flags & 0x04)
	{
		if (g_global.stop > 0)
			g_global.stop = 5;
		else
			g_global.stop = -3;
		g_global.and_flag--;
	}
	if (cmd->cmd_flags & 0x08)
	{
		if (g_global.and_flag > 0)
		{
			if (g_global.stop > 0)
				g_global.stop = -4;
			else
				g_global.stop = 6;
		g_global.and_flag--;
		}
		if (g_global.stop > 0 && g_global.or_flag > 0)
			g_global.stop = 6;
		g_global.or_flag--;
	}
	g_global.first_cmd = 1;
}

/*
*   Flags used:
*   If (cmd_flags & 0x01) at least one argument/cmd has a possible wildcard.
*   If (cmd_flags & 0x02) at least one argument/cmd needs to expand exit code.
*   If (cmd_flags & 0x04) cmd is to be executed before a &&
*   If (cmd_flags & 0x08) cmd is to be executed before a ||
*   If (cmd_flags & 0x10) cmd is at the end of a list
*   If (cmd_flags & 0x20) cmd is to be executed before a ; therefore reseting
*    logic.
*   If (cmd_flags & 0x40) input piped to next command.
*/
int	command_exec(t_cmd *cmd)
{
	int	ret;

	ret = 0;
	if (!cmd->cmd[0])
	{
		no_cmd_flagged(cmd);
		return (-2);
	}
	if (!cmd_identifier(cmd->cmd) && g_global.first_cmd
		&& ((cmd->cmd_flags & 0x10) || (cmd->cmd_flags & 0x20)))
		return (bultin_exec(cmd));
	ret = stop_check(cmd);
	if (cmd->cmd_flags & 0x40)
		g_global.first_cmd = 0;
	else
		g_global.first_cmd = 1;
	return (ret);
}
