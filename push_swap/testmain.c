/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testmain.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:41:50 by dongseo           #+#    #+#             */
/*   Updated: 2023/05/15 23:35:18 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "checker.h"


int	ft_atoi(const char *str)
{
	int			i;
	long long	res;
	int			sign;

	sign = 1;
	res = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res *= 10;
		res += str[i] - '0';
		i++;
	}
	return (sign * res);
}


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
	printf("%d", p->data);
}

int main(int argc, char *argv[])
{
	t_stack *stack_a;
	t_stack *stack_b;

	stack_a = (t_stack *)malloc(sizeof(t_stack));
	stack_b = (t_stack *)malloc(sizeof(t_stack));
	stack_init(argc, argv, stack_a, stack_b);
	print_all(stack_a);
	return 0;
}