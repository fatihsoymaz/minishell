/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatihsoymaz <fatihsoymaz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 01:46:10 by fsoymaz           #+#    #+#             */
/*   Updated: 2023/09/17 12:07:11 by fatihsoymaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	fill_heredoc(void)
{
	t_command		*cmd;
	t_redirection	*redir;

	cmd = g_glb.commands;
	while (cmd)
	{
		redir = cmd->redirects;
		while (redir)
		{
			if (redir->type == HEREDOC)
				heredoc(cmd->fd, redir->redirect);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}
