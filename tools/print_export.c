/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoymaz <fsoymaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 01:52:24 by fsoymaz           #+#    #+#             */
/*   Updated: 2023/07/25 01:52:36 by fsoymaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	print_env_vars_child(char **env, int i)
{
	char	*val;
	char	*eq;

	val = env[i];
	eq = ft_strchr(val, '=');
	if (eq != NULL)
	{
		*eq = '\0';
		printf("declare -x %s=\"%s\"\n", val, eq + 1);
		*eq = '=';
	}
	else
		printf("declare -x %s\n", val);
}

void	print_env_vars_child_2(char **env, int i, int j, char *tmp)
{
	if (env[i][0] > env[j][0])
	{
		tmp = env[i];
		env[i] = env[j];
		env[j] = tmp;
	}
}

void	print_env_vars(void)
{
	char	**env;
	int		num_env;
	int		i;
	int		j;
	char	*tmp;

	tmp = NULL;
	env = g_glb.env;
	num_env = 0;
	while (env[num_env] != NULL)
		num_env++;
	i = -1;
	while (++i < num_env)
	{
		j = i;
		while (++j < num_env)
			print_env_vars_child_2(env, i, j, tmp);
		print_env_vars_child(env, i);
	}
	g_glb.erorno = 0;
}
