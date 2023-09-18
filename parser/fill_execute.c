/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoymaz <fsoymaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 01:44:34 by fsoymaz           #+#    #+#             */
/*   Updated: 2023/07/30 17:53:40 by fsoymaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	prev_type(enum e_token type)
{
	if (type == IN_RED || type == OUT_RED || type == APPEND || type == HEREDOC)
		return (1);
	return (0);
}

t_execute	*lst_new_elem_execute(char *value)
{
	t_execute	*new_elem;

	new_elem = (t_execute *)malloc(sizeof(t_execute));
	if (!new_elem)
		return (0);
	new_elem->execute = value;
	new_elem->next = 0;
	return (new_elem);
}

t_execute	*lst_last_execute(t_execute *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
		return (lst);
	}
	return (0);
}

void	lst_add_back_execute(t_execute **lst, t_execute *new_node)
{
	t_execute	*tmp;

	if (lst)
	{
		if (*lst == 0)
			*lst = new_node;
		else
		{
			tmp = lst_last_execute(*lst);
			tmp->next = new_node;
		}
	}
}

t_execute	*fill_execute(t_token *token, t_execute **execute)
{
	t_execute	*new_execute;

	if (token->type == WORD && token->prev == 0)
	{
		new_execute = lst_new_elem_execute(token->str);
		lst_add_back_execute(execute, new_execute);
	}
	else if (token->type == WORD && prev_type(token->prev->type) == 0)
	{
		new_execute = lst_new_elem_execute(token->str);
		lst_add_back_execute(execute, new_execute);
	}
	return (*execute);
}
