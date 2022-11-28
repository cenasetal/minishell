/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultins_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fferreir <fferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 01:27:26 by fferreir          #+#    #+#             */
/*   Updated: 2022/02/09 01:43:08 by fferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include "parser.h"

#include "utilities.h"

/*
*   It will check for the input files flags. If the file does not exist, it will
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

/*
*   All built in function that are single commands will execute using this
*    function. It manages all the inputs/outputs.
*/
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
