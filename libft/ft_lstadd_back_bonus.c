/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 18:57:06 by dcelsa            #+#    #+#             */
/*   Updated: 2021/10/17 18:57:07 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*begin;

	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	begin = (*lst);
	while (begin->next && new)
		begin = begin->next;
	begin->next = new;
}
