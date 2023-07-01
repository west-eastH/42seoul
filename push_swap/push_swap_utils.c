/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 23:57:22 by dongseo           #+#    #+#             */
/*   Updated: 2023/07/01 18:28:42 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
/* 
void	print_cur(t_node *cur)
{
	ft_printf("data : %d\n", cur->data);
	ft_printf("ra : %d\n", cur->ra_cnt);
	ft_printf("rb : %d\n", cur->rb_cnt);
	ft_printf("flag : %d\n", cur->flag);
	ft_printf("pre-data : %d\n", cur->pre->data);
	ft_printf("next-data : %d\n", cur->next->data);
}

void	print_stack(t_stack *stack_a, t_stack *stack_b)
{
	t_node	*cur_a;
	t_node	*cur_b;

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
 */

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
	if (ra_cnt < stack_a->size / 2)
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

void	push_a_to_b(t_stack *stack_a, t_stack *stack_b)
{
	int	pivot_a;
	int	pivot_b;
	int	count;

	count = stack_a->size;
	if (stack_b->head->next->data > stack_b->tail->pre->data)
		swap(stack_b, 2);
	pivot_a = stack_b->head->next->data;
	pivot_b = stack_b->tail->pre->data;
	while (count - 3)
	{
		if (get_top(stack_a) < pivot_b)
		{
			push_stack(stack_b, stack_a, 2);
			if (get_top(stack_b) < pivot_a)
				rotate(stack_b, 2);
		}
		else
			rotate(stack_a, 1);
		count--;
	}
	while (stack_a->size > 3)
		push_stack(stack_b, stack_a, 2);
}
