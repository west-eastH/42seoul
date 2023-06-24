/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_stack.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 05:27:34 by dongseo           #+#    #+#             */
/*   Updated: 2023/06/25 05:57:32 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	stack_init(int argc, char *argv[])
{
	int i;
	char *joined_str;

	if (argc < 2)
		return (1);
	i = 1;
	joined_str = NULL;
	while (i < argc)
	{
		if (ft_strlen(argv[i]) == 0)
			return (1);
		joined_str = ft_strjoin(joined_str, argv[i], ft_strlen(argv[i]));
		if (joined_str == NULL)
			return (1);
		i++;
	}
	ft_printf("%s", joined_str);
	return (0);
}