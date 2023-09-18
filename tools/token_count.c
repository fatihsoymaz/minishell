/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_count.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoymaz <fsoymaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 01:53:53 by fsoymaz           #+#    #+#             */
/*   Updated: 2023/07/29 07:09:42 by fsoymaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	double_quote(char *line, int *i, int *count)
{
	if (line[*i] == '\"')
	{
		if ((*i >= 1 && line[*i - 1] != '\\') || *i == 0)
		{
			(*i)++;
			while (((line[*i] != '\"' || ((line[*i] == '\"') && \
				line[*i - 1] == '\\')) && line[*i] != '\0'))
				(*i)++;
			if (line[*i] == '\0')
			{
				ft_putstr_fd("Error: found not closed quote\n", 2);
				(*count) = -300;
			}
			if (line[*i - 1] != '\\')
			{
				(*i)++;
				if (line[*i] == '\0' || is_operator(&line[*i]) != 0)
					(*count)++;
			}
		}
		else if ((line[*i] == '\"') && (line[*i - 1] == '\\'))
			(*i) += 1;
		else
			words_and_op(line, i, count);
	}
}

void	words_and_op(char *line, int *i, int *count)
{
	if (is_operator(&line[*i]) != 0 && line[*i] != '\0')
	{
		while (is_operator(&line[*i]) != 0 && line[*i] != '\0')
			(*i)++;
		(*count)++;
	}
	else if (line[*i] != '\'' && line[*i] != '\"' && line[*i] != '\0')
	{
		while (is_operator(&line[*i]) == 0 && line[*i] != '\0' \
			&& line[*i] != '\'' && line[*i] != '\"')
			(*i)++;
		if ((line[*i] != '\'' && line[*i] != '\"') || line[*i] == '\0')
			(*count)++;
	}
}

void	single_quote(char *line, int *i, int *count)
{
	if (line[*i] == '\'')
	{
		if ((*i >= 1 && (line[*i - 1]) != '\\') || *i == 0)
		{
			(*i)++;
			while (((line[*i] != '\'' || ((line[*i] == '\'') && \
				line[*i - 1] == '\\')) && line[*i] != '\0'))
				(*i)++;
			if (line[*i] == '\0')
			{
				ft_putstr_fd("Error: found not closed quote\n", 2);
				(*count) = -300;
			}
			if (line[*i - 1] != '\\')
			{
				(*i)++;
				if (line[*i] == '\0' || is_operator(&line[*i]) != 0)
					(*count)++;
			}
		}
		else if ((line[*i] == '\'') && (line[*i - 1] == '\\'))
			(*i) += 1;
		else
			words_and_op(line, i, count);
	}
}


int	tokens_count(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i] != '\0')
	{
		single_quote(line, &i, &count);
		double_quote(line, &i, &count);
		words_and_op(line, &i, &count);
	}
	return (count);
}