/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 14:52:57 by dongseo           #+#    #+#             */
/*   Updated: 2023/07/27 14:27:05 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft/libft.h"

char	*set_path(char **envp);
char	*ft_cmdjoin(char const *s1, char const *s2);
void	ft_execve(char **cmd, char **envp);
void	ft_close(int cnt, int *fd[]);
void	first_child(int *fd[], char *argv[], char **envp);
void	middle_child(int *fd[], char *argv[], char **envp, int i);
void	last_child(int *fd[], char *argv[], char **envp, int i);
void	ft_perror(char *msg);
void	make_pipe(int cnt);
#endif