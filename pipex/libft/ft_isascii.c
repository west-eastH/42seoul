/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 12:52:53 by dongseo           #+#    #+#             */
/*   Updated: 2023/03/18 16:26:00 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}

/*
#include <stdio.h>
#include <ctype.h>

int	main ()
{
	printf("========================정답========================\n");
	printf("%d\n", isascii('a'));
	printf("%d\n", isascii('1'));
	printf("%d\n", isascii('4'));
	printf("%d\n", isascii(2));
	printf("%d\n", isascii('5'));
	printf("%d\n", isascii('a'));

	printf("========================정답========================\n");
	printf("%d\n", ft_isascii('a'));
	printf("%d\n", ft_isascii('1'));
	printf("%d\n", ft_isascii('4'));
	printf("%d\n", ft_isascii(2));
	printf("%d\n", ft_isascii('5'));
	printf("%d\n", ft_isascii('a'));
	return (0);
}
*/