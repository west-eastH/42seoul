/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 20:11:15 by dongseo           #+#    #+#             */
/*   Updated: 2023/03/25 20:44:59 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*temp;
	int		i;

	i = 0;
	while (lst)
	{
		temp = lst;
		lst = lst->next;
		i++;
	}
	if (i == 0)
		return (0);
	return (temp);
}
