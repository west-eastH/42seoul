/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 21:05:18 by dongseo           #+#    #+#             */
/*   Updated: 2023/08/05 15:12:13 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	**ft_join_split(int argc, char *argv[])
{
	char	*temp;
	char	**result;

	temp = join_argv(argc, argv);
	if (!temp)
	{
		write(2, "Error\n", 6);
		exit (1);
	}
	result = ft_split(temp);
	free(temp);
	return (result);
}
