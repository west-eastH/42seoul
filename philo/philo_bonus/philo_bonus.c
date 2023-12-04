/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:45:48 by dongseo           #+#    #+#             */
/*   Updated: 2023/12/04 15:59:27 by dongseo          ###   ########.fr       */
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
		return (1)
	init_philo(&info, philo);
	i = 0;
	while (i < info.philo_num)
	{
		pthread_join(philo[i].pthread, NULL);
		i++;
	}
	free(philo);
	free(info.after_lock);
	free(info.lock);
	return (0);
}
