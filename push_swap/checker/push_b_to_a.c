/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_b_to_a.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 21:52:32 by dongseo           #+#    #+#             */
/*   Updated: 2023/07/01 17:59:48 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rotate_a(t_stack *stack_a, t_stack *stack_b, int cnt_a, int cnt_b)
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
	push_stack(stack_a, stack_b, 1);
}

void	rotate_b(t_stack *stack_a, t_stack *stack_b, int cnt_a, int cnt_b)
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
	push_stack(stack_a, stack_b, 1);
}

void	rotate_c(t_stack *stack_a, t_stack *stack_b, int cnt_a, int cnt_b)
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
	push_stack(stack_a, stack_b, 1);
}

void	rotate_d(t_stack *stack_a, t_stack *stack_b, int cnt_a, int cnt_b)
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
	push_stack(stack_a, stack_b, 1);
}

void	push_b_to_a(t_stack *stack_a, t_stack *stack_b, t_node *cur)
{
	if (cur->flag == 1)
		rotate_a(stack_a, stack_b, cur->ra_cnt, cur->rb_cnt);
	else if (cur->flag == 2)
		rotate_b(stack_a, stack_b, stack_a ->size - cur->ra_cnt, cur->rb_cnt);
	else if (cur->flag == 3)
		rotate_c(stack_a, stack_b, cur->ra_cnt, stack_b ->size - cur->rb_cnt);
	else
		rotate_d(stack_a, stack_b,
			stack_a ->size - cur->ra_cnt, stack_b ->size - cur->rb_cnt);
}
