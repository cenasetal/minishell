/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_mng.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:00:03 by fheaton-          #+#    #+#             */
/*   Updated: 2022/11/28 13:25:06 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "readline.h"
#include "libft.h"
#include "minishell.h"

//The Temp Path function is responsible to create the path for the temporary
//files that hold the heredoc data provided by the user.
char	*temp_path(char *filename, char *path)
{
	char	*pth;

	if (!filename || !path)
		return (NULL);
	pth = ft_strjoin(path, filename);
	ft_free(g_global.hdoc_files[g_global.file_counter]);
	g_global.hdoc_files[g_global.file_counter++] = filename;
	return (pth);
}

//The create heredoc file function is to create and save the information
//provided by the user through input. The temp file name is going to be a
//joint of the eof provided by the user and a global counter used for heredoc
//requests count.
static int	create_hrdoc_file(char *eof_str, char *filename)
{
	char	*input;
	int		output;

	if (!eof_str)
		return (-1);
	filename = temp_path(filename, g_global.temp_path);
	if (!filename)
		return (-1);
	output = open(filename, 02 | 0100 | 01000, 0400 | 0200 | 040 | 04);
	if (output < 0)
		return (-1);
	input = readline("heredoc> ");
	while (input && ft_strcmp(input, eof_str) != 1)
	{
		if (ft_strlen(input) > 0)
			write(output, input, ft_strlen(input));
		write(output, "\n", 1);
		ft_free(input);
		input = readline("heredoc> ");
	}
	ft_free(input);
	ft_free(eof_str);
	ft_free(filename);
	close(output);
	return (0);
}

//The Check heredoc call function will look for a heredoc call on the provided
//cmd line. If found, it will request the creation of a temporary file that will
//would the heredoc data.
static void	check_heredoc_call(t_cmd *cmd)
{
	t_list	*head;
	char	*filename;
	char	*eof;
	char	*i;

	eof = NULL;
	if (cmd->in.heredoc)
		head = cmd->in.heredoc;
	while (cmd->in.heredoc)
	{
		eof = (char *)cmd->in.heredoc->content;
		i = ft_itoa(++g_global.hdoc_counter);
		filename = ft_strjoin(eof, i);
		ft_free(i);
		if (create_hrdoc_file(ft_substr(eof, 2, ft_strlen(eof)), filename) < 0)
			printf("Error: unable to create heredoc file\n");
		cmd->in.heredoc = cmd->in.heredoc->next;
	}
	if (eof)
		cmd->in.heredoc = head;
}

//The Check heredoc function is to run through the command list. If cmd does not
//point to NULL, it will send it to another function to check for an eventual
//heredoc call in the cmd line.
static int	check_loop(t_tree *t)
{
	t_cmd		*cmd;
	static int	step;

	cmd = (t_cmd *)t->content;
	step += 10;
	if (!cmd)
		return (0);
	g_global.hdoc_counter = step;
	check_heredoc_call(cmd);
	return (1);
}

void	check_heredoc(t_tree *t)
{
	int	i;
	int	ret;

	i = -1;
	ret = 1;
	while (++i < t->lcount)
	{
		ret = check_loop(t->leaves[i]);
		if (ret == 0 && t->leaves[i])
			check_heredoc(t->leaves[i]);
	}
}
