/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 23:57:22 by dongseo           #+#    #+#             */
/*   Updated: 2023/06/27 01:20:08 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void print_stack(t_stack *stack_a, t_stack *stack_b)
{
	t_node *cur_a;
	t_node *cur_b;

	cur_a = stack_a->head->next;
	cur_b = stack_b->head->next;
	ft_printf("stack_a : ");
	while (cur_a != stack_a->tail)
	{
		ft_printf("%d  ", cur_a->data);
		cur_a = cur_a->next;
	}
	ft_printf("\n");
	ft_printf("stack_b : ");
	while (cur_b != stack_b->tail)
	{
		ft_printf("%d  ", cur_b->data);
		cur_b = cur_b->next;
	}
	ft_printf("\n");
}

void	check_sort(t_stack *stack_a, t_stack *stack_b)
{
	t_node	*cur;

	if (stack_b->size != 0)
	{
		ft_printf("KO\n");
		return ;
	}
	cur = stack_a->head->next;
	while (cur != stack_a->tail)
	{
		if (cur->next == stack_a->tail)
			break ;
		if (cur->data < cur->next->data)
		{
			ft_printf("KO\n");
			return ;
		}
		cur = cur->next;
	}
	ft_printf("OK\n");
}
