/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_add_back.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoymaz <fsoymaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 01:42:43 by fsoymaz           #+#    #+#             */
/*   Updated: 2023/07/25 01:42:52 by fsoymaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	lst_add_back_token(t_token **lst, t_token *new_node, int count)
{
	t_token	*tmp;

	if (lst)
	{
		if (*lst == 0)
			*lst = new_node;
		else
		{
			tmp = lst_last_token(*lst);
			tmp->next = new_node;
			new_node->prev = tmp;
		}
	}
	return (count);
}
