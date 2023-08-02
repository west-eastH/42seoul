/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 21:05:18 by dongseo           #+#    #+#             */
/*   Updated: 2023/08/02 21:43:28 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

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
		exit (1);
	result = ft_split(temp);
	free(temp);
	return (result);
}
