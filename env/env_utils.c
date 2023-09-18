/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoymaz <fsoymaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 01:36:04 by fsoymaz           #+#    #+#             */
/*   Updated: 2023/09/16 14:00:24 by fsoymaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	new_str_fill(char **new_str, char *str)
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

char	*env_fill_str(char *str)
{
	int		i;
	int		first;
	char	*env;
	char	*result;
	char	*data;

	i = 0;
	result = NULL;
	data = get_str(str, &i, '$');
	new_str_fill(&result, data);
	first = i;
	if (str[i] == '?' && ++i)
		new_str_fill(&result, ft_itoa(g_glb.erorno));
	else
	{
		while (valid_op(str[i]))
			(i)++;
		data = ft_substr(str, first, i - first);
		env = get_env(data);
		new_str_fill(&result, env);
		free(data);
	}
	data = get_str(str, &i, 0);
	new_str_fill(&result, data);
	return (result);
}

char	*get_env(char *str)
{
	size_t	len;
	char	**env;
	char	*new_str;

	env = g_glb.env;
	new_str = ft_strjoin(str, "=");
	len = ft_strlen(new_str);
	while (*env)
	{
		if (!ft_strncmp(*env, new_str, len))
		{
			free(new_str);
			return (split_env2(*env));
		}
		env++;
	}
	free(new_str);
	return (ft_calloc(sizeof(char *), 1));
}
