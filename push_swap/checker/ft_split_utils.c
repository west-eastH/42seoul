/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:10:45 by dongseo           #+#    #+#             */
/*   Updated: 2023/06/21 15:26:20 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	free_split(char	**temp)
{
	int	i;

	i = 0;
	while (temp[i])
	{
		free(temp[i]);
		temp[i] = NULL;
		i++;
	}
	free(temp);
	temp = NULL;
}

int	is_dup_split(char *st)
{
	char	**temp;
	int		i;
	int		j;

	i = 0;
	j = 1;
	temp = ft_split(st);
	while (temp[j])
	{
		if (ft_atoi(temp[i]) == ft_atoi(temp[j]))
		{
			free_split(temp);
			return (1);
		}
		i++;
		j++;
	}
	free_split(temp);
	return (0);
}

int	st_compare(char **st1, char **st2)
{
	int	i;
	int	j;

	i = 0;
	while (st1[i])
	{
		j = 0;
		while (st2[j])
		{
			if (ft_atoi(st1[i]) == ft_atoi(st2[j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
