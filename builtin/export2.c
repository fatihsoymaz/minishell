/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoymaz <fsoymaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 01:31:26 by fsoymaz           #+#    #+#             */
/*   Updated: 2023/07/25 01:31:36 by fsoymaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	add_env(char *str)
{
	int		i;
	char	**env;
	char	**new_env;

	i = 0;
	env = g_glb.env;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = ft_strdup(str);
	new_env[i + 1] = 0;
	free_env();
	g_glb.env = new_env;
}

int	env_position(char *str)
{
	int		i;
	char	**env;
	char	*tmp;
	char	*tmp2;

	i = 0;
	env = g_glb.env;
	while (env[i])
	{
		tmp = get_var_name(env[i]);
		tmp2 = get_var_name(str);
		if (strcmp_while(tmp, tmp2) == -999)
		{
			free(tmp);
			free(tmp2);
			return (i);
		}
		free(tmp);
		free(tmp2);
		i++;
	}
	return (-1);
}

int	strcmp_while(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
		i++;
	}
	if (s1[i] == '\0' && s2[i] == '\0')
	{
		return (-999);
	}
	return (s1[i] - s2[i]);
}

void	free_env(void)
{
	int	i;

	i = 0;
	while (g_glb.env[i])
	{
		free(g_glb.env[i]);
		i++;
	}
	free(g_glb.env);
}
