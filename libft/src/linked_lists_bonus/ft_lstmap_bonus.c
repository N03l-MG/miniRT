/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:37:30 by nmonzon           #+#    #+#             */
/*   Updated: 2024/11/25 16:43:32 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*node;
	t_list	*last;
	void	*modified_content;

	new = NULL;
	while (lst)
	{
		modified_content = f(lst->content);
		node = ft_lstnew(modified_content);
		if (!node)
		{
			if (del)
				del(modified_content);
			ft_lstclear(&new, del);
			return (NULL);
		}
		if (!new)
			new = node;
		else
			last->next = node;
		last = node;
		lst = lst->next;
	}
	return (new);
}
