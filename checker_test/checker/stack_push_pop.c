/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_push_pop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:57:01 by dongseo           #+#    #+#             */
/*   Updated: 2023/05/17 18:11:18 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int	push_back(t_stack *stack, int data)
{
	t_node	*temp;
	t_node	*tail_node;
	t_node	*cur;

	temp = (t_node *)malloc(sizeof(t_node));
	temp->data = data;
	cur = stack->head->next;
	temp->rank = 1;
	while (cur != stack->tail)
	{
		if (cur->data > data)
			temp->rank++;
		else
			cur->rank++;
		cur = cur->next;
	}
	tail_node = stack->tail;
	tail_node->pre->next = temp;
	temp->pre = tail_node->pre;
	tail_node->pre = temp;
	temp->next = tail_node;
	stack->size++;
	return (0);
}

int	push_front(t_stack *stack, int data)
{
	t_node	*temp;
	t_node	*head_node;
	t_node	*cur;

	temp = (t_node *)malloc(sizeof(t_node));
	temp->data = data;
	cur = stack->head->next;
	temp->rank = 1;
	while (cur != stack->tail)
	{
		if (cur->data > data)
			temp->rank++;
		else
			cur->rank++;
		cur = cur->next;
	}
	head_node = stack->head;
	temp->next = head_node->next;
	head_node->next->pre = temp;
	head_node->next = temp;
	temp->pre = head_node;
	stack->size++;
	return (0);
}

int	pop_last(t_stack *stack)
{
	t_node	*temp;
	int		result;
	t_node	*cur;

	cur = stack->head->next;
	temp = stack->tail->pre;
	result = temp->data;
	temp->pre->next = temp->next;
	temp->next->pre = temp->pre;
	while (cur != stack->tail)
	{
		if (cur->data < result)
			cur->rank--;
		cur = cur->next;
	}
	free(temp);
	temp = 0;
	stack->size--;
	return (result);
}

int	pop_first(t_stack *stack)
{
	t_node	*temp;
	int		result;
	t_node	*cur;

	cur = stack->head->next;
	temp = stack->head->next;
	result = temp->data;
	temp->pre->next = temp->next;
	temp->next->pre = temp->pre;
	while (cur != stack->tail)
	{
		if (cur->data < result)
			cur->rank--;
		cur = cur->next;
	}
	free(temp);
	temp = 0;
	stack->size--;
	return (result);
}

void	push_stack(t_stack *dest, t_stack *src)
{
	if (src->size == 0)
		return ;
	push_back(dest, pop_last(src));
}
