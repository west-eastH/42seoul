/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:41:50 by dongseo           #+#    #+#             */
/*   Updated: 2023/05/11 13:45:35 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "./get_next_line/get_next_line.h"
#include "./libft/libft.h"
#include "checker.h"

int	is_int(int argc, char *argv[])
{
	size_t	i;
	size_t	j;
	int		data;

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
	size_t	i;
	size_t	j;
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

void	push_back(t_stack *stack, int data)
{
	t_node *temp;

	temp = (t_node*)malloc(sizeof(t_node));
	temp->data = data;
	temp.
	if (stack->head == NULL && stack->tail == NULL)
	{
		stack->head = temp;
		stack->tail = temp;
		stack->size++;
	}
}

int	init(t_stack *stack_a, t_stack *stack_b)
{
	stack_a = (t_stack *)malloc(sizeof(t_stack));
	stack_b = (t_stack *)malloc(sizeof(t_stack));
	stack_a->head = 0;
	stack_a->size = 0;
	stack_a->tail = 0;
	stack_b->head = 0;
	stack_b->size = 0;
	stack_b->tail = 0;
	return 0;
}

int	stack_init(int argc, char *argv[])
{
	size_t	i;
	int		data;
	t_stack *stack_a;
	t_stack *stack_b;

	if (is_int(argc, argv) || is_dup(argc, argv) || init(stack_a, stack_b))
		return 1;
	i = 1;
	while (i < argc)
	{
		data = ft_atoi(argv[i]);
		push_back(stack_a, data);
	}
}

int main(int argc, char *argv[])
{
	char *test;
	size_t	i;

	i = 1;
	(void)argc;
	while (argv[i])
	{
		printf("%s ", argv[i]);
		i++;
	}
	test = get_next_line(0);
	while (test)
	{
		printf("%s", test);
		free(test);
		test = get_next_line(1);
	}
	return 0;
}