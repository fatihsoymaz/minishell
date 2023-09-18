/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actuation_cmd2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoymaz <fsoymaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 01:38:10 by fsoymaz           #+#    #+#             */
/*   Updated: 2023/09/16 13:55:46 by fsoymaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

char	**get_arg_fill(t_execute *execute)
{
	char	**args;
	int		i;
	int		arg_count;

	i = 1;
	arg_count = arg_count_ex(execute);
	args = (char **)malloc(sizeof(char *) * (arg_count + 1));
	args[0] = ft_strdup(execute->execute);
	execute = execute->next;
	while (i < arg_count && execute)
	{
		args[i] = ft_strdup(execute->execute);
		execute = execute->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}

void	actuation_cmd(t_command *cmd)
{
	pid_t	pid;
	char	*path;
	char	**args;

	pid = fork();
	if (pid == 0)
	{
		g_glb.parent_pid = 0;
		cmd_route(cmd);
		start_builtin(cmd->execute);
		path = get_path(cmd->execute->execute);
		args = get_arg_fill(cmd->execute);
		execve(path, args, g_glb.env);
		command_err(cmd->execute->execute);
		exit(errno);
	}
	else
		cmd->pid = pid;
}
