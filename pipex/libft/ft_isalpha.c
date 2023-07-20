/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 12:52:53 by dongseo           #+#    #+#             */
/*   Updated: 2023/03/18 16:07:08 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	else if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}

/*
#include <stdio.h>
#include <ctype.h>

int	main ()
{
	printf("%d\n", ft_isalpha('a'));
	printf("%d\n", ft_isalpha(125));
	printf("%d\n", ft_isalpha(2));
	printf("%d\n", ft_isalpha(1));
	printf("%d\n", ft_isalpha(25));
	printf("%d\n", ft_isalpha('c'));
	printf("%d\n", ft_isalpha('D'));
	return (0);
}
*/