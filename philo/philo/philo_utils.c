/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 13:55:20 by dongseo           #+#    #+#             */
/*   Updated: 2023/11/30 10:40:23 by dongseo          ###   ########.fr       */
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
int	get_diff(struct timeval time)
{
	struct timeval	now;
	int				diff;
	int				sec;
	int				ms;

	gettimeofday(&now, NULL);
	sec = (now.tv_sec - time.tv_sec) * 1000000;
	ms = (now.tv_usec - time.tv_usec);
	diff = (sec + ms) / 1000;
	return (diff);
}
void	philo_printf(t_philo *philo, char *msg)
{
	int				diff;

	pthread_mutex_lock(&(philo->info->flag_lock));
	if (!philo->info->flag)
	{
		diff = get_diff(philo->info->start_time);
		printf("%d %d %s", diff, philo->idx + 1, msg);
	}
	pthread_mutex_unlock(&(philo->info->flag_lock));
}

void	ft_usleep(int time, t_philo *philo)
{
	struct timeval	start;
	struct timeval	now;
	double			sec;
	double			ms;
	double			diff;

	gettimeofday(&start, NULL);
	while (!philo->info->flag)
	{
		usleep(100);
		gettimeofday(&now, NULL);
		sec = (now.tv_sec - start.tv_sec) * 1000000;
		ms = ((double)now.tv_usec - start.tv_usec);
		diff = sec + ms;
		if (diff > time)
			return ;
	}
}


// sec, usec

// result = sec * 1000000 + usec
// result = (now.sec - start.sec) * 1000000 + (now.usec - start.usec)
// - start.sec * 1000000 - start.usec
// aaa = start.sec * 1000000 + start.usec
// now.sec * 1000000 + now.usec - aaa;