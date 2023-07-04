/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_num.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 17:59:09 by dongseo           #+#    #+#             */
/*   Updated: 2023/07/01 18:27:34 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	set_mm_ra(t_stack *stack_a)
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
	if (temp2 == stack_a->head)
		ra_cnt = 0;
	return (ra_cnt);
}

void	set_ra_cnt(t_stack *stack_a, t_stack *stack_b)
{
	t_node	*temp1;
	t_node	*temp2;
	t_node	*cur;
	int		cnt;

	cur = stack_b->tail->pre;
	while (cur != stack_b->head)
	{
		cnt = 0;
		temp1 = stack_a->head->next;
		temp2 = stack_a->tail->pre;
		while (temp2 != stack_a->head && cnt++ != -1)
		{
			if (cur->data > temp1->data && cur->data < temp2->data)
			{
				cur->ra_cnt = cnt -1;
				break ;
			}
			temp1 = temp2;
			temp2 = temp2->pre;
		}
		if (temp2 == stack_a->head)
			cur->ra_cnt = set_mm_ra(stack_a);
		cur = cur->pre;
	}
}

void	set_rb_cnt(t_stack *stack_b)
{
	t_node	*cur;
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

int	set_min_cnt(int *min_cnt, t_node *cur, int flag, int size)
{
	if (flag == 1)
		*min_cnt = cur->ra_cnt + cur->rb_cnt;
	else if (flag == 2)
		*min_cnt = size - cur->ra_cnt + cur->rb_cnt;
	else if (flag == 3)
		*min_cnt = cur->ra_cnt + size - cur->rb_cnt;
	else
		*min_cnt = size - cur->ra_cnt - cur->rb_cnt;
	cur->flag = flag;
	return (cur->data);
}

int	find_min(t_stack *stack_a, t_stack *stack_b)
{
	int		min_cnt;
	int		result;
	t_node	*cur;

	cur = stack_b->head->next;
	min_cnt = 999999;
	set_ra_cnt(stack_a, stack_b);
	set_rb_cnt(stack_b);
	while (cur != stack_b->tail)
	{
		if (cur->ra_cnt + cur->rb_cnt < min_cnt)
			result = set_min_cnt(&min_cnt, cur, 1, stack_a->size);
		if (stack_a->size - cur->ra_cnt + cur->rb_cnt < min_cnt)
			result = set_min_cnt(&min_cnt, cur, 2, stack_a->size);
		if (cur->ra_cnt + stack_b->size - cur->rb_cnt < min_cnt)
			result = set_min_cnt(&min_cnt, cur, 3, stack_b->size);
		if (stack_a->size - cur->ra_cnt + stack_b->size - cur->rb_cnt < min_cnt)
			result = set_min_cnt(&min_cnt, cur, 4,
					stack_a->size + stack_b->size);
		cur = cur->next;
	}
	return (result);
}
