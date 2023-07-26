/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 14:52:57 by dongseo           #+#    #+#             */
/*   Updated: 2023/07/26 16:03:34 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft/libft.h"

char	*set_path(char **envp);
char	*ft_cmdjoin(char const *s1, char const *s2);
void	ft_execve(char **cmd, char **envp);
void	child_process(int fd[2], char *argv[], char **envp);
void	parent_process(int fd[2], char *argv[], char **envp, pid_t pid);
void	ft_perror(char *msg);
#endif