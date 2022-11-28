/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheaton- <fheaton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 04:15:46 by fheaton-          #+#    #+#             */
/*   Updated: 2022/11/28 04:21:40 by fheaton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"

# define S 1
# define D 2
# define Q 4
# define V 8

/**
 * error: Error code if parser fails
 */
typedef struct s_commands
{
	int		error;
	char	*line;
	t_tree	*tree;
}				t_commands;

/**
 * in: pointer to the actual input node
 * input: Input for command if any. NULL for stdin otherwise contains path to
 *   file. If heredoc the end string is specified here
 * input_flags: Flags for input.
 *   Defaults to 0. No extract info
 *   If (input_flags & 1) heredoc used as input.
 *   If (input_flags & 2) input piped from previous cmd.
 * output: Input for command if any. NULL for stdout otherwise contains path to
 *   file.
 * output_flags: Flags for output. Defaults to 0. Set to 1 if file in append.
 */
typedef struct s_input
{
	t_list	*in;
	t_list	*input;
	t_list	*heredoc;
	t_list	*out;
	t_list	*output;
	t_list	*append;
}				t_input;

/**
 * cmd: Command to be executed
 * cmd_flags: flags about the command.
 *   If (cmd_flags & 0x01) at least one argument/cmd has a possible wildcard.
 *   If (cmd_flags & 0x02) at least one argument/cmd needs to expand exit code.
 *   If (cmd_flags & 0x04) cmd is to be executed before a &&
 *   If (cmd_flags & 0x08) cmd is to be executed before a ||
 *   If (cmd_flags & 0x10) cmd is at the end of a list
 *   If (cmd_flags & 0x20) cmd is to be executed before a ; therefore reseting
 *     logic.
 *   If (cmd_flags & 0x40) input piped to next command
 * args: Arguments to be passed to the command
 * in: input
 */
typedef struct s_cmd
{
	char	*line;
	char	**cmd;
	char	cmd_flags;
	t_input	in;
}				t_cmd;

t_commands	*parse(const char *str);
char		*proc_q(char *str, t_commands *cmd);
int			split_cmd(t_tree *t, char *c, int i);
int			parse_op(t_tree *t);
int			expand(t_tree *t);
int			word_split(t_tree *t);
int			unmask(t_tree *t);
void		free_command(t_commands *cmd);
int			unmask_str(char *str);
t_commands	*validate(const char *str);
int			wild(int i, char **s, t_cmd *cmd, int norm);
int			ft_isspecial(char s);
void		lstsort(t_list **l);

#endif
