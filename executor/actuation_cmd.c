/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actuation_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatihsoymaz <fatihsoymaz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 01:37:46 by fsoymaz           #+#    #+#             */
/*   Updated: 2023/09/17 12:06:48 by fatihsoymaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	pipe_route(t_command *cmd)
{
	if (cmd->prev == NULL)
		dup2(cmd->fd[1], 1);
	else if (cmd->next == NULL)
		dup2(cmd->prev->fd[0], 0);
	else
	{
		dup2(cmd->prev->fd[0], 0);
		dup2(cmd->fd[1], 1);
	}
}

void	heredoc_route(t_command *cmd)
{
	dup2(cmd->fd[0], 0);
	if (cmd->next != NULL)
		dup2(cmd->fd[1], 1);
}

void	cmd_route(t_command *cmd)
{
	if (g_glb.cmd_count > 1)
	{
		if (contain_heredoc(cmd))
			heredoc_route(cmd);
		else
			pipe_route(cmd);
	}
	redirect_inputs(cmd);
	redirect_outputs(cmd);
	close_all_fd();
}

void	command_err(char *str)
{
	errno = 127;
	write(2, "minishell: ", 11);
	write(2, str, ft_strlen(str));
	write(2, ": command not found\n", 20);
	if (!is_parent())
		exit(errno);
}

int	arg_count_ex(t_execute *execute)
{
	int	i;

	i = 0;
	while (execute)
	{
		i++;
		execute = execute->next;
	}
	return (i);
}
