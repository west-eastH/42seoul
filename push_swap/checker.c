/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:41:50 by dongseo           #+#    #+#             */
/*   Updated: 2023/05/16 19:58:58 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "./get_next_line/get_next_line.h"
#include "./libft/libft.h"
#include "checker.h"

int	is_int(int argc, char *argv[])
{
	int	i;
	int	j;
	int	data;

	i = 1;
	if (argc == 1)
		return 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return 1;
			j++;
		}
		data = ft_atoi(argv[i]);
		if (data < -2147483648 || data > 2147483647)
			return 1;
		i++;
	}
	return 0;
}

int	is_dup(int argc, char *argv[])
{
	int	i;
	int	j;
	int		temp1;
	int		temp2;

	i = 1;
	while (i < argc)
	{
		j = i + 1;
		while (j < argc)
		{
			temp1 = ft_atoi(argv[i]);
			temp2 = ft_atoi(argv[j]);
			if (temp1 == temp2)
				return 1;
			j++;
		}
		i++;
	}
	return 0;
}

int	init(t_stack *ft_stack)
{
	ft_stack->head = (t_node *)malloc(sizeof(t_node));
	ft_stack->tail = (t_node *)malloc(sizeof(t_node));
	ft_stack->size = 0;
	ft_stack->head->data = 0;
	ft_stack->head->rank = 0;
	ft_stack->head->pre = ft_stack->head;
	ft_stack->head->next = ft_stack->tail;
	ft_stack->tail->data = 0;
	ft_stack->tail->rank = 0;
	ft_stack->tail->pre = ft_stack->head;
	ft_stack->tail->next = ft_stack->tail;
	return 0;
}

int	push_back(t_stack *ft_stack, int data)
{
	t_node	*temp;
	t_node	*tail_node;
	t_node	*cur;

	temp = (t_node *)malloc(sizeof(t_node));
	temp->data = data;
	cur = ft_stack->head->next;
	temp->rank = 1;
	while (cur != ft_stack->tail)
	{
		if (cur->data > data)
			temp->rank++;
		else
			cur->rank++;
		cur = cur->next;
	}
	tail_node = ft_stack->tail;
	tail_node->pre->next = temp;
	temp->pre = tail_node->pre;
	tail_node->pre = temp;
	temp->next = tail_node;
	ft_stack->size++;
	return 0;
}

int push_front(t_stack *stack, int data)
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
	return 0;
}

int	stack_init(int argc, char *argv[], t_stack *stack_a, t_stack *stack_b)
{
	size_t	i;
	int		data;

	if (is_int(argc, argv) || is_dup(argc, argv)
		|| init(stack_a) || init(stack_b))
		return 1;
	i = argc - 1;
	while (i > 0)
	{
		data = ft_atoi(argv[i]);
		if (push_back(stack_a, data))
			return 1;
		i--;
	}
	return 0;
}

void print_all(t_stack *ft_stack)
{
	t_node *p;
	p = ft_stack->tail->pre;
	while (p->pre != ft_stack->head)
	{
		printf("%d  %d\n", p->data, p->rank);
		p = p->pre;
	}
	printf("%d  %d\n", p->data, p->rank);
}

void swap(t_stack *stack)
{
	t_node *top;
	t_node *temp;

	if (stack->size <= 1)
		return ;
	top = stack->tail->pre;
	temp = top->pre;
	temp->pre->next = top;
	temp->next = top->next;
	top->pre = temp->pre;
	temp->next->pre = temp;
	top->next = temp;
	temp->pre = top;
}

int is_empty(t_stack *stack)
{
	if (stack->size == 0)
		return 1;
	return 0;
}
int delete_last(t_stack *stack)
{
	t_node *temp;
	int result;
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
	return result;
}
int delete_first(t_stack *stack)
{
	t_node *temp;
	int result;
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
	return result;
}

void push_stack(t_stack *dest, t_stack *src)
{
	if (src->size == 0)
		return ;
	push_back(dest, delete_last(src));
}
void rotate(t_stack *stack)
{
	if (stack->size < 2)
		return ;
	push_back(stack, delete_first(stack));
}

void rev_rotate(t_stack *stack)
{
	if (stack->size < 2)
		return ;
	push_front(stack, delete_last(stack));
}

void	set_rank(t_stack *stack)
{
	t_node	*cur;
	cur = stack->head->next;
}

int checker(t_stack *stack_a, t_stack *stack_b)
{
	t_node	*cur;

	if (stack_b->size != 0)
		return 1;
	cur = stack_a->head->next;
	while (cur != stack_a->tail)
	{
		if (cur->next == stack_a->tail)
			break ;
		if (cur->data < cur->next->data)
			return 1;
		cur = cur->next;
	}
	return 0;
}

int main(int argc, char *argv[])
{
	char *test;
	t_stack *stack_a;
	t_stack *stack_b;

	stack_a = (t_stack *)malloc(sizeof(t_stack));
	stack_b = (t_stack *)malloc(sizeof(t_stack));
	if (stack_init(argc, argv, stack_a, stack_b))
	{
		printf("Erorr\n");
		return 0;
	}
	printf("stack_a list\n");
	print_all(stack_a);
	printf("stack_b list\n");
	print_all(stack_b);
	test = get_next_line(0);
	while (test)
	{
		if (ft_strncmp(test, "sa", ft_strlen(test) - 1) == 0)
			swap(stack_a);
		else if (ft_strncmp(test, "sb", ft_strlen(test) - 1) == 0)
			swap(stack_b);
		else if (ft_strncmp(test, "ss", ft_strlen(test) - 1) == 0)
		{
			swap(stack_a);
			swap(stack_b);
		}
		else if (ft_strncmp(test, "pa", ft_strlen(test) - 1) == 0)
			push_stack(stack_a, stack_b);
		else if (ft_strncmp(test, "pb", ft_strlen(test) - 1) == 0)
			push_stack(stack_b, stack_a);
		else if (ft_strncmp(test, "ra", ft_strlen(test) - 1) == 0)
			rotate(stack_a);
		else if (ft_strncmp(test, "rb", ft_strlen(test) - 1) == 0)
			rotate(stack_b);
		else if (ft_strncmp(test, "rr", ft_strlen(test) - 1) == 0)
		{
			rotate(stack_a);
			rotate(stack_b);
		}
		else if (ft_strncmp(test, "rra", ft_strlen(test) - 1) == 0)
			rev_rotate(stack_a);
		else if (ft_strncmp(test, "rrb", ft_strlen(test) - 1) == 0)
			rev_rotate(stack_b);
		else if (ft_strncmp(test, "rrr", ft_strlen(test) - 1) == 0)
		{
			rev_rotate(stack_a);
			rev_rotate(stack_b);
		}
		printf("stack_a list\n");
		print_all(stack_a);
		printf("stack_b list\n");
		print_all(stack_b);
		free(test);
		test = get_next_line(0);
	}
	if (checker(stack_a, stack_b))
		printf("KO\n");
	else
		printf("OK\n");
	return 0;
}
