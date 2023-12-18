/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatihsoymaz <fatihsoymaz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 01:29:35 by fsoymaz           #+#    #+#             */
/*   Updated: 2023/10/03 22:40:14 by fatihsoymaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	change_oldpwd(char **env, char *old_pwd)
{
	int		i;
	char	*new_env;

	i = 0;
	while (env[i])
	{
		if (strncmp(env[i], "OLDPWD=", 7) == 0)
		{
			new_env = malloc(strlen(old_pwd) + 8);
			if (new_env)
			{
				strcpy(new_env, "OLDPWD=");
				strcat(new_env, old_pwd);
				free(old_pwd);
				free(env[i]);
				env[i] = new_env;
			}
			break ;
		}
		i++;
	}
}

char	*check_tilde(char *str)
{
	if (!ft_strlen(str) || *str != '~' || !getenv("HOME"))
		return (ft_strdup(str));
	str++;
	return (ft_strjoin(getenv("HOME"), str));
}

void	change_pwd(char **env, char *new_pwd)
{
	int		i;
	char	*new_env;

	i = 0;
	while (env[i])
	{
		if (strncmp(env[i], "PWD=", 4) == 0)
		{
			new_env = malloc(strlen(new_pwd) + 5);
			if (new_env)
			{
				strcpy(new_env, "PWD=");
				strcat(new_env, new_pwd);
				free(new_pwd);
				free(env[i]);
				env[i] = new_env;
			}
			break ;
		}
		i++;
	}
}

void	change_pwd_and_oldpwd(void)
{
	change_oldpwd(g_glb.env, get_env("PWD"));
	change_pwd(g_glb.env, getcwd(NULL, 0));
}

void	builtin_cd(t_execute *execute)
{
	char	*home;
	char	*tmp;

	if (execute->next != 0)
	{
		tmp = check_tilde(execute->next->execute);
		change_directory(tmp);
		free(tmp);
	}
	else
	{
		home = getenv("HOME");
		if (home && *home)
			change_directory(home);
	}
	change_pwd_and_oldpwd();
	if (!is_parent())
		exit(errno);
}
