/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:37:31 by dongseo           #+#    #+#             */
/*   Updated: 2023/12/07 11:13:54 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	int	num;

	if (philo->info->philo_num > 1)
	{
		num = philo->info->philo_num;
		take_up_fork(philo, num);
		philo_printf(philo, "is eating\n");
		pthread_mutex_lock(&(philo->info->after_lock[philo->idx]));
		gettimeofday(&(philo->after_eat), NULL);
		pthread_mutex_unlock(&(philo->info->after_lock[philo->idx]));
		ft_usleep(philo->info->time_to_eat * 1000, philo);
		pthread_mutex_lock(&(philo->info->cnt_lock[philo->idx]));
		philo->eat_cnt++;
		pthread_mutex_unlock(&(philo->info->cnt_lock[philo->idx]));
		philo->info->fork[(philo->idx + 1) % num] = 0;
		pthread_mutex_unlock(&(philo->info->lock[(philo->idx + 1) % num]));
		philo->info->fork[philo->idx] = 0;
		pthread_mutex_unlock(&(philo->info->lock[philo->idx]));
	}
	else
	{
		philo_printf(philo, "has taken a fork\n");
		ft_usleep(philo->info->time_to_die * 1500, philo);
	}
}

void	*start(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->idx % 2 != 0)
		ft_usleep(philo->info->time_to_die * 250, philo);
	pthread_mutex_lock(&(philo->info->flag_lock));
	while (!philo->info->flag)
	{
		pthread_mutex_unlock(&(philo->info->flag_lock));
		eating(philo);
		philo_printf(philo, "is sleeping\n");
		ft_usleep(philo->info->time_to_sleep * 1000, philo);
		philo_printf(philo, "is thinking\n");
		pthread_mutex_lock(&(philo->info->flag_lock));
	}
	pthread_mutex_unlock(&(philo->info->flag_lock));
	return (NULL);
}

int	is_died(t_philo *philo)
{
	int				diff;

	pthread_mutex_lock(&(philo->info->after_lock[philo->idx]));
	diff = get_diff(philo->after_eat);
	pthread_mutex_unlock(&(philo->info->after_lock[philo->idx]));
	if (diff > philo->info->time_to_die)
	{
		pthread_mutex_lock(&(philo->info->flag_lock));
		philo->info->flag = 1;
		diff = get_diff(philo->info->start_time);
		printf("%d %d died\n", diff, philo->idx + 1);
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
			if (is_died(&philo[j]))
				return ;
			pthread_mutex_lock(&(philo[j].info->cnt_lock[j]));
			if (philo[j].eat_cnt >= philo[0].info->min_cnt)
				cnt++;
			pthread_mutex_unlock(&(philo[j].info->cnt_lock[j]));
			j++;
		}
		if (philo->info->min_cnt != -1 && cnt == philo[0].info->philo_num)
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
	int		check;

	check = init(&info, argc, argv);
	if (argc < 5 || argc > 6 || check == 1)
	{
		printf("error\n");
		return (free_all(&info, NULL, 1));
	}
	if (check == 2)
		return (free_all(&info, NULL, 0));
	philo = (t_philo *)malloc(sizeof(t_philo) * info.philo_num);
	if (!philo)
		return (free_all(&info, NULL, 1));
	init_philo(&info, philo);
	i = 0;
	while (i < info.philo_num)
	{
		pthread_join(philo[i].pthread, NULL);
		i++;
	}
	return (free_all(&info, philo, 0));
}
