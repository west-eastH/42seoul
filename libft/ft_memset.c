/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:07:04 by dongseo           #+#    #+#             */
/*   Updated: 2023/03/27 17:23:21 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		ptr[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

/*

#include <string.h>
#include <stdio.h>
int main()
{
	int arr[20];
	char s1[20] = "212rsefsfsfsf";
	char s2[20] = "212rsefsfsfsf";
	char s3[20] = "212rs";
	char s4[20] = "212rqqsf";
	char s5[20] = "aaa21212fsfsf";
	
	memset(arr, 0, 20 * sizeof(int));
	memset(s1, 'a', 5);
	memset(s2, 'a', 5);
	memset(s3, 'a', 5);
	memset(s4, 'a', 5);
	memset(s5, 'a', 5);

	int ft_arr[20];
	char ft_s1[20] = "212rsefsfsfsf";
	char ft_s2[20] = "212rsefsfsfsf";
	char ft_s3[20] = "212rs";
	char ft_s4[20] = "212rqqsf";
	char ft_s5[20] = "aaa21212fsfsf";

	ft_memset(ft_arr, 0, 20 * sizeof(int));
	ft_memset(ft_s1, 'a', 5);
	ft_memset(ft_s2, 'a', 5);
	ft_memset(ft_s3, 'a', 5);
	ft_memset(ft_s4, 'a', 5);
	ft_memset(ft_s5, 'a', 5);

	printf("=======정답=======\n");
	int i = 0;
	while (i < 20)
	{
		printf("%d ", arr[i]);
		i++;
	}
	printf("\n");
	printf("%s\n", s1);
	printf("%s\n", s2);
	printf("%s\n", s3);
	printf("%s\n", s4);
	printf("%s\n", s5);
	
	printf("=======출력=======\n");
	int j = 0;
	while (j < 20)
	{
		printf("%d ", ft_arr[j]);
		j++;
	}
	printf("\n");
	printf("%s\n", ft_s1);
	printf("%s\n", ft_s2);
	printf("%s\n", ft_s3);
	printf("%s\n", ft_s4);
	printf("%s\n", ft_s5);
	
	return 0;
}
*/