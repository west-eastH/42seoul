/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:46:21 by dongseo           #+#    #+#             */
/*   Updated: 2023/06/25 18:07:46 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int	stack_init(int argc, char *argv[], t_stack *stack_a, t_stack *stack_b)
{
	int		i;
	int		j;
	int		data;
	char	**temp;

	if (is_int(argc, argv) || is_dup(argc, argv)
		|| init(stack_a) || init(stack_b))
		return (1);
	i = 1;
	while (i < argc)
	{
		j = 0;
		temp = ft_split(argv[i]);
		while (temp[j])
		{
			data = ft_atoi(temp[j]);
			if (push_front(stack_a, data))
				return (1);
			j++;
		}
		i++;
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
	int		i;
	char	**sp;
	int		j;

	i = 1;
	if (argc == 1)
		return (1);
	while (i < argc)
	{
		sp = ft_split(argv[i]);
		j = 0;
		while (sp[j])
		{
			if (check_sign(sp[j]) || ft_atoi(sp[j]) < -2147483648
				|| ft_atoi(sp[j]) > 2147483647)
			{
				free_split(sp);
				return (1);
			}
			j++;
		}
		free_split(sp);
		i++;
	}
	return (0);
}

int	is_dup(int argc, char *argv[])
{
	int		i;
	int		j;
	char	**temp1;
	char	**temp2;

	i = 1;
	while (i < argc)
	{
		j = i + 1;
		if (is_dup_split(argv[i]))
			return (1);
		if (j < argc)
			if (is_dup_split(argv[j]))
				return (1);
		while (j < argc)
		{
			temp1 = ft_split(argv[i]);
			temp2 = ft_split(argv[j]);
			if (st_compare(temp1, temp2))
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
