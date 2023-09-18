/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoymaz <fsoymaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 01:31:59 by fsoymaz           #+#    #+#             */
/*   Updated: 2023/07/25 01:32:09 by fsoymaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	remove_env(char *del)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	while (g_glb.env[i])
		i++;
	new_env = (char **)malloc(sizeof(char *) * i);
	i = 0;
	while (g_glb.env[i])
	{
		if (ft_strncmp(g_glb.env[i], del, ft_strlen(del)))
		{
			new_env[j] = ft_strdup(g_glb.env[i]);
			j++;
		}
		i++;
	}
	new_env[j] = 0;
	free_env();
	g_glb.env = new_env;
}

void	builtin_unset(t_execute *execute)
{
	execute = execute->next;
	while (execute)
	{
		remove_env(execute->execute);
		execute = execute->next;
	}
	fill_paths();
	g_glb.erorno = 0;
}
