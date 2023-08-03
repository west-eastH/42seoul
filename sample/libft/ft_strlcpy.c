/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 12:15:39 by dongseo           #+#    #+#             */
/*   Updated: 2023/03/27 17:23:56 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;

	src_len = 0;
	while (src[src_len])
		src_len++;
	if (dstsize == 0)
		return (src_len);
	i = 0;
	while (i + 1 < dstsize && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (src_len);
}

/*
#include <stdio.h>
#include <string.h>

int main ()
{
	char *s1 = "dong";
	char d1[20] = "ddddddddddddddddd";

	char *s2 = "dong";
	char d2[20] = "ddddddddddddddddd";

	char *s3 = "donghyeonzzzzzzzzzzzzzzzzz";
	char d3[20] = "";
	
	char *s4 = "donghyeonzzzzzzzzzzzzzzzzz";
	char d4[20] = "";
	
	size_t temp1 = strlcpy(d1,s1,15);
	size_t temp2 = ft_strlcpy(d2,s2,15);
	size_t temp3 = strlcpy(d3,s3,15);
	size_t temp4 = ft_strlcpy(d4,s4,15);
	
	printf("%s %zu\n", d1, temp1);
	printf("%s %zu\n", d2, temp2);
	printf("%s %zu\n", d3, temp3);
	printf("%s %zu\n", d4, temp4);
	
	return 0;
}
*/