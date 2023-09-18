/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoymaz <fsoymaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 01:44:16 by fsoymaz           #+#    #+#             */
/*   Updated: 2023/09/16 13:41:28 by fsoymaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

t_command	*setup_cmd(void)
{
	t_command	*commands;

	commands = ft_calloc(sizeof(t_command), 1);
	pipe(commands->fd);
	commands->execute = ft_calloc(sizeof(t_execute), 1);
	commands->redirects = ft_calloc(sizeof(t_redirection), 1);
	commands->tmp = commands->execute;
	commands->tmp2 = commands->redirects;
	commands->execute = 0;
	commands->redirects = 0;
	commands->prev = NULL;
	commands->next = NULL;
	return (commands);
}

void	add_back_cmd(t_command **commands, t_command *new_cmd)
{
	t_command	*tmp;

	tmp = *commands;
	if (!(tmp))
		*commands = new_cmd;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_cmd;
		new_cmd->prev = tmp;
	}
}

void	add_arguman(t_token **token, t_command *commands)
{
	if ((*token)->type == WORD)
	{
		commands->execute = fill_execute(*token, &commands->execute);
	}
	else if ((*token)->type == HEREDOC)
	{
		commands->redirects = fill_redirect(*token, &commands->redirects);
	}
	else if ((*token)->type == IN_RED || (*token)->type == OUT_RED
		|| (*token)->type == APPEND)
	{
		commands->redirects = fill_redirect(*token, &commands->redirects);
	}
}

void	fill_command(t_token *tokens, t_command **commands)
{
	t_command	*cmd;

	cmd = 0;
	while (tokens)
	{
		if (tokens->type == PIPE || tokens->prev == NULL)
		{
			if (tokens->type == PIPE)
				tokens = tokens->next;
			cmd = setup_cmd();
			add_back_cmd(commands, cmd);
			g_glb.cmd_count++;
		}
		if (!tokens)
			break ;
		add_arguman(&tokens, cmd);
		if (tokens)
			tokens = tokens->next;
	}
}
