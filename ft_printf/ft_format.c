/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 19:23:13 by dongseo           #+#    #+#             */
/*   Updated: 2023/05/17 19:25:07 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
	return (len);
}

size_t	ft_printf_u(unsigned int u)
{
	size_t	len;

	len = 0;
	ft_putnbr_u(u, &len);
	return (len);
}

size_t	ft_printf_x(int x, int is_upper)
{
	size_t	len;

	len = 0;
	ft_putnbr_x(x, &len, is_upper);
	return (len);
}
