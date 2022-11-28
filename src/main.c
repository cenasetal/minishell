/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 23:17:23 by fletcher          #+#    #+#             */
/*   Updated: 2022/11/28 04:22:41 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

#include "readline.h"

#include "~libft.h"

#include "minishell.h"
#include "parser.h"
#include "utilities.h"
#include "execution.h"

t_mini	g_mini;

/*
*   Struct init function is used to initiate the stuct variable and cut down
*    some lines in the main function body.
*/
static void	struct_init(char **env)
{
	g_mini.head = ft_malloc(sizeof(t_dl_list));
	g_mini.env = get_env(env);
	g_mini.exit = 0;
	g_mini.exit_status = 0;
	g_mini.and_flag = 0;
	g_mini.or_flag = 0;
	g_mini.es_flag = 0;
	g_mini.stop = 0;
	g_mini.fd_in = 0;
	g_mini.fd_out = 1;
	g_mini.hdoc_counter = 0;
	g_mini.temp_path = ft_strdup("/tmp/");
	create_hdoc_and_pid_arrays();
	g_mini.file_counter = 0;
	g_mini.cmd_counter = 0;
	g_mini.pid_counter = -1;
}

/*
*   Check cmd calls function will run the command in case it exists on the tree
*    struct sent by the tree loop function.
*/
static int	check_cmd_calls(t_tree *t)
{
	t_cmd		*cmd;
	static int	step;

	cmd = (t_cmd *)t->content;
	step += 10;
	if (!cmd)
		return (0);
	g_mini.argv = cmd->cmd;
	g_mini.hdoc_counter = step;
	if (command_exec(cmd) == -1)
		return (-1);
	return (1);
}

/*
*   Tree loop function will check the tree leafs for commands. Also, it is
*    responsible for setting up the FD initial logic and retrieving exit
*    status variable from child process's.
*/
void	tree_loop(t_tree *t, int i)
{
	int		status;
	int		ret;
	t_cmd	*cmd;
	t_tree	*t_temp;

	cmd = NULL;
	dup_init_and_close('i');
	while (++i < t->lcount)
	{
		t_temp = t->leafs[i];
		cmd = (t_cmd *)t_temp->content;
		ret = check_cmd_calls(t->leafs[i]);
		if (ret == -1)
			break ;
		if (ret == 0 && t->leafs[i])
			tree_loop(t->leafs[i], -1);
		if (cmd && ((cmd->cmd_flags & 0x04) || (cmd->cmd_flags & 0x08)
				|| cmd->cmd_flags & 0x20))
			break ;
	}
	status = dup_init_and_close('c');
	(g_mini.pid > 0) && (waitpid(g_mini.pid, &status, 0));
	if (WIFEXITED(status))
		g_mini.exit_status = WEXITSTATUS(status);
	check_and_or_flag(cmd, t, i);
}

/*
*   The input loop is used to cut down some lines on the main function body.
*/
static void	input_loop(char *input)
{
	t_commands	*cmd;

	g_mini.input = input;
	g_mini.first_cmd = 1;
	add_history(input);
	cmd = parse(input);
	if (!cmd->error)
	{
		g_mini.cmd = cmd;
		check_heredoc(cmd->tree);
		g_mini.hdoc_counter = 0;
		tree_loop(cmd->tree, -1);
		delete_temp(g_mini.temp_path);
	}
	else
		printf("Syntax error code: %d\n", cmd->error);
	free_command(cmd);
	ft_free(input);
	re_init();
	input = NULL;
}

/*
*   The main function is responsible for receiving the input from the user and
*   manage it. It will make sure the program has a promp until the used call for
*   exit or sends the signal do quit.
*/
int	main(int argc, char **argv, char **env)
{
	char	*input;

	(void) argc;
	(void) argv;
	struct_init(env);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, hsi);
	while (42)
	{
		input = readline("minishell: ");
		if (input && ft_strlen(input) != 0)
			input_loop(input);
		else if (input)
			ft_free(input);
		if (g_mini.exit || !input)
			exit_loop();
	}
	return (0);
}
