/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 03:59:46 by dongseo           #+#    #+#             */
/*   Updated: 2023/06/27 15:26:45 by dongseo          ###   ########.fr       */
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
	int a;
	int b;
	int c;

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

void	push_a_to_b(t_stack *stack_a, t_stack *stack_b)
{
	int	pivot_a;
	int	pivot_b;
	int	count;

	count = stack_a->size;
	if (stack_b->head->next->data > stack_b->tail->pre->data)
	{
		swap(stack_b, 2);
		print_stack(stack_a, stack_b);
	}
	pivot_a = stack_b->head->next->data;
	pivot_b = stack_b->tail->pre->data;
	while (count - 3)
	{
		if (get_top(stack_a) < pivot_b)
		{
			push_stack(stack_b, stack_a, 2);
			print_stack(stack_a, stack_b);
			if (get_top(stack_b) < pivot_a)
			{
				rotate(stack_b, 2);
				print_stack(stack_a, stack_b);
			}
		}
		else
			rotate(stack_a, 1);
		count--;
	}
	while (stack_a->size > 3)
	{
		push_stack(stack_b, stack_a, 2);
		print_stack(stack_a, stack_b);
	}
}

void	push_until_three(t_stack *stack_a, t_stack *stack_b)
{
	if (stack_a->size > 3)
	{
		if (stack_a->size > 4)
		{
			push_stack(stack_b, stack_a, 2);
			print_stack(stack_a, stack_b);
		}
		push_stack(stack_b, stack_a, 2);
		print_stack(stack_a, stack_b);/////////////////////////////
	}
	push_a_to_b(stack_a, stack_b);
	sort_three(stack_a);
}
void	push_swap(t_stack *stack_a, t_stack *stack_b)
{
	push_until_three(stack_a, stack_b);
}

int main(int argc, char *argv[])
{
	//char	*command;
	t_stack	*stack_a;
	t_stack	*stack_b;

	stack_a = (t_stack *)malloc(sizeof(t_stack));
	stack_b = (t_stack *)malloc(sizeof(t_stack));
	if (stack_init(argc, argv, stack_a, stack_b))
	{
		ft_printf("Error\n");
		exit(1);
	}
	print_stack(stack_a, stack_b);
	push_swap(stack_a, stack_b);
	print_stack(stack_a, stack_b);
	check_sort(stack_a, stack_b);
	return 0;
}
