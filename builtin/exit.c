/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoymaz <fsoymaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 01:30:41 by fsoymaz           #+#    #+#             */
/*   Updated: 2023/07/25 01:30:52 by fsoymaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	ft_get_arg_count(t_execute *execute)
{
	int	i;

	i = 0;
	while (execute)
	{
		execute = execute->next;
		i++;
	}
	return (i);
}

int	ft_isnumber_with_sign(char *arg)
{
	while (*arg)
	{
		if ((*arg >= '0' && *arg <= '9') || *arg == '+' || *arg == '-')
			arg++;
		else
			return (0);
	}
	return (1);
}

void	builtin_exit(t_execute *execute)
{
	if (ft_get_arg_count(execute) == 1)
	{
		printf("exit\n");
		exit(errno);
	}
	else
	{
		if (ft_isnumber_with_sign(execute->next->execute))
		{
			if (ft_get_arg_count(execute) > 2)
			{
				write(2, "exit\nminishell: exit: too many arguments\n", 41);
				errno = 1;
				return ;
			}
			printf("exit\n");
			exit(ft_atoi(execute->next->execute) % 256);
		}
		write(2, "exit\nminishell: exit: numeric argument required\n", 48);
		exit(-1 % 256);
	}
}
