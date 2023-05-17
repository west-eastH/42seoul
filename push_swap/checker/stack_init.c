/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:46:21 by dongseo           #+#    #+#             */
/*   Updated: 2023/05/17 18:03:29 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int	stack_init(int argc, char *argv[], t_stack *stack_a, t_stack *stack_b)
{
	size_t	i;
	int		data;

	if (is_int(argc, argv) || is_dup(argc, argv)
		|| init(stack_a) || init(stack_b))
		return (1);
	i = argc - 1;
	while (i > 0)
	{
		data = ft_atoi(argv[i]);
		if (push_back(stack_a, data))
			return (1);
		i--;
	}
	return (0);
}

int	check_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			if (((i == 0 && str[i] == '-') || (i == 0 && str[i] == '+'))
				&& str[i + 1] > '0' && str[i + 1] < '9')
			{
				i++;
				continue ;
			}
			return (1);
		}
		i++;
	}
	return (0);
}

int	is_int(int argc, char *argv[])
{
	int	i;
	int	data;

	i = 1;
	if (argc == 1)
		return (1);
	while (i < argc)
	{
		if (check_sign(argv[i]))
			return (1);
		data = ft_atoi(argv[i]);
		if (data < -2147483648 || data > 2147483647)
			return (1);
		i++;
	}
	return (0);
}

int	is_dup(int argc, char *argv[])
{
	int	i;
	int	j;
	int	temp1;
	int	temp2;

	i = 1;
	while (i < argc)
	{
		j = i + 1;
		while (j < argc)
		{
			temp1 = ft_atoi(argv[i]);
			temp2 = ft_atoi(argv[j]);
			if (temp1 == temp2)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	init(t_stack *stack)
{
	stack->head = (t_node *)malloc(sizeof(t_node));
	stack->tail = (t_node *)malloc(sizeof(t_node));
	stack->size = 0;
	stack->head->data = 0;
	stack->head->rank = 0;
	stack->head->pre = stack->head;
	stack->head->next = stack->tail;
	stack->tail->data = 0;
	stack->tail->rank = 0;
	stack->tail->pre = stack->head;
	stack->tail->next = stack->tail;
	return (0);
}
