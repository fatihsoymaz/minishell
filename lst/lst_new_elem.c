/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_new_elem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoymaz <fsoymaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 01:43:24 by fsoymaz           #+#    #+#             */
/*   Updated: 2023/07/25 01:43:32 by fsoymaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

t_token	*lst_new_elem_token(enum e_token type, char *value)
{
	t_token	*new_elem;

	new_elem = (t_token *)malloc(sizeof(t_token));
	if (!new_elem)
		return (0);
	new_elem->type = type;
	new_elem->str = value;
	new_elem->next = 0;
	new_elem->prev = 0;
	return (new_elem);
}
