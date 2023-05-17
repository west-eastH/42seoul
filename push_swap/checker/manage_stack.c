/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_stack.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:50:39 by dongseo           #+#    #+#             */
/*   Updated: 2023/05/17 18:11:18 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	swap(t_stack *stack)
{
	t_node	*top;
	t_node	*temp;

	if (stack->size <= 1)
		return ;
	top = stack->tail->pre;
	temp = top->pre;
	temp->pre->next = top;
	temp->next = top->next;
	top->pre = temp->pre;
	temp->next->pre = temp;
	top->next = temp;
	temp->pre = top;
}

int	is_empty(t_stack *stack)
{
	if (stack->size == 0)
		return (1);
	return (0);
}

void	rotate(t_stack *stack)
{
	if (stack->size < 2)
		return ;
	push_back(stack, pop_first(stack));
}

void	rev_rotate(t_stack *stack)
{
	if (stack->size < 2)
		return ;
	push_front(stack, pop_last(stack));
}

void	set_rank(t_stack *stack)
{
	t_node	*cur;

	cur = stack->head->next;
}
