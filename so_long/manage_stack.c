/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 10:39:29 by dongseo           #+#    #+#             */
/*   Updated: 2023/07/17 10:39:40 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	push_back(t_stack **stack, int y, int x)
{
	t_stack *cur;
	t_stack *temp;

	cur = (t_stack *)malloc(sizeof(t_stack));
	if (!cur)
		exit(1);
	cur->x = x;
	cur->y = y;
	cur->pre = NULL;
	cur->next = NULL;
	if (*stack == NULL)
	{
		*stack = cur;
		return ;
	}
	temp = *stack;
	while (temp->next)
		temp = temp->next;
	cur->pre = temp;
	temp->next = cur;
}

int is_empty(t_stack *stack)
{
	if (stack == NULL)
		return 1;
	return 0;
}

t_stack *top_stack(t_stack *stack)
{
	t_stack *cur;

	cur = stack;
	while (cur->next)
		cur = cur->next;
	return cur;
}

int	stack_size(t_stack *stack)
{
	t_stack *cur;
	int i;

	if (stack == NULL)
		return 0;
	i = 1;
	cur = stack;
	while(cur->next)
	{
		i++;
		cur = cur->next;
	}
	return i;
}
void	pop_stack(t_stack **stack)
{
	t_stack *cur;
	t_stack *temp;
	if (stack_size(*stack) == 1)
	{
		cur = *stack;
		free(cur);
		*stack = NULL;
		return ;
	}
	cur = *stack;
	while (cur->next)
		cur = cur->next;
	temp = cur;
	cur->pre->next = NULL;
	free(temp);
	temp = NULL;
}

