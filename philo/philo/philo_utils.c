/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 13:55:20 by dongseo           #+#    #+#             */
/*   Updated: 2023/10/09 14:32:00 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	philo_printf(t_philo *philo, char *msg)
{
	struct timeval	now;
	int				diff;
	int				sec;
	int				ms;

	gettimeofday(&now, NULL);
	sec = (now.tv_sec - philo->info->start_time.tv_sec) * 1000000;
	ms = (now.tv_usec - philo->info->start_time.tv_usec);
	diff = (sec + ms) / 1000;
	pthread_mutex_lock(&(philo->info->print));
	pthread_mutex_lock(&(philo->info->flag_lock));
	if (!philo->info->flag)
		printf("%d %d %s", diff, philo->idx + 1, msg);
	pthread_mutex_unlock(&(philo->info->flag_lock));
	pthread_mutex_unlock(&(philo->info->print));
}

void	ft_usleep(int time)
{
	struct timeval	start;
	struct timeval	now;
	double			sec;
	double			ms;
	double			diff;

	gettimeofday(&start, NULL);
	while (1)
	{
		usleep(10);
		gettimeofday(&now, NULL);
		sec = (now.tv_sec - start.tv_sec) * 1000000;
		ms = ((double)now.tv_usec - start.tv_usec);
		diff = sec + ms;
		if (diff > time)
			return ;
	}
}
