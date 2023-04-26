/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 13:30:47 by dongseo           #+#    #+#             */
/*   Updated: 2023/03/27 17:23:54 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dest_len;
	size_t	src_len;

	src_len = ft_strlen(src);
	if (dst == 0)
		dest_len = 0;
	else
		dest_len = ft_strlen(dst);
	i = 0;
	if (dest_len >= dstsize)
		return (src_len + dstsize);
	while (src[i] && (dest_len + i + 1 < dstsize))
	{
		dst[dest_len + i] = src[i];
		i++;
	}
	dst[dest_len + i] = 0;
	return (dest_len + src_len);
}
/*
#include <stdio.h>
#include <string.h>
int main()
{
	char *dest = 0;
    char src[7] = "Hell";
	printf("intput\n");
    printf("ft_strlcat count: %zu\n", ft_strlcat(dest, src, 16));
	printf("dest :%s\n", dest);
	printf("------------------------\n");
	char *dest1 = 0;
    char src1[7] = "Hell";
	printf("ouput\n");
    printf("strlcat count: %zu\n", strlcat(dest1, src1, 16));
	printf("dest :%s\n", dest1);
}
*/