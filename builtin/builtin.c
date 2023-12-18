/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatihsoymaz <fatihsoymaz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 01:29:15 by fsoymaz           #+#    #+#             */
/*   Updated: 2023/10/03 23:33:32 by fatihsoymaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	change_directory(const char *path)
{
	if (chdir(path) != 0)
	{
		g_glb.erorno = 1;
		perror("minishell ");
	}
	else
	{
		g_glb.erorno = 0;
	}
}

int	is_builtin(char *command)
{
	if (ft_strcmp(command, "cd\0") && ft_strlen(command) == 2)
		return (CD);
	else if (ft_strcmp(command, "env\0") && ft_strlen(command) == 3)
		return (ENV);
	else if (ft_strcmp(command, "pwd\0") && ft_strlen(command) == 3)
		return (PWD);
	else if (ft_strcmp(command, "echo\0") && ft_strlen(command) == 4)
		return (ECO);
	else if (ft_strcmp(command, "exit\0") && ft_strlen(command) == 4)
		return (EXIT);
	else if (ft_strcmp(command, "unset\0") && ft_strlen(command) == 5)
		return (UNSET);
	else if (ft_strcmp(command, "export\0") && ft_strlen(command) == 6)
		return (EXPORT);
	return (0);
}

void	start_builtin(t_execute *execute)
{
	int	mode;

	if (!execute)
		return ;
	mode = is_builtin(execute->execute);
	if (mode == CD)
		builtin_cd(execute);
	if (mode == ENV)
		builtin_env();
	if (mode == PWD)
		builtin_pwd();
	if (mode == ECO)
		builtin_echo(execute, 0);
	if (mode == EXIT)
		builtin_exit(execute);
	if (mode == UNSET)
		builtin_unset(execute);
	if (mode == EXPORT)
	{
		if (execute->next == 0)
			print_env_vars();
		else
			builtin_export(execute);
	}
}
