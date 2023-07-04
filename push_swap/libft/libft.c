/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 04:57:55 by dongseo           #+#    #+#             */
/*   Updated: 2023/07/04 18:32:49 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

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

int	ft_atoi(const char *str)
{
	int			i;
	long long	res;
	int			sign;

	sign = 1;
	res = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res *= 10;
		res += str[i] - '0';
		i++;
	}
	return (sign * res);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i] && i + 1 < n)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
