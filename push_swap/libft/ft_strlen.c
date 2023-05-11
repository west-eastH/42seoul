/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 16:52:43 by dongseo           #+#    #+#             */
/*   Updated: 2023/03/27 17:24:01 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/*
#include <stdio.h>
#include <string.h>

int main ()
{
	char *s1 = "aaawdqdwef";
	char *s2 = "aaawef";
	char *s3 = "aaawef";
	char *s4 = "";
	char *s5 = "ddddaaawdqdwef";
	printf("=======정답=======\n");
	printf("%zu\n", strlen(s1));
	printf("%zu\n", strlen(s2));
	printf("%zu\n", strlen(s3));
	printf("%zu\n", strlen(s4));
	printf("%zu\n", strlen(s5));
	printf("=======출력=======\n");
	printf("%zu\n", ft_strlen(s1));
	printf("%zu\n", ft_strlen(s2));
	printf("%zu\n", ft_strlen(s3));
	printf("%zu\n", ft_strlen(s4));
	printf("%zu\n", ft_strlen(s5));
	return 0;
}
*/