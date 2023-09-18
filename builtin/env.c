/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoymaz <fsoymaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 01:30:22 by fsoymaz           #+#    #+#             */
/*   Updated: 2023/07/27 17:49:14 by fsoymaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	builtin_env(void)
{
	char	**env;

	env = g_glb.env;
	while (*env)
	{
		if (ft_strchr(*env, '='))
			printf("%s\n", *env);
		env++;
	}
	if (!is_parent())
		exit(EXIT_SUCCESS);
	g_glb.erorno = 0;
}

int	control_env(char *str)
{
	char	*key;
	int		i;

	i = 0;
	key = ft_strchr(str, '=');
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		if ((str[i] >= 33 && str[i] <= 47) || (str[i] >= 58 && str[i] <= 64))
			return (0);
		i++;
	}
	if (!key)
		return (-1);
	if (key == str)
		return (0);
	return (1);
}
