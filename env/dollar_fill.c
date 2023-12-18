/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_fill.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatihsoymaz <fatihsoymaz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 01:33:58 by fsoymaz           #+#    #+#             */
/*   Updated: 2023/10/03 22:18:22 by fatihsoymaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	dollar_fill(t_token *tokens)
{
	char	*tmp;

	while (tokens)
	{
		if (tokens->type == WORD)
		{
			if (ft_strchr(tokens->str, '$') && ft_strlen(tokens->str) > 1)
			{
				tmp = tokens->str;
				tokens->str = env_fill_init(tmp);
			}
		}
		tokens = tokens->next;
	}
}
