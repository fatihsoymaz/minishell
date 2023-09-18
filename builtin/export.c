/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatihsoymaz <fatihsoymaz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 01:31:05 by fsoymaz           #+#    #+#             */
/*   Updated: 2023/09/17 11:59:52 by fatihsoymaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

char	*get_var_name(char *var)
{
	char	*name;
	char	*eq_pos;

	name = ft_strdup(var);
	if (name == 0)
	{
		return (0);
	}
	eq_pos = ft_strchr(name, '=');
	if (eq_pos != 0)
	{
		*eq_pos = '\0';
	}
	return (name);
}

int	export_no_value_child(char *str, char *tmp, int *i)
{
	if (strcmp_while(tmp, str) != -999)
	{
		*i = *i + 1;
		free(tmp);
		return (1);
	}
	return (0);
}

void	export_no_value(char *str)
{
	char	**env;
	int		i;
	char	*tmp;
	char	*tmp2;

	env = g_glb.env;
	i = 0;
	while (env[i])
	{
		tmp = get_var_name(env[i]);
		if (export_no_value_child(str, tmp, &i))
			continue ;
		tmp2 = env[i];
		env[i] = ft_strdup(str);
		free(tmp2);
		free(tmp);
		break ;
	}
	add_env(str);
}

void	builtin_export_child(t_execute *execute)
{
	int		pos;
	char	*tmp;

	pos = env_position(execute->execute);
	if (pos != -1)
	{
		tmp = g_glb.env[pos];
		g_glb.env[pos] = ft_strdup(execute->execute);
		free(tmp);
	}
	else
		add_env(execute->execute);
}

void	builtin_export(t_execute *execute)
{
	int	check;

	execute = execute->next;
	while (execute)
	{
		check = control_env(execute->execute);
		if (check == 1)
			builtin_export_child(execute);
		else if (check == -1)
			export_no_value(execute->execute);
		else if (check == 0)
		{
			printf("minishell: export: `%s': not a valid identifier\n",
				execute->execute);
			g_glb.erorno = 1;
			return ;
		}
		execute = execute->next;
	}
	fill_paths();
	g_glb.erorno = 0;
}
