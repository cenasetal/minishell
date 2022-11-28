/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:00:21 by fheaton-          #+#    #+#             */
/*   Updated: 2022/11/28 17:08:51 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

#include "readline.h"

#include "minishell.h"
#include "utilities.h"

void	exit_fork(void)
{
	ft_free(g_global.input);
	exit(0);
}

void	signal_handler(int signal)
{
	rl_replace_line("", signal);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
}

/*
*  Closes all possibly open file descriptors and
*  kills all processes that were not naturally closed.
*/
void	clean_processes(void)
{
	int	i;

	i = 2;
	while (++i < MAX_FD)
		close(i);
	i = -1;
	while (g_global.pid_lst[++i] > 0)
	{
		kill(g_global.pid_lst[i], SIGTERM);
		g_global.pid_lst[i] = -1;
	}
}

void	re_init(void)
{
	clean_processes();
	g_global.fd_in = 0;
	g_global.fd_out = 1;
	g_global.cmd_counter = 0;
	g_global.file_counter = 0;
	g_global.hdoc_counter = 0;
	g_global.pid_counter = -1;
	g_global.first_cmd = 1;
	g_global.stop = 0;
	g_global.and_flag = 0;
	g_global.or_flag = 0;
	g_global.es_flag = 0;
}
