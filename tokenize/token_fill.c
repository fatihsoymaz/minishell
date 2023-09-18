/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoymaz <fsoymaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 01:47:11 by fsoymaz           #+#    #+#             */
/*   Updated: 2023/07/30 11:24:28 by fsoymaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	token_fill(char *input, t_token **tokens)
{
	while (*input)
	{
		while (*input == ' ')
			input++;
		if (is_operator(input) == PIPE)
			input += lst_add_back_token(tokens, lst_new_elem_token(PIPE,
						ft_strdup("|")), 1);
		else if (is_operator(input) == IN_RED)
			input += lst_add_back_token(tokens, lst_new_elem_token(IN_RED,
						ft_strdup("<")), 1);
		else if (is_operator(input) == OUT_RED)
			input += lst_add_back_token(tokens, lst_new_elem_token(OUT_RED,
						ft_strdup(">")), 1);
		else if (is_operator(input) == APPEND)
			input += lst_add_back_token(tokens, lst_new_elem_token(APPEND,
						ft_strdup(">>")), 2);
		else if (is_operator(input) == HEREDOC)
			input += lst_add_back_token(tokens, lst_new_elem_token(HEREDOC,
						ft_strdup("<<")), 2);
		else
			parse_token_string(&input, tokens);
	}
}
