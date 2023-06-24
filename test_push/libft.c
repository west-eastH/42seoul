/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 04:57:55 by dongseo           #+#    #+#             */
/*   Updated: 2023/06/25 06:13:57 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (i);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*temp;
	size_t	len;
	size_t	i;

	i = 0;
	len = 0;
	while (s1[len])
		len++;
	temp = (char *)malloc(len + 1);
	if (!temp)
		return (NULL);
	while (s1[i])
	{
		temp[i] = s1[i];
		i++;
	}
	temp[i] = 0;
	return (temp);
}


char	*ft_strjoin(char *s1, char *s2, size_t s2_len)
{
	char	*temp;
	size_t	s1_len;
	size_t	i;
	size_t	j;

	i = 0;
	if (!s1)
		return (ft_strdup(s2));
	s1_len = ft_strlen(s1);
	temp = (char *)malloc(s1_len + s2_len + 2);
	if (!temp)
		return (NULL);
	while (s1[i++])
		temp[i - 1] = s1[i - 1];
	free(s1);
	temp[i - 1] = ' ';
	j = 0;
	while (s2[j])
	{
		temp[i + j] = s2[j];
		j++;
	}
	temp[i + j] = 0;
	return (temp);
}