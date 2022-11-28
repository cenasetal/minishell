/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_mng.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fporto <fporto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:00:45 by fheaton-          #+#    #+#             */
/*   Updated: 2022/11/28 16:32:08 by fporto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	error_output(char type, int i, char *str)
{
	if (i < 0)
		i = 0;
	if (type == 'c')
	{
		printf("minishell: command not found: %s\n", g_global.argv[i]);
		g_global.exit_status = 127;
	}
	else if (type == 'd')
	{
		printf("minishell: cd: %s: No such file or directory\n", \
			g_global.argv[i]);
		g_global.exit_status = 1;
	}
	else if (type == 's')
	{
		printf("minishell: special char not defined: %s\n", g_global.argv[i]);
		g_global.exit_status = 33;
	}
	else if (type == 'i')
	{
		printf("minishell: %s: No such file or directory\n", str);
		g_global.exit_status = 1;
	}
	return (g_global.exit_status);
}

static int	output_loop(t_list *output, int output_file)
{
	char	*path;

	while (output)
	{
		if (output_file)
			close(output_file);
		path = ft_substr((char *)output->content, 1,
				ft_strlen((char *)output->content));
		output_file = open(path, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR
				| S_IWUSR | S_IRGRP | S_IROTH);
		output = output->next;
		ft_free(path);
	}
	return (output_file);
}

static int	append_loop(t_list *append, int output_file)
{
	char	*path;

	while (append)
	{
		if (output_file)
			close(output_file);
		path = ft_substr((char *)append->content, 2,
				ft_strlen((char *)append->content));
		output_file = open(path, O_RDWR | O_CREAT | O_APPEND, 0644);
		append = append->next;
		ft_free(path);
	}
	return (output_file);
}

static int	final_output_loop(t_list *final_output, int output_file)
{
	char	*path;

	while (final_output)
	{
		if (output_file)
			close(output_file);
		if (!ft_strncmp(final_output->content, ">>", 2))
		{
			path = ft_substr((char *)final_output->content, 2,
					ft_strlen((char *)final_output->content));
			output_file = open(path, O_RDWR | O_CREAT | O_APPEND, 0644);
		}
		else if (!ft_strncmp(final_output->content, ">", 1))
		{
			path = ft_substr((char *)final_output->content, 1,
					ft_strlen((char *)final_output->content));
			output_file = open(path, O_RDWR | O_CREAT | O_TRUNC, 0644);
		}
		ft_free(path);
		final_output = final_output->next;
	}
	return (output_file);
}

int	file_output(t_list *output, t_list *append, t_list *final_output)
{
	int	output_file;

	output_file = 0;
	output_file = output_loop(output, output_file);
	output_file = append_loop(append, output_file);
	output_file = final_output_loop(final_output, output_file);
	return (output_file);
}
