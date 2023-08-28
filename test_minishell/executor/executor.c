/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:35:51 by dongseo           #+#    #+#             */
/*   Updated: 2023/08/28 17:43:24 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_cmd	**head);

int	export(char **cmd)
{	
	int		i;
	char	*addr;

	if (cmd[1] == 0)
		print_export(g_package.sorted_head);
	else
	{
		i = 0;
		while (cmd[++i])
		{
			addr = ft_strchr(cmd[i], '=');
			if (addr == cmd[i])
			{
				printf("export: '%s': not a valid identifier\n", addr);
				continue ;
			}
			if (addr)
				*(addr++) = 0;
			add_env_node(&g_package, cmd[i], addr);
		}
	}
	return (1);
}

int	unset(char **cmd)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		if (check_envlen(cmd[i]) != (int)ft_strlen(cmd[i]))
			printf("unset: '%s': not a valid identifier\n", cmd[i]);
		else
			delete_env(cmd[i]);
		i++;
	}
	return (1);
}

int	pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
	return (1);
}

int cd(char **cmd)
{
	int 	result;
	char	*temp;
	t_env	*pwd_dir;

	temp = getcwd(0, 0);
	if (!cmd[1] || !ft_strcmp(cmd[1], "~"))
		result = chdir(find_env("HOME")->value);
	else if (!ft_strcmp(cmd[1], "-"))
	{
		if (!find_env("OLDPWD"))
		{
			printf("cd: OLDPWD not set\n");
			return (1);
		}
		result = chdir(find_env("OLDPWD")->value);
		pwd();
	}
	else
		result = chdir(cmd[1]);
	if (!result)
	{
		add_env_node(&g_package, "OLDPWD", temp);
		free(temp);
		pwd_dir = find_env("PWD");
		free(pwd_dir->value);
		pwd_dir->value = getcwd(0, 0);
	}
	else
		printf("cd: %s: No such file or directory\n", cmd[1]);
	return 1;
}

int	echo(char **cmd)
{
	int	flag;
	int	i;

	flag = 0;
	if (cmd[1] && !ft_strcmp(cmd[1], "-n"))
		flag = 1;
	i = 1;
	while (cmd[i + flag] && cmd[i + flag + 1])
		printf("%s ", cmd[i++ + flag]);
	if (cmd[i + flag])
		printf("%s", cmd[i + flag]);
	if (flag == 0)
		printf("\n");
	return (1);
}

int	check_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			if (((i == 0 && str[i] == '-') || (i == 0 && str[i] == '+'))
				&& str[i + 1] >= '0' && str[i + 1] <= '9')
			{
				i++;
				continue ;
			}
			return (1);
		}
		i++;
	}
	return (0);
}

int	builtin_exit(char **cmd)
{
	int exit_num;

	exit_num = 0;
	printf("exit\n");
	if (cmd && cmd[1])
	{
		if (check_sign(cmd[1]))
		{
			printf("exit: %s: numeric argument required\n", cmd[1]);
			exit_num = 255;
			exit(exit_num);
		}
		if (cmd[2])
		{
			printf("exit: too many arguments\n");
			exit_num = 1;
			return (1);
		}
		else
			exit_num = ft_atoi(cmd[1]) % 256;
	}
	exit(exit_num);
	return (1);
}

int	check_builtin(char **cmd, int flag)
{
	int result;
	if (cmd == NULL)
		return 0;
	if (ft_strcmp(*cmd, "export") == 0)
		result = export(cmd);
	else if (ft_strcmp(*cmd, "env") == 0)
		result = print_env(g_package.origin_head);
	else if (ft_strcmp(*cmd, "unset") == 0)
		result = unset(cmd);
	else if (ft_strcmp(*cmd, "pwd") == 0)
		result = pwd();
	else if (ft_strcmp(*cmd, "cd") == 0)
		result = cd(cmd);
	else if (ft_strcmp(*cmd, "echo") == 0)
		result = echo(cmd);
	else if (ft_strcmp(*cmd, "exit") == 0)
		result = builtin_exit(cmd);
	else
		result = 0;
	if (flag)
		exit(0);
	else
		return result;
}

int	open_files(t_cmd *cmd)
{
	t_redir *temp;

	temp = cmd->redirection;
	while (temp)
	{
		if (temp->type == L_D_LESSER || temp->type == L_LESSER)
			cmd->infile = temp;
		else if (temp->type == L_D_GREATER || temp->type == L_GREATER)
			cmd->outfile = temp;
		if (temp->type == L_D_LESSER)
		{
			here_doc_open(temp);
			close(temp->fd);
		}
		temp = temp->next;
	}
	temp = cmd->redirection;
	while (temp)
	{
		if (temp->type != L_D_LESSER && temp->filename[2])
		{
			printf("%s: ambiguous redirect\n", temp->filename[0]);
			return (1);
		}
		if (temp->type == L_LESSER)
			temp->fd = open(temp->filename[1], O_RDONLY);
		else if (temp->type == L_GREATER)
			temp->fd = open(temp->filename[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (temp->type == L_D_GREATER)
			temp->fd = open(temp->filename[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (temp->type != L_D_LESSER && temp->fd < 0)
		{
			printf("%s: file open error\n", temp->filename[1]);
			return (1);
		}
		close(temp->fd);
		temp = temp->next;
	}
	return (0);
} 

void	set_fd(t_cmd *cur, int fds[2], int *in_fd, int *out_fd)
{
	if (cur->infile)
		*in_fd = open(cur->infile->filename[1], O_RDONLY);
	else
		*in_fd = cur->prev_fd;
	if (cur->outfile)
	{
		if (cur->outfile->type == L_D_GREATER)
			*out_fd = open(cur->outfile->filename[1], O_APPEND | O_CREAT, 0644);
		else
			*out_fd = open(cur->outfile->filename[1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	}
	else if (cur->next)
		*out_fd = fds[1];
}

char	*set_path(void)
{
	char	*result;
	int		i;
	t_env	*env;

	i = 0;
	env = g_package.origin_head;
	while (env && (ft_strncmp(env->name, "PATH", 4)))
		env = env->origin_next;
	result = ft_strdup(env->value);
	if (!result)
		printf("malloc error\n");
	return (result);
}

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
		printf("malloc error\n");
	while (s1[i])
	{
		temp[i] = s1[i];
		i++;
	}
	temp[i] = '/';
	i++;
	j = 0;
	while (s2[j++])
		temp[i + j - 1] = s2[j - 1];
	temp[i + j - 1] = 0;
	return (temp);
}

void	ft_execve(char **cmd)
{
	char	**split;
	int		i;
	char	*result;
	char	*path;

	if (cmd[0] == NULL || !cmd)
		printf("cmd error\n");
	path = set_path();
	split = ft_split(path + 5, ':');
	i = 0;
	while (split[i])
	{
		result = ft_cmdjoin(split[i], cmd[0]);
		if (access(result, X_OK) == 0)
		{
			if (execve(result, cmd, 0) < 0)
				printf("execve error\n");
		}
		free(result);
		free(split[i]);
		i++;
	}
	free(split);
	split = NULL;
	printf("cmd error\n");
}

void	dup_fd (int	in_fd, int out_fd, int *fds)
{
	if (in_fd != 0)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);	
	}
	if (out_fd != 1)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);		
	}
	close(fds[0]);
	close(fds[1]);
}

void	pipe_exec(t_cmd	*cur)
{
	if (cur->cmd_args[0][0] == '/')
		if (execve(cur->cmd_args[0], cur->cmd_args, 0) < 0)
			printf("execve error\n");
	ft_execve(cur->cmd_args);
}

void execute_cmds(t_cmd *cur, int *fds)
{
	int		in_fd;
	int		out_fd;
	pid_t	pid;

	in_fd = 0;
	out_fd = 1;
	set_fd(cur, fds, &in_fd, &out_fd);
	pid = fork();
	if (pid == -1)
		printf("fork error\n");
	if (pid == 0)
	{
		printf("in == %d out == %d\n", in_fd, out_fd);
		printf("fd[0] == %d fd[1] == %d\n", fds[0], fds[1]);
		dup_fd(in_fd, out_fd, fds);
		if (check_builtin(cur->cmd_args, 1))
			printf("========builtin========\n");
		else
			pipe_exec(cur);
	}
	else if (cur->next)
	{
		if (cur->prev_fd != 0)
			close(cur->prev_fd);
		cur->next->prev_fd = fds[0];
		close(fds[1]);
	}
}

void	executor(t_cmd *cmds_head)
{
	t_cmd	*cur;
	int		idx;
	int		fds[2];
	int		count;

	idx = 0;
	cur = cmds_head;
	count = 0;
	while (cur)
	{
		count++;
		cur = cur->next;
	}
	cur = cmds_head;
	while (cur)
	{
		if (idx == 0 && !cur->next
			&& check_builtin(cur->cmd_args, 0))
		{
			cur = cur->next;
			continue ;
		}
		if (open_files(cur))
		{
			cur = cur->next;
			continue ;
		}
		if (pipe(fds) == -1)
		{
			printf("pipe error\n");
			exit(1);
		}
		execute_cmds(cur, fds);	//여기서 명령 실행(빌트인 포함)
		cur = cur->next;
	}
	while (count--)
		wait(0);
	free_cmd(&cmds_head);
}

void	free_cmd(t_cmd	**head)
{
	t_cmd	*temp;
	t_redir	*redir;
	int		idx;


	while (*head)
	{
		temp = *head;
		idx = 0;
		while (temp->cmd_args && temp->cmd_args[idx])
		{
			free(temp->cmd_args[idx]);
			idx++;
		}
		free(temp->cmd_args);
		while (temp->redirection)
		{
			redir = temp->redirection;
			free_strings(redir->filename);
			temp->redirection = temp->redirection->next;
			free(redir);
		}
		*head = temp->next;
		free(temp);
	}
}
