/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:17:46 by dongseo           #+#    #+#             */
/*   Updated: 2023/03/27 23:22:02 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

/* 
#include <stdio.h>
#include <stdlib.h>
int main ()
{
	printf("atoi=============\n");
	printf("%d\n", atoi(" 123221ddwef123"));
	printf("%d\n", atoi("- 12341ddwef123"));
	printf("%d\n", atoi("12-341ddwef123"));
	printf("%d\n", atoi("-1254 341ddwef123"));
	printf("%d\n", atoi("aa12341ddwef123"));
	printf("%d\n", atoi("aqw12341ddwef123"));
	printf("%d\n", atoi("   -12-341ddwef123"));
	printf("%d\n", atoi("   aa12341ddwef123"));

	printf("ft_atoi=============\n");
	printf("%d\n", ft_atoi(" 123221ddwef123"));
	printf("%d\n", ft_atoi("- 12341ddwef123"));
	printf("%d\n", ft_atoi("12-341ddwef123"));
	printf("%d\n", ft_atoi("-1254 341ddwef123"));
	printf("%d\n", ft_atoi("aa12341ddwef123"));
	printf("%d\n", ft_atoi("aqw12341ddwef123"));
	printf("%d\n", ft_atoi("   -12-341ddwef123"));
	printf("%d\n", ft_atoi("   aa12341ddwef123"));
}
*/