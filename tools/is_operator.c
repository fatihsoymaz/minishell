/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_operator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoymaz <fsoymaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 01:51:50 by fsoymaz           #+#    #+#             */
/*   Updated: 2023/07/25 01:51:54 by fsoymaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	is_operator(char *str)
{
	if (!str)
		return (0);
	if (str[0] == '<' && str[1] == '<')
		return (HEREDOC);
	if (str[0] == '>' && str[1] == '>')
		return (APPEND);
	if (str[0] == '<')
		return (IN_RED);
	if (str[0] == '>')
		return (OUT_RED);
	if (str[0] == '|')
		return (PIPE);
	return (0);
}
