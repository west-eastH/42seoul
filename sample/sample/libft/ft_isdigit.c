/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 12:52:53 by dongseo           #+#    #+#             */
/*   Updated: 2023/03/18 16:14:38 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

/*
#include <stdio.h>
#include <ctype.h>

int	main ()
{
	printf("========================정답========================");
	printf("%d\n", isdigit('a'));
	printf("%d\n", isdigit('1'));
	printf("%d\n", isdigit('4'));
	printf("%d\n", isdigit(2));
	printf("%d\n", isdigit('5'));
	printf("%d\n", isdigit('a'));
	
	printf("========================정답========================");
	printf("%d\n", ft_isdigit('a'));
	printf("%d\n", ft_isdigit('1'));
	printf("%d\n", ft_isdigit('4'));
	printf("%d\n", ft_isdigit(2));
	printf("%d\n", ft_isdigit('5'));
	printf("%d\n", ft_isdigit('a'));
	return (0);
}
*/