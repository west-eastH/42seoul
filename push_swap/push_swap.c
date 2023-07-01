/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 03:59:46 by dongseo           #+#    #+#             */
/*   Updated: 2023/07/01 18:03:42 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_three_num(int a, int b, int c, t_stack *stack)
{
	if (a < b && b < c)
	{
		swap(stack, 1);
		rev_rotate(stack, 1);
	}
	else if (a < c && c < b)
		rev_rotate(stack, 1);
	else if (b < a && a < c)
		rotate(stack, 1);
	else if (c < a && a < b)
	{
		rev_rotate(stack, 1);
		swap(stack, 1);
	}
	else if (b < c && c < a)
		swap(stack, 1);
}

void	sort_three(t_stack *stack)
{
	int	a;
	int	b;
	int	c;

	if (stack->size == 1)
		return ;
	if (stack->size == 2)
	{
		if (stack->head->next->data < stack->tail->pre->data)
			rotate(stack, 1);
		return ;
	}
	a = stack->head->next->data;
	b = stack->head->next->next->data;
	c = stack->head->next->next->next->data;
	sort_three_num(a, b, c, stack);
}

void	greedy(t_stack *stack_a, t_stack *stack_b)
{
	int		min_num;
	t_node	*cur;

	min_num = find_min(stack_a, stack_b);
	cur = stack_b->tail->pre;
	while (cur != stack_b->head)
	{
		if (cur->data == min_num)
		{
			push_b_to_a(stack_a, stack_b, cur);
			break ;
		}
		cur = cur->pre;
	}
}

void	push_swap(t_stack *stack_a, t_stack *stack_b)
{
	if (is_sort(stack_a))
		return ;
	if (stack_a->size > 3)
	{
		if (stack_a->size > 4)
			push_stack(stack_b, stack_a, 2);
		push_stack(stack_b, stack_a, 2);
	}
	push_a_to_b(stack_a, stack_b);
	sort_three(stack_a);
	while (stack_b->size)
		greedy(stack_a, stack_b);
	check_ra(stack_a);
}

int	main(int argc, char *argv[])
{
	t_stack	*stack_a;
	t_stack	*stack_b;

	stack_a = (t_stack *)malloc(sizeof(t_stack));
	stack_b = (t_stack *)malloc(sizeof(t_stack));
	if (stack_init(argc, argv, stack_a, stack_b))
	{
		ft_printf("Error\n");
		exit(1);
	}
	push_swap(stack_a, stack_b);
	return (0);
}
