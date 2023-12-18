/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatihsoymaz <fatihsoymaz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 01:29:49 by fsoymaz           #+#    #+#             */
/*   Updated: 2023/10/03 23:41:16 by fatihsoymaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	put_char(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		write(STDOUT_FILENO, &(input[i]), 1);
		i++;
	}
}

int	check_tire_en(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == '-')
			flag++;
		i++;
	}
	i = 0;
	while (str[i])
	{
		if ((str[i] != '-' && str[i] != 'n') || flag != 1)
			return (0);
		i++;
	}
	return (1);
}

int	skip_flag(t_execute *str)
{
	int	i;

	i = 0;
	while (str)
	{
		if (ft_strcmp(str->execute, "-n") && check_tire_en(str->execute))
		{
			i++;
			if (str->next)
			{
				if (str->next->execute)
					str = str->next;
				else
					break ;
			}
			else
				break ;
		}
		else
			break ;
	}
	return (i);
}

void	builtin_echo(t_execute *execute, int flag)
{
	int	i;

	if (execute->next)
		if (ft_strlen(execute->next->execute) > 1)
			flag = skip_flag(execute->next);
	i = flag;
	while (i--)
		execute = execute->next;
	execute = execute->next;
	while (execute)
	{
		put_char(execute->execute);
		if (execute->next)
			write(STDOUT_FILENO, " ", 1);
		execute = execute->next;
	}
	if (!flag)
		write(STDOUT_FILENO, "\n", 1);
	if (!is_parent())
		exit(EXIT_SUCCESS);
}
