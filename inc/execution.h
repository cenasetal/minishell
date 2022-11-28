/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 04:15:56 by fheaton-          #+#    #+#             */
/*   Updated: 2022/11/28 17:13:00 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "parser.h"

int		command_exec(t_cmd *cmd);

int		pipe_command(t_cmd *cmd, int fd[2]);

int		execute_cmd(t_cmd *cmd);

int		bultin_exec(t_cmd *cmd);
#endif
