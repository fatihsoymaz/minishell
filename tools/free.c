/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoymaz <fsoymaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 01:51:29 by fsoymaz           #+#    #+#             */
/*   Updated: 2023/07/25 01:51:32 by fsoymaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	free_token(t_token *tokens)
{
	t_token	*tmp;
	t_token	*token;

	token = tokens;
	while (token)
	{
		free(token->str);
		token = token->next;
	}
	token = tokens;
	while (token)
	{
		tmp = token;
		token = token->next;
		free(tmp);
	}
}

void	free_redir(t_redirection *tokens)
{
	t_redirection	*tmp;
	t_redirection	*token;

	token = tokens;
	while (token)
	{
		tmp = token;
		token = token->next;
		free(tmp);
	}
}

void	free_exec(t_execute *tokens)
{
	t_execute	*tmp;
	t_execute	*token;

	token = tokens;
	while (token)
	{
		tmp = token;
		token = token->next;
		free(tmp);
	}
}

void	free_cmd(void)
{
	t_command	*cmd;
	t_command	*tmp;

	cmd = g_glb.commands;
	if (!cmd)
		return ;
	while (cmd)
	{
		free_exec(cmd->execute);
		free_redir(cmd->redirects);
		tmp = cmd;
		cmd = cmd->next;
		free(tmp->tmp);
		free(tmp->tmp2);
		free(tmp);
	}
}

void	del_quote(t_token *token)
{
	while (token)
	{
		token->str = delete_quote(token->str);
		token = token->next;
	}
}
