/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_stack.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 02:10:26 by dongseo           #+#    #+#             */
/*   Updated: 2023/07/01 17:52:56 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap(t_stack *stack, int flag)
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
	if (flag == 1)
		ft_printf("sa\n");
	else if (flag == 2)
		ft_printf("sb\n");
}

void	rotate(t_stack *stack, int flag)
{
	if (stack->size < 2)
		return ;
	push_front(stack, pop_last(stack));
	if (flag == 1)
		ft_printf("ra\n");
	else if (flag == 2)
		ft_printf("rb\n");
}

void	rev_rotate(t_stack *stack, int flag)
{
	if (stack->size < 2)
		return ;
	push_back(stack, pop_first(stack));
	if (flag == 1)
		ft_printf("rra\n");
	else if (flag == 2)
		ft_printf("rrb\n");
}

void	push_stack(t_stack *dest, t_stack *start, int flag)
{
	push_back(dest, pop_last(start));
	if (flag == 1)
		ft_printf("pa\n");
	else if (flag == 2)
		ft_printf("pb\n");
}

int	get_top(t_stack *stack)
{
	t_node	*cur;

	cur = stack->tail->pre;
	return (cur->data);
}
