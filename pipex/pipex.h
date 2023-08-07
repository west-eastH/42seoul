/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 14:52:57 by dongseo           #+#    #+#             */
/*   Updated: 2023/08/07 14:41:39 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft/libft.h"

void	first_child(int *fd[], char *argv[], char **envp);
void	middle_child(int *fd[], char *argv[], char **envp, int i);
void	last_child(int *fd[], char *argv[], char **envp, int i);
int		is_group(char *str);
void	ft_execve(char **cmd, char **envp);

char	*set_path(char **envp);
char	*ft_cmdjoin(char const *s1, char const *s2);
void	ft_close(int cnt, int *fd[]);
int		**make_pipe(int cnt, char *argv[]);

void	ft_perror(char *msg);
int		ft_wait(int argc, int **fd);

void	ft_dup2(int fd, int fd2);
void	file_close(int fd);
int		file_open(char *file, int is_here_doc);
#endif