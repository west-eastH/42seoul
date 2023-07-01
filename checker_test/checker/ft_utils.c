/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:39:29 by dongseo           #+#    #+#             */
/*   Updated: 2023/06/21 16:37:10 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	print_stack(t_stack *stack)
{
	t_node	*temp;

	temp = stack->head->next;
	while (temp != stack->tail)
	{

		ft_printf("%d ", temp->data);
		temp = temp->next;
	}
	ft_printf("\n");
}
