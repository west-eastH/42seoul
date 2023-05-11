/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 12:52:53 by dongseo           #+#    #+#             */
/*   Updated: 2023/03/19 12:59:53 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	else if (c >= 'A' && c <= 'Z')
		return (1);
	else if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
/*
#include <stdio.h>
#include <ctype.h>

int	main ()
{
	printf("========================정답========================\n");
	printf("%d\n", isalnum('a'));
	printf("%d\n", isalnum('1'));
	printf("%d\n", isalnum('4'));
	printf("%d\n", isalnum(2));
	printf("%d\n", isalnum('5'));
	printf("%d\n", isalnum('a'));

	printf("========================정답========================\n");
	printf("%d\n", ft_isalnum('a'));
	printf("%d\n", ft_isalnum('1'));
	printf("%d\n", ft_isalnum('4'));
	printf("%d\n", ft_isalnum(2));
	printf("%d\n", ft_isalnum('5'));
	printf("%d\n", ft_isalnum('a'));
	return (0);
}
*/