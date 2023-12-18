/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatihsoymaz <fatihsoymaz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 01:50:02 by fsoymaz           #+#    #+#             */
/*   Updated: 2023/10/03 22:42:40 by fatihsoymaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	return_new_str(char **new_str, char *str)
{
	char	*tmp;

	if (!(*new_str))
	{
		*new_str = ft_strdup(str);
		free(str);
		return ;
	}
	tmp = *new_str;
	*new_str = ft_strjoin(*new_str, str);
	free(tmp);
	free(str);
}

char	*replace_quote_tools(char *str, int *index, char type)
{
	int		first;
	char	*new_str;

	(*index)++;
	first = *index;
	while (str[*index] && str[*index] != type)
		(*index)++;
	new_str = ft_substr(str, first, *index - first);
	if (str[*index])
		(*index)++;
	return (new_str);
}

char	*no_quote_tools(char *str, int *i)
{
	int		j;
	char	*data;

	j = 0;
	data = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!data)
		return (0);
	while (str[*i] != '\0' && (str[*i] != '\'' && str[*i] != '\"'))
	{
		if (str[*i] == '\\')
		{
			(*i)++;
			if (str[*i] != '\0')
			{
				data[j] = str[*i];
				j++;
			}
		}
		else
			data[j++] = str[*i];
		(*i)++;
	}
	data[j] = '\0';
	return (data);
}

char	*delete_quote(char *str)
{
	int		i;
	char	*data;
	char	*result;

	i = 0;
	result = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			data = replace_quote_tools(str, &i, '\"');
		else if (str[i] == '\'')
			data = replace_quote_tools(str, &i, '\'');
		else
			data = no_quote_tools(str, &i);
		return_new_str(&result, data);
	}
	free(str);
	return (result);
}
