/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_push_pop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:57:01 by dongseo           #+#    #+#             */
/*   Updated: 2023/07/04 15:51:54 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	push_back(t_stack *stack, int data)
{
	t_node	*temp;
	t_node	*tail_node;

	temp = (t_node *)malloc(sizeof(t_node));
	if (!temp)
		return (1);
	temp->data = data;
	temp->ra_cnt = 0;
	temp->rb_cnt = 0;
	temp->flag = -1;
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

	temp = (t_node *)malloc(sizeof(t_node));
	if (!temp)
		return (1);
	temp->data = data;
	temp->ra_cnt = 0;
	temp->rb_cnt = 0;
	temp->flag = -1;
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
	if (stack->head == NULL)
		return (1);
	stack->tail = (t_node *)malloc(sizeof(t_node));
	if (stack->tail == NULL)
	{
		free(stack->head);
		return (1);
	}
	stack->size = 0;
	stack->head->data = 0;
	stack->head->ra_cnt = 0;
	stack->head->rb_cnt = 0;
	stack->head->flag = -1;
	stack->tail->data = 0;
	stack->tail->ra_cnt = 0;
	stack->tail->rb_cnt = 0;
	stack->tail->flag = -1;
	stack->head->pre = stack->head;
	stack->head->next = stack->tail;
	stack->tail->pre = stack->head;
	stack->tail->next = stack->tail;
	return (0);
}
