/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:37:31 by dongseo           #+#    #+#             */
/*   Updated: 2023/09/12 17:35:10 by dongseo          ###   ########.fr       */
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

void	init(t_info *info, int argc, char *argv[])
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) < 0)
			ft_exit("argc error");
		i++;
	}
	info->philo_num = ft_atoi(argv[1]);
	info->die = ft_atoi(argv[2]);
	info->time_eat = ft_atoi(argv[3]);
	info->sleep = ft_atoi(argv[4]);
	info->fork = malloc(sizeof(int) * info->philo_num);
	info->lock = malloc(sizeof(pthread_mutex_t) * info->philo_num);
	if (argc == 5)
	{
		info->flag = 0;
		info->min_cnt = 0;
	}
	else
	{
		info->flag = 1;
		info->min_cnt = ft_atoi(argv[5]);
	}
	gettimeofday(&info->start_time, NULL);
}

void	init_philo(t_info *info, t_philo philo[])
{
	int	i;

	i = 0;
	while (i < info->philo_num)
	{
		philo[i].idx = i;
		philo[i].eat_num = 0;
		philo[i].left = (i + info->philo_num - 1) % info->philo_num;
		philo[i].right = (i + 1) % info->philo_num;
		philo[i].info = info;
		gettimeofday(&(philo[i].after_eat), NULL);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_info	info;
	//struct timeval	end_time;
	t_philo *philo;
	//double	diff_time;

	if (argc < 5 || argc > 6)
	{
		printf("argc error\n");
		return (0);
	}
	init(&info, argc, argv);
	philo = (t_philo *)malloc(sizeof(t_philo) * info.philo_num);
	init_philo(&info, philo);
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
