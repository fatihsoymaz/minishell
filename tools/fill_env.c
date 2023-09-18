/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoymaz <fsoymaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 01:51:04 by fsoymaz           #+#    #+#             */
/*   Updated: 2023/07/30 11:11:14 by fsoymaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

char	*split_env(char *str)
{
	while (*str != '=')
		str++;
	str++;
	return (ft_strdup(str));
}

char	*get_env_key(char *str)
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
			return (split_env(*env));
		}
		env++;
	}
	free(new_str);
	return (ft_calloc(sizeof(char *), 1));
}

void	free_paths(char **paths)
{
	size_t	i;

	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
}

void	fill_paths(void)
{
	char	*path;

	if (g_glb.paths)
		free_paths(g_glb.paths);
	path = get_env_key("PATH");
	if (!(*path))
		g_glb.paths = NULL;
	else
		g_glb.paths = ft_split(path, ':');
	free(path);
}

void	fill_env(char **env)
{
	size_t	i;
	size_t	len;
	char	**tmp;

	tmp = env;
	while (*tmp)
		tmp++;
	len = tmp - env;
	g_glb.env = ft_calloc(sizeof(char **), len + 1);
	i = -1;
	while (++i < len)
		g_glb.env[i] = ft_strdup(env[i]);
	g_glb.env[i] = NULL;
}
