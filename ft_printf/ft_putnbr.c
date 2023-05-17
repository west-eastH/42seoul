/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 19:26:21 by dongseo           #+#    #+#             */
/*   Updated: 2023/05/17 19:27:02 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_di(int n, size_t *len)
{
	long long	num;
	int			sign;
	char		c;

	num = n;
	sign = 1;
	if (num < 0)
	{
		sign *= -1;
		num *= -1;
	}
	if (sign == -1)
	{
		*len += 1;
		write(1, "-", 1);
	}
	if (num > 9)
		ft_putnbr_di(num / 10, len);
	c = num % 10 + '0';
	*len += 1;
	write(1, &c, 1);
}

void	ft_putnbr_u(unsigned int u, size_t *len)
{
	unsigned int	num;
	char			c;

	num = u;
	if (num > 9)
		ft_putnbr_u(num / 10, len);
	c = num % 10 + '0';
	*len += 1;
	write(1, &c, 1);
}

void	ft_putnbr_x(int x, size_t *len, int is_upper)
{
	char	c;
	char	*hex;

	if (is_upper == 1)
		hex = "0123456789ABCDEF";
	else
		hex = "0123456789ABCDEF";
	if (x > 15)
		ft_putnbr_x(x / 16, len, is_upper);
	c = x % 16;
	*len += 1;
	write(1, &hex[(int)c], 1);
}

size_t	ft_printf_p(unsigned long long p)
{
	unsigned long long	len;
	unsigned long long	i;
	int					base[16];
	size_t				result;

	len = 15;
	i = 15;
	while (len + 1 && p > 0)
	{
		base[len] = p % 16;
		p /= 16;
		len--;
		i--;
	}
	i++;
	write(1, "0x", 2);
	result = 2;
	while (i < 16)
	{
		write(1, &"0123456789abcdef"[base[i] % 16], 1);
		result++;
		i++;
	}
	return (result);
}
