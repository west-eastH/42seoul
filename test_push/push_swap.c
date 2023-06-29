/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 03:59:46 by dongseo           #+#    #+#             */
/*   Updated: 2023/06/28 22:20:57 by dongseo          ###   ########.fr       */
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
		//print_stack(stack_a, stack_b);
	}
	pivot_a = stack_b->head->next->data;
	pivot_b = stack_b->tail->pre->data;
	while (count - 3)
	{
		if (get_top(stack_a) < pivot_b)
		{
			push_stack(stack_b, stack_a, 2);
			//print_stack(stack_a, stack_b);
			if (get_top(stack_b) < pivot_a)
			{
				rotate(stack_b, 2);
				//print_stack(stack_a, stack_b);
			}
		}
		else
		{
			rotate(stack_a, 1);
			//print_stack(stack_a, stack_b);	
		}
		count--;
	}
	while (stack_a->size > 3)
	{
		push_stack(stack_b, stack_a, 2);
		//print_stack(stack_a, stack_b);
	}
}

void	push_until_three(t_stack *stack_a, t_stack *stack_b)
{
	if (stack_a->size > 3)
	{
		if (stack_a->size > 4)
		{
			push_stack(stack_b, stack_a, 2);
			//print_stack(stack_a, stack_b);
		}
		push_stack(stack_b, stack_a, 2);
		//print_stack(stack_a, stack_b);/////////////////////////////
	}
	push_a_to_b(stack_a, stack_b);
	sort_three(stack_a);
}

void set_ra_cnt(t_stack *stack_a, t_stack *stack_b)
{
	t_node *temp1;
	t_node *temp2;
	t_node *cur;
	int		cnt;

	cur = stack_b->tail->pre;
	while (cur != stack_b->head)
	{
		cnt = 0;
		temp1 = stack_a->head->next;
		temp2 = stack_a->tail->pre;
		while (temp2 != stack_a->head)
		{
			if (cur->data < temp1->data && cur->data > temp2->data)
			{
				cur->ra_cnt = cnt;
				break ;
			}
			temp1 = temp2;
			temp2 = temp2->pre;
		}
		if (temp2 == stack_a->head)
			cur->ra_cnt = 0;
		cur = cur->pre;
	}
}

void set_rb_cnt(t_stack *stack_b)
{
	t_node *cur;
	int		cnt;

	cnt = 0;
	cur = stack_b->tail->pre;
	while (cur != stack_b->head)
	{
		cur->rb_cnt = cnt;
		cnt++;
		cur = cur->pre;
	}
}

int set_min_cnt(int *min_cnt, t_node *cur, int flag, int size)
{
	if (flag == 1)
		*min_cnt = cur->ra_cnt + cur->rb_cnt;
	else if (flag == 2)
		*min_cnt = size - cur->ra_cnt + cur->rb_cnt;
	else if (flag == 3)
		*min_cnt = cur->ra_cnt + size - cur->ra_cnt;
	else
		*min_cnt = size - cur->ra_cnt + size - cur->rb_cnt;
	cur->flag = flag;
	return (cur->data);
}

int find_min(t_stack *stack_a, t_stack *stack_b)
{
	int	min_cnt;
	int	result;
	t_node	*cur;

	cur = stack_b->tail->pre;
	min_cnt = 999999;
	set_ra_cnt(stack_a, stack_b);
	set_rb_cnt(stack_b);
	while (cur != stack_b->head)
	{
		if (cur->ra_cnt + cur->rb_cnt < min_cnt)
			result = set_min_cnt(&min_cnt, cur, 1, stack_a->size);
		if (stack_a->size - cur->ra_cnt + cur->rb_cnt < min_cnt)
			result = set_min_cnt(&min_cnt, cur, 2, stack_a->size);
		if (cur->ra_cnt + stack_a->size - cur->rb_cnt < min_cnt)
			result = set_min_cnt(&min_cnt, cur, 3, stack_a->size);
		if (stack_a->size - cur->ra_cnt + stack_a->size - cur->rb_cnt < min_cnt)
			result = set_min_cnt(&min_cnt, cur, 4, stack_a->size);
		cur = cur->pre;
	}
	return result;
}

void push_b_to_a(t_stack *stack_a, t_stack *stack_b, t_node *cur)
{
	if (cur->flag == 1)
		rotate_a(stack_a, stack_b, cur->ra_cnt, cur->rb_cnt);
	else if (cur->flag == 2)
		rotate_b(stack_a, stack_b, stack_a ->size - cur->ra_cnt, cur->rb_cnt);
	else if (cur->flag == 3)
		rotate_c(stack_a, stack_b, cur->ra_cnt, stack_a ->size - cur->rb_cnt);
	else
		rotate_d(stack_a, stack_b,
			stack_a ->size - cur->ra_cnt, stack_a ->size - cur->rb_cnt);
}

void greedy(t_stack *stack_a, t_stack *stack_b)
{
	int min_num;
	t_node *cur;

	min_num = find_min(stack_a, stack_b);
	cur = stack_b->tail->pre;
	while (cur != stack_b->head)
	{
		if (cur->data == min_num)
			push_b_to_a(stack_a, stack_b, cur);
		cur = cur->pre;
	}
}

void	push_swap(t_stack *stack_a, t_stack *stack_b)
{
	push_until_three(stack_a, stack_b);
	while (stack_b->size)
		greedy(stack_a, stack_b);
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
