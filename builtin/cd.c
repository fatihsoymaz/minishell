/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoymaz <fsoymaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 01:29:35 by fsoymaz           #+#    #+#             */
/*   Updated: 2023/07/25 01:29:41 by fsoymaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

char	*check_tilde(char *str)
{
	if (!ft_strlen(str) || *str != '~' || !getenv("HOME"))
		return (ft_strdup(str));
	str++;
	return (ft_strjoin(getenv("HOME"), str));
}

void	builtin_cd(t_execute *execute)
{
	char	*home;
	char	*tmp;

	if (execute->next != 0)
	{
		tmp = check_tilde(execute->next->execute);
		if (chdir(tmp) != 0)
		{
			g_glb.erorno = 1;
			perror("minishell ");
		}
		else
			g_glb.erorno = 0;
		free(tmp);
	}
	else
	{
		home = getenv("HOME");
		if (home && *home)
			if (chdir(home))
				perror("minishell ");
		g_glb.erorno = 0;
	}
	if (!is_parent())
		exit(errno);
}
