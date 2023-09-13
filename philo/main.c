/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:37:31 by dongseo           #+#    #+#             */
/*   Updated: 2023/09/13 21:58:41 by dongseo          ###   ########.fr       */
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

void	ft_exit(char *msg)
{
	printf("%s\n", msg);
	exit(0);
}

int	init(t_info *info, int argc, char *argv[])
{
	int	i;
	info->philo_num = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 5)
		info->min_cnt = 0;
	else
		info->min_cnt = ft_atoi(argv[5]);
	if (info->philo_num <= 0 || info->time_to_die < 0 ||
		info->time_to_eat < 0 || info->time_to_sleep < 0 || info->min_cnt < 0)
		return 1;
	info->fork = malloc(sizeof(int) * info->philo_num);
	if (!info->fork)
		return 1;
	i = 0;
	while (i < info->philo_num)
	{
		info->fork[i] = 0;
		i++;
	}
	info->lock = malloc(sizeof(pthread_mutex_t) * info->philo_num);
	if (!info->lock)
		return 1;
	i = 0;
	while (i < info->philo_num)
	{
		pthread_mutex_init(&(info->lock[i]), NULL);
		i++;
	}
	pthread_mutex_init(&(info->print), NULL);
	gettimeofday(&info->start_time, NULL);
	return 0;
}

void	*start(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	if (philo->idx % 2 == 0)
		usleep(1000);
	while (1)
	{
		eating();
		printf("%d philo sleep\n", philo->idx);
		usleep(philo->info->time_to_sleep);
		printf("%d philo thinking\n", philo->idx);
	}
	return NULL;
}

void	init_philo(t_info *info, t_philo philo[])
{
	int	i;

	i = 0;
	while (i < info->philo_num)
	{
		philo[i].idx = i;
		philo[i].eat_cnt = 0;
		philo[i].left = i;
		philo[i].right = (i + 1) % info->philo_num;
		philo[i].info = info;
		gettimeofday(&(philo[i].after_eat), NULL);
		pthread_create(&(philo[i].pthread), NULL, start, &(philo[i]));
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_info	info;
	//struct timeval	end_time;
	t_philo *philo;
	int		i;
	//double	diff_time;

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
	/* 
	if (info.fork == 1)
	{
		usleep(info.die * 1000);
		gettimeofday(&end_time, NULL);
		diff_time = ((double)(end_time.tv_sec - info.start_time.tv_sec) * 1000000 + (end_time.tv_usec - info.start_time.tv_usec)) / 1000;
		printf("%f_in_ms 1 died\n", diff_time);
		exit(0);
	}
	printf("philosopher num = %d\n", info.fork);
	printf("die = %d\n", info.die);
	printf("eat = %d\n", info.eat);
	printf("sleep = %d\n", info.sleep);
	printf("min_cnt = %d\n", info.min_cnt); */
	return (0);
}
