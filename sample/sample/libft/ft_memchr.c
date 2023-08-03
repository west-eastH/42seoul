/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:27:39 by dongseo           #+#    #+#             */
/*   Updated: 2023/03/27 20:44:33 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	i = 0;
	ptr = (unsigned char *)s;
	while (i < n)
	{
		if (ptr[i] == (unsigned char)c)
			return (ptr + i);
		i++;
	}
	return (0);
}

/* 
#include <stdio.h>
#include <string.h>
int main ()
{
	char s[] = {0, 65, 2 ,3 ,4 ,5};

	printf("%s", memchr(s, 'A', 5));
	printf("\n");
	printf("%s", ft_memchr(s, 'A', 5));
	return 0;
}
 */