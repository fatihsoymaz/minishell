/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoymaz <fsoymaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 01:44:54 by fsoymaz           #+#    #+#             */
/*   Updated: 2023/09/16 13:39:52 by fsoymaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

t_redirection	*lst_new_elem_redirect(enum e_token type, char *value)
{
	t_redirection	*new_elem;

	new_elem = (t_redirection *)malloc(sizeof(t_redirection));
	if (!new_elem)
		return (0);
	new_elem->type = type;
	new_elem->redirect = value;
	new_elem->next = 0;
	return (new_elem);
}

t_redirection	*lst_last_redirect(t_redirection *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
		return (lst);
	}
	return (0);
}

void	lst_add_back_redirect(t_redirection **lst, t_redirection *new_node)
{
	t_redirection	*tmp;

	if (lst)
	{
		if (*lst == 0)
			*lst = new_node;
		else
		{
			tmp = lst_last_redirect(*lst);
			tmp->next = new_node;
		}
	}
}

t_redirection	*fill_redirect(t_token *tokens, t_redirection **redirects)
{
	t_redirection	*new_redirect;

	if (tokens->type == OUT_RED)
	{
		new_redirect = lst_new_elem_redirect(OUT_RED, tokens->next->str);
		lst_add_back_redirect(redirects, new_redirect);
	}
	else if (tokens->type == IN_RED)
	{
		new_redirect = lst_new_elem_redirect(IN_RED, tokens->next->str);
		lst_add_back_redirect(redirects, new_redirect);
	}
	else if (tokens->type == APPEND)
	{
		new_redirect = lst_new_elem_redirect(APPEND, tokens->next->str);
		lst_add_back_redirect(redirects, new_redirect);
	}
	else if (tokens->type == HEREDOC)
	{
		new_redirect = lst_new_elem_redirect(HEREDOC, tokens->next->str);
		lst_add_back_redirect(redirects, new_redirect);
	}
	return (*redirects);
}
