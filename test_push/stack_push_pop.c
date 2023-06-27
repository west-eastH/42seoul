/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_push_pop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:57:01 by dongseo           #+#    #+#             */
/*   Updated: 2023/06/27 03:43:14 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	push_back(t_stack *stack, int data)
{
	t_node	*temp;
	t_node	*tail_node;
	t_node	*cur;

	temp = (t_node *)malloc(sizeof(t_node));
	if (!temp)
		return (1);
	temp->data = data;
	temp->cnt = 0;
	cur = stack->head->next;
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
	if (!temp)
		return (1);
	temp->data = data;
	temp->cnt = 0;
	cur = stack->head->next;
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

	temp = stack->tail->pre;
	result = temp->data;
	temp->pre->next = temp->next;
	temp->next->pre = temp->pre;
	free(temp);
	temp = 0;
	stack->size--;
	return (result);
}

int	pop_first(t_stack *stack)
{
	t_node	*temp;
	int		result;

	temp = stack->head->next;
	result = temp->data;
	temp->pre->next = temp->next;
	temp->next->pre = temp->pre;
	free(temp);
	temp = 0;
	stack->size--;
	return (result);
}

int	init(t_stack *stack)
{
	stack->head = (t_node *)malloc(sizeof(t_node));
	stack->tail = (t_node *)malloc(sizeof(t_node));
	if (stack->head == NULL || stack->tail == NULL)
		return (1);
	stack->size = 0;
	stack->head->data = 0;
	stack->head->cnt = 0;
	stack->tail->data = 0;
	stack->tail->cnt = 0;
	stack->head->pre = stack->head;
	stack->head->next = stack->tail;
	stack->tail->pre = stack->head;
	stack->tail->next = stack->tail;
	return (0);
}
