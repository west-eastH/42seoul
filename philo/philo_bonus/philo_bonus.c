/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:45:48 by dongseo           #+#    #+#             */
/*   Updated: 2023/12/05 15:26:32 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char *argv[])
{
	t_info	info;
	t_philo	*philo;
	int		i;

	if (argc < 5 || argc > 6 || init(&info, argc, argv))
	{
		if (init(&info, argc, argv) != 2)
			printf("error\n");
		return (0);
	}
	philo = (t_philo *)malloc(sizeof(t_philo) * info.philo_num);
	if (!philo)
		return (1);
	i = 0;
	return (0);
}
