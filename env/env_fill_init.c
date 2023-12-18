/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_fill_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatihsoymaz <fatihsoymaz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 01:34:14 by fsoymaz           #+#    #+#             */
/*   Updated: 2023/10/03 22:18:13 by fatihsoymaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

char	*split_env2(char *str)
{
	while (*str != '=')
		str++;
	str++;
	return (ft_strdup(str));
}

int	valid_op(char c)
{
	return ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9')
		|| (c == '_'));
}

int	dollar_control(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 1;
	while (str[i])
	{
		if (str[i] == '\'')
			flag = 0;
		if (str[i] == '"')
			flag = 1;
		i++;
	}
	return (flag);
}

char	*get_str(char *str, int *pos, int type)
{
	int		first;
	char	*data;

	first = *pos;
	while (str[*pos] != type)
		(*pos)++;
	data = ft_substr(str, first, *pos - first);
	(*pos)++;
	return (data);
}

char	*env_fill_init(char *str)
{
	char	*tmp;

	while (ft_strchr(str, '$') && dollar_control(str))
	{
		tmp = str;
		str = env_fill_str(tmp);
		free(tmp);
	}
	return (str);
}
