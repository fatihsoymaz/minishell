/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_all_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatihsoymaz <fatihsoymaz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 01:46:25 by fsoymaz           #+#    #+#             */
/*   Updated: 2023/09/17 12:07:21 by fatihsoymaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	redirect_inputs(t_command *cmd)
{
	t_redirection	*redir;

	redir = cmd->redirects;
	while (redir)
	{
		if (redir->type == IN_RED)
			input(redir->redirect);
		else if (redir->type == HEREDOC)
			dup2(cmd->fd[0], 0);
		redir = redir->next;
	}
}

void	redirect_outputs(t_command *cmd)
{
	t_redirection	*redir;

	redir = cmd->redirects;
	while (redir)
	{
		if (redir->type == OUT_RED)
			output(redir->redirect, OUT_RED);
		else if (redir->type == APPEND)
			output(redir->redirect, APPEND);
		redir = redir->next;
	}
}
