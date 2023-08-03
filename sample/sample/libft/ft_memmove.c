/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:56:00 by dongseo           #+#    #+#             */
/*   Updated: 2023/03/28 14:17:09 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (dst == NULL && src == NULL)
		return (NULL);
	if (dst < src)
	{
		i = 0;
		while (i < len)
		{
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	else
	{
		i = len;
		while (i > 0)
		{
			((unsigned char *)dst)[i - 1] = ((unsigned char *)src)[i - 1];
			i--;
		}
	}
	return (dst);
}

/*
#include<string.h>
#include<stdio.h>
 
int main(void)
{
	int arr1[20] = {1,2,3,4,5,6,7,8};
	int arr2[20] = {1,2,3,4,5,6,7,8};
	for(int i=0;i<8;i++)
		printf("%d ", arr1[i]);
	printf("\n");
	for(int i=0;i<8;i++)
		printf("%d ", arr2[i]); 
	printf("\n");
	memmove(arr1 +3, arr1 + 1,8);
	ft_memmove(arr2 + 3, arr2 + 1, 8);
	for(int i=0;i<8;i++)
		printf("%d ", arr1[i]);
		printf("\n");
	for(int i=0;i<8;i++)
		printf("%d ", arr2[i]); 
    return 0;
}
*/