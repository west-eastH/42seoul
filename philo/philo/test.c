

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>


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

int main ()
{
	int diff;
	struct timeval start_time;
	gettimeofday(&start_time, NULL);
	diff = get_diff(start_time);
	printf("before = %d\n", diff);
	ft_usleep(200000);
	diff = get_diff(start_time);
	printf("before = %d\n", diff);
	return 0;
}