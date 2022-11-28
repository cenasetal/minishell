/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_mng.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fferreir <fferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:43:44 by fferreir          #+#    #+#             */
/*   Updated: 2021/12/27 17:59:31 by fferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>

#include "ft_string.h"
#include "ft_stdlib.h"
#include "ft_list.h"

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
		output_file = open(path, O_RDWR | O_CREAT | O_APPEND, S_IRUSR
				| S_IWUSR | S_IRGRP | S_IROTH);
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
			output_file = open(path, O_RDWR | O_CREAT | O_APPEND, S_IRUSR
					| S_IWUSR | S_IRGRP | S_IROTH);
		}
		else if (!ft_strncmp(final_output->content, ">", 1))
		{
			path = ft_substr((char *)final_output->content, 1,
					ft_strlen((char *)final_output->content));
			output_file = open(path, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR
					| S_IWUSR | S_IRGRP | S_IROTH);
		}
		ft_free(path);
		final_output = final_output->next;
	}
	return (output_file);
}

int	file_output(t_list *output, t_list *append, t_list *final_output)
{
	int		output_file;

	output_file = 0;
	output_file = output_loop(output, output_file);
	output_file = append_loop(append, output_file);
	output_file = final_output_loop(final_output, output_file);
	return (output_file);
}
