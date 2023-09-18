/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taybakan <taybakan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 01:48:32 by fsoymaz           #+#    #+#             */
/*   Updated: 2023/07/31 05:13:58 by taybakan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	ft_is_whitespace(char c)
{
	return (c == ' ' || c == '\t');
}

void	find_end_pos(char **str, char type)
{
	(*str)++;
	while (**str)
	{
		if (**str == type)
		{
			(*str)++;
			if (**str == '\'' || **str == '"')
				without_quote_parse(str);
			else
				while (**str && !ft_is_whitespace(**str) && !is_operator(*str))
					(*str)++;
			return ;
		}
		(*str)++;
	}
}

void	without_quote_parse(char **str)
{
	while (**str)
	{
		if (**str == '\\' && ((*str)[1] == '"' || (*str)[1] == '\''))
		{
			(*str) += 2;
			continue ;
		}
		else if (**str == '"')
			find_end_pos(str, '"');
		else if (**str == '\'')
			find_end_pos(str, '\'');
		if (ft_is_whitespace(**str) || is_operator(*str))
			break ;
		(*str)++;
	}
}

void	skip_whitespace(char **str, char **head)
{
	while (**str && ft_is_whitespace(**str))
		(*str)++;
	*head = *str;
}

int	parse_token_string(char **str, t_token **tokens)
{
	int		len;
	char	*head;
	char	*token_str;

	head = *str;
	without_quote_parse(str);
	len = *str - head;
	if (len > 0)
	{
		token_str = ft_substr(head, 0, len);
		lst_add_back_token(tokens, lst_new_elem_token(WORD, token_str),
			ft_strlen(token_str));
		return (len);
	}
	return (0);
}
