/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_stack.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 05:27:34 by dongseo           #+#    #+#             */
/*   Updated: 2023/06/25 18:13:40 by dongseo          ###   ########.fr       */
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

int	is_int(char *str[])
{
	int i;

	i = 0;
	while (str[i])
	{
		if (check_sign(str[i]) || ft_atoi(str[i]) < -2147483648
				|| ft_atoi(str[i]) > 2147483647)
			return (1);
		i++;
	}
	return 0;
}

int	stack_init(int argc, char *argv[])
{
	int i;
	char *joined_str;
	char	**split_str;

	if (argc < 2)
		return (1);
	i = 1;
	joined_str = NULL;
	while (i < argc)
	{
		if (ft_strlen(argv[i]) == 0)
			return (1);
		joined_str = ft_strjoin(joined_str, argv[i], ft_strlen(argv[i]));
		if (joined_str == NULL)
			return (1);
		i++;
	}
	split_str = ft_split(joined_str);
	if (is_int(split_str))
	{
		free(split_str);
		return (1);
	}
	return (0);
}

int	is_dup()
{
	
}
