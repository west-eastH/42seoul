/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 23:57:22 by dongseo           #+#    #+#             */
/*   Updated: 2023/07/07 13:35:54 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	check_ra(t_stack *stack_a)
{
	t_node	*temp1;
	t_node	*temp2;
	int		ra_cnt;

	ra_cnt = 1;
	temp1 = stack_a->tail->pre;
	temp2 = temp1->pre;
	while (temp2 != stack_a->head)
	{
		if (temp1->data > temp2->data)
			break ;
		ra_cnt++;
		temp1 = temp2;
		temp2 = temp2->pre;
	}
	if (ra_cnt == stack_a->size)
		return ;
	if (ra_cnt <= stack_a->size / 2)
		while (ra_cnt--)
			rotate(stack_a, 1);
	else
		while (stack_a->size - ra_cnt++)
			rev_rotate(stack_a, 1);
}

int	is_sort(t_stack *stack)
{
	t_node	*cur;

	cur = stack->tail->pre;
	while (cur != stack->head->next)
	{
		if (cur->data > cur->pre->data)
			return (0);
		cur = cur->pre;
	}
	return (1);
}

int	set_pivot(t_stack *stack_a, int flag)
{
	t_node	*cur;
	t_node	*temp;
	int		idx;

	cur = stack_a->head->next;
	while (cur != stack_a->tail)
	{
		idx = 0;
		temp = stack_a->head->next;
		while (temp != stack_a->tail)
		{
			if (cur->data > temp->data)
				idx++;
			temp = temp->next;
		}
		if (idx == (stack_a->size / 3) * flag)
			return (cur->data);
		cur = cur->next;
	}
	return (0);
}

void	push_sort(t_stack *stack_a, t_stack *stack_b, int p1, int p2)
{
	if (get_top(stack_b) < p1)
	{
		if (get_top(stack_a) > p2)
		{
			rotate(stack_a, 0);
			rotate(stack_b, 0);
			ft_printf("rr\n");
		}
		else
			rotate(stack_b, 2);
	}
}

void	push_a_to_b(t_stack *stack_a, t_stack *stack_b)
{
	int	pivot_a;
	int	pivot_b;
	int	count;

	count = stack_a->size;
	if (stack_b->head->next->data > stack_b->tail->pre->data)
		swap(stack_b, 2);
	pivot_a = set_pivot(stack_a, 1);
	pivot_b = set_pivot(stack_a, 2);
	while (count - 3)
	{
		if (get_top(stack_a) < pivot_b)
		{
			push_stack(stack_b, stack_a, 2);
			push_sort(stack_a, stack_b, pivot_a, pivot_b);
		}
		else
			rotate(stack_a, 1);
		count--;
	}
	while (stack_a->size > 3)
		push_stack(stack_b, stack_a, 2);
}
