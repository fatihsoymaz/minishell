/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoymaz <fsoymaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 01:46:41 by fsoymaz           #+#    #+#             */
/*   Updated: 2023/07/25 01:46:51 by fsoymaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	interrupt_here_document(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	exit(errno);
}

void	get_input(char *endline, int *fd)
{
	char	*input;

	signal(SIGINT, interrupt_here_document);
	while (1)
	{
		input = readline("heredoc>> ");
		if (!input || (ft_strcmp(input, endline)
				&& ft_strlen(input) == ft_strlen(endline)))
		{
			free(input);
			exit(1);
		}
		write(fd[1], input, ft_strlen(input));
		write(fd[1], "\n", 1);
		free(input);
	}
}

void	heredoc(int *fd, char *endline)
{
	int	pid;
	int	status;

	if (pipe(fd) < 0)
		return (perror("minishell"));
	pid = fork();
	if (pid == 0)
	{
		get_input(endline, fd);
		close(fd[1]);
	}
	waitpid(pid, &status, 0);
	if (status == 1024)
		g_glb.heredoc = 1;
	else
		g_glb.heredoc = 0;
	close(fd[1]);
}
