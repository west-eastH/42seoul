/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:37:31 by dongseo           #+#    #+#             */
/*   Updated: 2023/11/30 09:50:37 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&(philo->info->lock[philo->left]));
	philo_printf(philo, "has taken a fork\n");
	if (!pthread_mutex_lock(&(philo->info->lock[philo->right])))
	{
		philo_printf(philo, "has taken a fork\n");
		philo_printf(philo, "is eating\n");
		ft_usleep(philo->info->time_to_eat, philo);
		gettimeofday(&(philo->after_eat), NULL);
		philo->eat_cnt++;
		if (philo->idx % 2 != 0)
			ft_usleep(5, philo);
		pthread_mutex_unlock(&(philo->info->lock[philo->right]));
	}
	pthread_mutex_unlock(&(philo->info->lock[philo->left]));
}

void	*start(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->idx % 2 == 0)
		ft_usleep(philo->info->time_to_die / 4, philo);
	while (!philo->info->flag)
	{
		eating(philo);
		philo_printf(philo, "is sleeping\n");
		ft_usleep(philo->info->time_to_sleep, philo);
		philo_printf(philo, "is thinking\n");
	}
	return (NULL);
}

int	is_died(t_philo *philo)
{
	int				diff;

	diff = get_diff(philo->after_eat);
	if (diff > philo->info->time_to_die)
	{
		pthread_mutex_lock(&(philo->info->flag_lock));
		philo->info->flag = 1;
		diff = get_diff(philo->info->start_time);
		printf("%d %d is died\n", diff, philo->idx);
		pthread_mutex_unlock(&(philo->info->flag_lock));
		return (1);
	}
	return (0);
}

void	check_end(t_philo philo[])
{
	int	j;
	int	cnt;

	while (1)
	{
		j = 0;
		cnt = 0;
		while (j < philo[0].info->philo_num)
		{
			usleep(10);
			if (is_died(&philo[j]))
				return ;
			if (philo[j].eat_cnt >= philo[0].info->min_cnt)
				cnt++;
			j++;
			usleep(100);
		}
		if (philo->info->min_cnt && cnt == philo[0].info->philo_num)
		{
			pthread_mutex_lock(&(philo->info->flag_lock));
			philo[0].info->flag = 1;
			pthread_mutex_unlock(&(philo->info->flag_lock));
			return ;
		}
	}
}

int	main(int argc, char *argv[])
{
	t_info	info;
	t_philo	*philo;
	int		i;

	if (argc < 5 || argc > 6 || init(&info, argc, argv))
	{
		printf("error\n");
		return (0);
	}
	philo = (t_philo *)malloc(sizeof(t_philo) * info.philo_num);
	if (!philo)
		return (1);
	init_philo(&info, philo);
	i = 0;
	while (i < info.philo_num)
	{
		pthread_join(philo[i].pthread, NULL);
		i++;
	}
	return (0);
}
