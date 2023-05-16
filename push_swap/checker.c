/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:41:50 by dongseo           #+#    #+#             */
/*   Updated: 2023/05/16 16:50:26 by dongseo          ###   ########.fr       */
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

	temp = (t_node *)malloc(sizeof(t_node));
	temp->data = data;
	temp->rank = 1;
	tail_node = ft_stack->tail;
	tail_node->pre->next = temp;
	temp->pre = tail_node->pre;
	tail_node->pre = temp;
	temp->next = tail_node;
	ft_stack->size++;
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
	p = ft_stack->head->next;
	while (p->next != ft_stack->tail)
	{
		printf("%d  ", p->data);
		p = p->next;
	}
	printf("%d\n", p->data);
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

	temp = stack->tail->pre;
	result = temp->data;
	temp->pre->next = temp->next;
	temp->next->pre = temp->pre;
	free(temp);
	temp = 0;
	stack->size--;
	return result;
}

void push_stack(t_stack *dest, t_stack *src)
{
	push_back(dest, delete_last(src));
	
}
void rotate(t_stack *stack)
{
	int data;
	t_node *temp;

	if (stack->size < 2)
		return ;
	temp = stack->head->next;
	data = temp->data;
	stack->head->next = temp->next;
	temp->next->pre = stack->head;
	free(temp);
	temp = 0;
	stack->size--;
	push_back(stack, data);
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
		if (ft_strncmp(test, "sb", ft_strlen(test) - 1) == 0)
			swap(stack_b);
		if (ft_strncmp(test, "ss", ft_strlen(test) - 1) == 0)
		{
			swap(stack_a);
			swap(stack_b);
		}
		if (ft_strncmp(test, "pa", ft_strlen(test) - 1) == 0 && !(is_empty(stack_b)))
			push_stack(stack_a, stack_b);
		if (ft_strncmp(test, "pb", ft_strlen(test) - 1) == 0 && !(is_empty(stack_a)))
			push_stack(stack_b, stack_a);
		if (ft_strncmp(test, "ra", ft_strlen(test) - 1) == 0)
			rotate(stack_a);
		if (ft_strncmp(test, "rb", ft_strlen(test) - 1) == 0)
			rotate(stack_b);
		if (ft_strncmp(test, "rr", ft_strlen(test) - 1) == 0)
		{
			rotate(stack_a);
			rotate(stack_b);
		}
		printf("stack_a list\n");
		print_all(stack_a);
		printf("stack_b list\n");
		print_all(stack_b);
		free(test);
		test = get_next_line(1);
	}
	return 0;
}
