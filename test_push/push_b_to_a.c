/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_b_to_a.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 21:52:32 by dongseo           #+#    #+#             */
/*   Updated: 2023/06/28 22:06:23 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void rotate_a(t_stack *stack_a, t_stack *stack_b, int cnt_a, int cnt_b)
{
	while (cnt_a && cnt_b)
	{
		rotate(stack_a, 0);
		rotate(stack_b, 0);
		ft_printf("rr\n");
		cnt_a--;
		cnt_b--;
	}
	while (cnt_a)
	{
		rotate(stack_a, 1);
		cnt_a--;
	}
	while (cnt_b)
	{
		rotate(stack_b, 2);
		cnt_b--;
	}
	push_stack(stack_b, stack_a, 1);
}

void rotate_b(t_stack *stack_a, t_stack *stack_b, int cnt_a, int cnt_b)
{
	while (cnt_a)
	{
		rev_rotate(stack_a, 1);
		cnt_a--;
	}
	while (cnt_b)
	{
		rotate(stack_b, 2);
		cnt_b--;
	}
	push_stack(stack_b, stack_a, 1);
}
void rotate_c(t_stack *stack_a, t_stack *stack_b, int cnt_a, int cnt_b)
{
	while (cnt_a)
	{
		rotate(stack_a, 1);
		cnt_a--;
	}
	while (cnt_b)
	{
		rev_rotate(stack_b, 2);
		cnt_b--;
	}
	push_stack(stack_b, stack_a, 1);
}
void rotate_d(t_stack *stack_a, t_stack *stack_b, int cnt_a, int cnt_b)
{
	while (cnt_a && cnt_b)
	{
		rev_rotate(stack_a, 0);
		rev_rotate(stack_b, 0);
		ft_printf("rrr\n");
		cnt_a--;
		cnt_b--;
	}
	while (cnt_a)
	{
		rev_rotate(stack_a, 1);
		cnt_a--;
	}
	while (cnt_b)
	{
		rev_rotate(stack_b, 2);
		cnt_b--;
	}
	push_stack(stack_b, stack_a, 1);
}