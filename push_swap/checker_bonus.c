/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 03:59:46 by dongseo           #+#    #+#             */
/*   Updated: 2023/07/04 18:49:20 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	checker(char *command, t_stack *stack_a, t_stack *stack_b)
{
	int	check;

	check = 0;
	while (command)
	{
		if (command[0] == 's')
			check = check_swap(command, stack_a, stack_b);
		else if (command[0] == 'p')
			check = check_push(command, stack_a, stack_b);
		else if (command[0] == 'r')
			check = check_rotate(command, stack_a, stack_b);
		else
			check = 1;
		free(command);
		if (check == 1)
		{
			free_stack(stack_a, stack_b);
			ft_printf("Error\n");
			return (1);
		}
		command = get_next_line(0);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	char	*command;

	if (argc < 2)
		return (0);
	stack_a = (t_stack *)malloc(sizeof(t_stack));
	stack_b = (t_stack *)malloc(sizeof(t_stack));
	if (!stack_a || !stack_b || stack_init(argc, argv, stack_a, stack_b))
	{
		ft_printf("Error\n");
		free_stack(stack_a, stack_b);
		return (0);
	}
	command = get_next_line(0);
	if (checker(command, stack_a, stack_b))
		return (0);
	check_sort(stack_a, stack_b);
	return (0);
}
