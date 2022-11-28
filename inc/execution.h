/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 04:15:56 by fheaton-          #+#    #+#             */
/*   Updated: 2022/11/28 11:52:07 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "parser.h"

/*
*   Command Execution functions
*/
int		command_exec(t_cmd *cmd);
/*
*   Pipe functions
*/
int		pipe_command(t_cmd *cmd, int fd[2]);

/*
*execute cmd function
*/
int		execute_cmd(t_cmd *cmd);

/*
*   Execute bultin functions
*/
int		bultin_exec(t_cmd *cmd);
#endif
