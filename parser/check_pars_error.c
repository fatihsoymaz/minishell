/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pars_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatihsoymaz <fatihsoymaz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 01:44:00 by fsoymaz           #+#    #+#             */
/*   Updated: 2023/10/03 22:41:54 by fatihsoymaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	check_pars_error(t_token *token)
{
	while (token)
	{
		if (token->type == PIPE || token->type == HEREDOC
			|| token->type == IN_RED || token->type == OUT_RED
			|| token->type == APPEND)
		{
			if (token->next == NULL || token->next->type == PIPE
				|| token->next->type == IN_RED || token->next->type == OUT_RED
				|| token->next->type == APPEND || token->next->type == HEREDOC)
			{
				printf("syntax error near unexpected token `newline'\n");
				return (1);
			}
		}
		token = token->next;
	}
	return (0);
}
