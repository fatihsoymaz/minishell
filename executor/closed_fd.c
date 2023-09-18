/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closed_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatihsoymaz <fatihsoymaz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 01:38:42 by fsoymaz           #+#    #+#             */
/*   Updated: 2023/09/17 12:07:44 by fatihsoymaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	contain_heredoc(t_command *tmp)
{
	t_redirection	*cmd;

	cmd = g_glb.commands->redirects;
	(void)tmp;
	while (cmd)
	{
		if (cmd->type == HEREDOC)
			return (1);
		if (cmd->next)
			cmd = cmd->next;
		else
			break ;
	}
	return (0);
}

void	close_heredoc_fd(t_command *cmd)
{
	if (contain_heredoc(cmd) && cmd->fd[0] > 2)
		close(cmd->fd[0]);
}

void	close_all_fd(void)
{
	t_command	*cmd;

	cmd = g_glb.commands;
	while (cmd)
	{
		close_heredoc_fd(cmd);
		if (cmd->fd[0] > 2)
			close(cmd->fd[0]);
		if (cmd->fd[1] > 2)
			close(cmd->fd[1]);
		cmd = cmd->next;
	}
}
