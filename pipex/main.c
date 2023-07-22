#include <unistd.h>
#include <stdio.h>
#include "libft/libft.h"


char	*ft_cmdjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*temp;
	size_t	i;
	size_t	j;

	i = 0;
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	temp = (char *)malloc(s1_len + s2_len + 2);
	if (!temp)
		return (0);
	while (s1[i++])
		temp[i - 1] = s1[i - 1];
	temp[i - 1] = '/';
	j = 0;
	while (s2[j])
	{
		temp[i + j] = s2[j];
		j++;
	}
	//temp[i + j] = 0;
	return (temp);
}


int	main(int argc, char *argv[], char **envp)
{
	if (argc != 5)
		return (0);
	int	root;
	char **cmd;
	int i  = 0;
	char **split;
	char *temp;

	root = 0;
	if (argv[1][0] == '/')
		root = 1;
	cmd = ft_split(argv[1], ' ');
	if (root)
		execve(cmd[0], cmd, envp);

	split = ft_split(envp[4], ':');
	temp = split[0];
	split[0] = ft_split(split[0], '=')[1];
	free(temp);
	temp = NULL;
	char *result;
	while (split[i])
	{
		ft_printf("%s\n", split[i]);
		i++;
	}
	ft_printf("\n");
	ft_printf("\n");
	i = 0;
	while (split[i])
	{
		result = ft_cmdjoin(split[i], cmd[0]);
		if (execve(result, argv, envp) != -1)
			break;
		printf("%s\n", result);
		free(result);
		i++;
	}
}