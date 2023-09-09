/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:23:29 by dongseo           #+#    #+#             */
/*   Updated: 2023/08/27 15:38:43 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*join_null_check(char *s1, char *s2)
{
	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (ft_strdup(s2));
	else
		return (s1);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*temp;
	size_t	i;
	size_t	j;

	i = 0;
	if (!s1 || !s2)
		return (join_null_check((char *)s1, (char *)s2));
	temp = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!temp)
		return (0);
	while (s1[i])
	{
		temp[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		temp[i + j] = s2[j];
		j++;
	}
	temp[i + j] = 0;
	free(s1);
	return (temp);
}
