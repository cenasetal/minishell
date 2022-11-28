/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fferreir <fferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 18:09:01 by fferreir          #+#    #+#             */
/*   Updated: 2022/02/09 01:48:39 by fferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <signal.h>

#include "readline.h"

#include "minishell.h"
#include "utilities.h"

void	hsi(int signal)
{
	rl_replace_line("", signal);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
}

/*
*   The Clean Processes function closes all possible open file descriptors and
*    kill all open processes that were not naturally closed.
*/
void	clean_processes(void)
{
	int	i;

	i = 2;
	while (++i < MAX_FD)
		close(i);
	i = -1;
	while (g_mini.pid_lst[++i] > 0)
	{
		kill(g_mini.pid_lst[i], SIGTERM);
		g_mini.pid_lst[i] = -1;
	}
}

/*
*   It will re-initialize all the variables that are needed to be reseted for
*    the input loop. It will also call the Clean Processes function.
*/
void	re_init(void)
{
	clean_processes();
	g_mini.fd_in = 0;
	g_mini.fd_out = 1;
	g_mini.cmd_counter = 0;
	g_mini.file_counter = 0;
	g_mini.hdoc_counter = 0;
	g_mini.pid_counter = -1;
	g_mini.first_cmd = 1;
	g_mini.stop = 0;
	g_mini.and_flag = 0;
	g_mini.or_flag = 0;
	g_mini.es_flag = 0;
}
