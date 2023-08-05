/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 05:27:34 by dongseo           #+#    #+#             */
/*   Updated: 2023/08/05 11:35:35 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	check_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			if (((i == 0 && str[i] == '-') || (i == 0 && str[i] == '+'))
				&& str[i + 1] >= '0' && str[i + 1] <= '9')
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

int	is_int(char *str[])
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (check_sign(str[i]) || ft_atoi(str[i]) < -2147483648
			|| ft_atoi(str[i]) > 2147483647)
			return (1);
		i++;
	}
	return (0);
}

char	*join_argv(int argc, char *argv[])
{
	int		i;
	char	*result;

	i = 1;
	result = NULL;
	while (i < argc)
	{
		if (ft_strlen(argv[i]) == 0)
		{
			if (result)
				free(result);
			return (NULL);
		}
		result = ft_strjoin(result, argv[i], ft_strlen(argv[i]));
		if (result == NULL)
			return (NULL);
		i++;
	}
	i = 0;
	while (result[i++])
	{
		if ((result[i - 1] < 9 || result[i - 1] > 13) && result[i - 1] != 32)
			return (result);
	}
	return (NULL);
}

int	stack_init(int argc, char *argv[], t_stack *stack_a, t_stack *stack_b)
{
	char	**split_str;
	int		i;

	split_str = ft_join_split(argc, argv);
	if (is_int(split_str) || is_dup(split_str)
		|| init(stack_a) || init(stack_b))
	{
		ft_free(split_str);
		return (1);
	}
	i = 0;
	while (split_str[i++])
	{
		if (push_front(stack_a, ft_atoi(split_str[i - 1])))
		{
			ft_free(split_str);
			return (1);
		}
	}
	ft_free(split_str);
	return (0);
}

int	is_dup(char *str[])
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (str[i + 1])
	{
		j = i + 1;
		while (str[j])
		{
			if (ft_atoi(str[i]) == ft_atoi(str[j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
