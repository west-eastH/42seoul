/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:01:57 by dongseo           #+#    #+#             */
/*   Updated: 2023/04/26 20:36:02 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

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
size_t	st_len(const char *st)
{
	size_t	i;
	size_t	len;

	len = 0;
	i = 0;
	while (st[i])
	{
		if (st[i] == '%')
		{
			i += 2;
			continue ;
		}
		len++;
		i++;
	}
	return len;
}

size_t	ft_printf_c(char c)
{
	write(1, &c, 1);
	return (1);
}
size_t	ft_printf_s(char *s)
{
	size_t	len;

	len = ft_strlen(s);
	write(1, s, len);
	return (len);
}

size_t	ft_printf_di(int d)
{
	size_t	len;

	len = 0;
	ft_putnbr_di(d, &len);
	return len;
}
size_t	ft_printf_u(unsigned int u)
{
	size_t	len;

	len = 0;
	ft_putnbr_u(u, &len);
	return len;
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

size_t	ft_printf_x(int x, int is_upper)
{
	size_t	len;
	len = 0;
	ft_putnbr_x(x, &len, is_upper);
	return len;
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
	return result;
}

size_t	check_format(char format, va_list ap)
{
	size_t	hex_len;

	hex_len = 0;
	if (format == 'c')
		return ft_printf_c(va_arg(ap, int));
	else if (format == 's')
		return ft_printf_s(va_arg(ap, char *));
	else if (format == 'p')
		return ft_printf_p(va_arg(ap, unsigned long long));
	else if (format == 'd' || format == 'i')
		return ft_printf_di(va_arg(ap, int));
	else if (format == 'u')
		return ft_printf_u(va_arg(ap, unsigned int));
	else if (format == 'x')
		return ft_printf_x(va_arg(ap, int), 0);
	else if (format == 'X')
		return ft_printf_x(va_arg(ap, int), 1);
	else
	{
		write(1, &format, 1);
		return 1;
	}
}
int ft_printf(const char *st, ...)
{
	va_list ap;
	size_t	i;
	size_t	len;

	len = st_len(st);
	i = 0;
	va_start(ap, st);
	while(st[i])
	{
		if (st[i] != '%')
			write(1, &st[i], 1);
		else
		{
			len += check_format(st[i + 1], ap);
			i += 2;
			continue ;
		}
		i++;
	}
	return len;
}
/* 
int main()
{

	size_t i;
	size_t j;
	int a;
	//i = ft_printf("%x\n", 1234);
	//j = printf("%x\n", 1234);
	i = ft_printf("%c\n%s\n%p\n%d\n%i\n%u\n%x\n%X\n%%", 'c', "abc", &a, 1324, -1234, 242121211, 2147483647, 2147483647);
	printf("%zu\n", i);
	printf("================================\n");
	j = printf("%c\n%s\n%p\n%d\n%i\n%u\n%x\n%X\n%%", 'c', "abc", &a, 1324, -1234, 242121211, 2147483647, 2147483647);
	printf("%zu\n", j);
	return 0;
} */