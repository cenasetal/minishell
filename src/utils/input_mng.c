/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_mng.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fferreir <fferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 17:00:03 by fferreir          #+#    #+#             */
/*   Updated: 2022/02/09 00:33:29 by fferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>

#include "ft_conv.h"
#include "ft_string.h"
#include "ft_stdlib.h"

#include "utilities.h"
#include "minishell.h"

static int	heredoc_loop(t_list *heredoc, int input_hdoc)
{
	char	*pth;
	char	*i;

	while (heredoc)
	{
		if (input_hdoc)
			close(input_hdoc);
		i = ft_itoa(++g_mini.hdoc_counter);
		pth = ft_strjoin((char *)heredoc->content, i);
		pth = temp_path(pth, g_mini.temp_path);
		input_hdoc = open(pth, O_RDONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		heredoc = heredoc->next;
		ft_free(pth);
		ft_free(i);
	}
	return (input_hdoc);
}

static int	input_loop(t_list *input, int input_file)
{
	char	*pth;

	while (input)
	{
		if (input_file)
			close(input_file);
		pth = ft_substr((char *)input->content, 1,
				ft_strlen((char *)input->content));
		input_file = open(pth, O_RDONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (input_file == -1)
		{
			error_output('i', 0, input->content + 1);
			ft_free(pth);
			break ;
		}
		input = input->next;
		ft_free(pth);
	}
	return (input_file);
}

int	file_input(t_list *input, t_list *heredoc, t_list *in)
{
	int		input_file;
	int		input_hdoc;

	input_file = 0;
	input_hdoc = 0;
	input_file = input_loop(input, input_file);
	input_hdoc = heredoc_loop(heredoc, input_hdoc);
	if (!ft_strncmp(in->content, "<<", 2))
	{
		if (input_file)
			close(input_file);
		return (input_hdoc);
	}
	if (input_hdoc)
		close(input_hdoc);
	return (input_file);
}
