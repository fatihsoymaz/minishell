/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatihsoymaz <fatihsoymaz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 01:40:16 by fsoymaz           #+#    #+#             */
/*   Updated: 2023/09/18 05:49:09 by fatihsoymaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	run_builtin(t_command *cmd)
{
	int	in;
	int	out;

	in = dup(0);
	out = dup(1);
	redirect_inputs(cmd);
	redirect_outputs(cmd);
	start_builtin(cmd->execute);
	dup2(in, 0);
	dup2(out, 1);
	close(in);
	close(out);
}

void	wait_cmd(void)
{
	t_command	*cmd;
	int			child_exit_status;
	int			prev_cmd_ret;

	cmd = g_glb.commands;
	close_all_fd();
	prev_cmd_ret = -1;
	while (cmd != NULL)
	{
		if (cmd->pid != -1)
		{
			waitpid(cmd->pid, &errno, 0);
			if (WIFEXITED(errno))
			{
				child_exit_status = WEXITSTATUS(errno);
				if (child_exit_status == 127)
					g_glb.erorno = 127;
				else if (prev_cmd_ret == 127)
					g_glb.erorno = 0;
				prev_cmd_ret = child_exit_status;
			}
		}
		cmd = cmd->next;
	}
}

void	pipe_fd(t_command *cmd)
{
	int	fd[2];

	while (cmd->next)
	{
		pipe(fd);
		cmd->fd[1] = fd[1];
		cmd->next->fd[0] = fd[0];
		cmd = cmd->next;
	}
}

void	run_cmd(void)
{
	t_command	*cmd;

	cmd = g_glb.commands;
	if (!cmd)
		return ;
	fill_heredoc();
	if (g_glb.heredoc)
		return ;
	if (cmd->execute != 0 && is_builtin(cmd->execute->execute)
		&& g_glb.cmd_count == 1)
	{
		run_builtin(cmd);
		cmd = cmd->next;
	}
	while (cmd)
	{
		actuation_cmd(cmd);
		cmd = cmd->next;
	}
	wait_cmd();
}
