/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:56:00 by dongseo           #+#    #+#             */
/*   Updated: 2023/03/27 17:23:13 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*p_dst;
	unsigned char	*p_src;
	size_t			i;

	if (dst == NULL && src == NULL)
		return (NULL);
	i = 0;
	p_dst = (unsigned char *)dst;
	p_src = (unsigned char *)src;
	while (i < n)
	{
		p_dst[i] = p_src[i];
		i++;
	}
	return (p_dst);
}

/*
#include<string.h>
#include<stdio.h>
 
int main(void)
{
	int arr1[20] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
	int arr2[20] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
	memcpy(arr1 +4, arr1 + 2,17);
	ft_memcpy(arr2 + 4, arr2 + 2, 17);
	for(int i=0;i<20;i++)
		printf("%d ", arr1[i]);
		printf("\n");
	for(int i=0;i<20;i++)
		printf("%d ", arr2[i]);
    char src[] = "BlockDMask";
    char dest1[] = "fffffdddddzzzzz";
    char dest2[] = "fffffdddddzzzzz";
    char dest3[] = "fffffdddddzzzzz";
 
    // 메모리 복사1 : src 길이만큼만 복사
    memcpy(dest1, src, sizeof(char) * 10);
 
    // 메모리 복사2 : src 길이 + 1 만큼 복사
    memcpy(dest2, src, sizeof(char) * 10 + 1);
 
    // 메모리 복사3 : 메모리 일부 복사
    memcpy(dest3 + 10, src, sizeof(char) * 3);
 
    // source
    printf("src  : %s\n", src);
 
    // destination
    printf("dest1 : %s\n", dest1);
    printf("dest2 : %s\n", dest2);
    printf("dest3 : %s\n", dest3);
 
    return 0;
}
*/