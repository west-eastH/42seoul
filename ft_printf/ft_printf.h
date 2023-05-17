/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 19:12:41 by dongseo           #+#    #+#             */
/*   Updated: 2023/05/17 19:18:35 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>

size_t	ft_strlen(const char *s);
size_t	st_len(const char *st);

void	ft_putnbr_di(int n, size_t *len);
void	ft_putnbr_u(unsigned int u, size_t *len);
void	ft_putnbr_x(int x, size_t *len, int is_upper);

size_t	ft_printf_c(char c);
size_t	ft_printf_s(char *s);
size_t	ft_printf_di(int d);
size_t	ft_printf_u(unsigned int u);
size_t	ft_printf_x(int x, int is_upper);
size_t	ft_printf_p(unsigned long long p);

size_t	check_format(char format, va_list ap);
int		ft_printf(const char *st, ...);
#endif