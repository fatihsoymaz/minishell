/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoymaz <fsoymaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 01:28:48 by fsoymaz           #+#    #+#             */
/*   Updated: 2023/10/19 00:34:52 by fsoymaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

t_glb	g_glb;

int	init_program(int argc, char **argv, char **env)
{
	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("Error: Wrong number of arguments\n", 2);
		return (1);
	}
	signals_init();
	fill_env(env);
	fill_paths();
	return (0);
}

int	start_shell_child(t_token **tokens)
{
	if (check_pars_error(*tokens))
	{
		free_token(*tokens);
		g_glb.erorno = 258;
		return (1);
	}
	return (0);
}

int	start_shell(char *input, t_token **tokens, t_redirection **redirection,
		t_execute **execute)
{
	int	token_count;

	g_glb.commands = 0;
	*tokens = 0;
	*redirection = 0;
	*execute = 0;
	token_count = tokens_count(input);
	g_glb.token_count = token_count;
	g_glb.heredoc = 0;
	g_glb.cmd_count = 0;
	if (token_count >= 0)
	{
		token_fill(input, tokens);
		if (start_shell_child(tokens))
			return (1);
		dollar_fill(*tokens);
		del_quote(*tokens);
		fill_command(*tokens, &g_glb.commands);
		run_cmd();
		free_token(*tokens);
		free_cmd();
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	char			*input;
	t_token			*tokens;
	t_redirection	*redirection;
	t_execute		*execute;

	if (init_program(argc, argv, env))
		return (0);
	while (1)
	{
		g_glb.parent_pid = 1;
		input = readline("minishell $> ");
		if (!input)
		{
			ft_putstr_fd("exit\n", 1);
			return (0);
		}
		if (ft_strncmp(input, "", ft_strlen(input)) != 0)
			add_history(input);
		if (*input)
			start_shell(input, &tokens, &redirection, &execute);
		free(input);
	}
	return (0);
}
