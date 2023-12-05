/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 12:12:23 by yusekim           #+#    #+#             */
/*   Updated: 2023/12/05 15:50:37 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>


typedef struct s_info
{
	int				philo_num;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				min_cnt;
	sem_t			*fork;
	sem_t			*flag;
	sem_t			**eat_cnt;
}	t_info;

typedef struct s_philo
{
	int				idx;
	struct timeval	after_eat;
	int				eat_cnt;
	pthread_t		pthread;
	t_info			*info;
}	t_philo;
#endif
