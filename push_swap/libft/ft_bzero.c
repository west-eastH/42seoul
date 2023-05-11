/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:39:41 by dongseo           #+#    #+#             */
/*   Updated: 2023/03/27 17:22:24 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}

/*
#include <strings.h>
#include <stdio.h>

int main()
{
	int arr[20];
	char s1[20] = "212rsefsfsfsf";
	char s2[20] = "212rsefsfsfsf";
	char s3[20] = "212rs";
	char s4[20] = "212rqqsf";
	char s5[20] = "aaa21212fsfsf";
	
	bzero(arr, 20 * sizeof(int));
	bzero(s1, 5);
	bzero(s2, 5);
	bzero(s3, 5);
	bzero(s4, 5);
	bzero(s5, 5);

	int ft_arr[20];
	char ft_s1[20] = "212rsefsfsfsf";
	char ft_s2[20] = "212rsefsfsfsf";
	char ft_s3[20] = "212rs";
	char ft_s4[20] = "212rqqsf";
	char ft_s5[20] = "aaa21212fsfsf";

	ft_bzero(ft_arr, 20 * sizeof(int));
	ft_bzero(ft_s1, 5);
	ft_bzero(ft_s2, 5);
	ft_bzero(ft_s3, 5);
	ft_bzero(ft_s4, 5);
	ft_bzero(ft_s5, 5);

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