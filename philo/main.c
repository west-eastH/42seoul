#include "philo.h"

//각 프로그램은 같은 옵션을 가져야 합니다 : 철학자의 수, 철학자의 수명, 밥을 먹는데 걸리는 시간, 잠자는 시간, [각 철학자가 최소한 밥을 먹어야 하는 횟수]

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


void	init(t_info *info, int argc, char *argv[])
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) < 0)
			exit(0);
		i++;
	}
	info->fork = ft_atoi(argv[1]);
	info->die = ft_atoi(argv[2]);
	info->eat = ft_atoi(argv[3]);
	info->sleep = ft_atoi(argv[4]);
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
}

int	main(int argc, char *argv[])
{
	t_info	info;

	if (argc < 5 || argc > 6)
	{
		printf("argc error\n");
		return (0);
	}
	init(&info, argc, argv);
	printf("philosopher num = %d\n", info.fork);
	printf("die = %d\n", info.die);
	printf("eat = %d\n", info.eat);
	printf("sleep = %d\n", info.sleep);
	printf("min_cnt = %d\n", info.min_cnt);
	return (0);
}
