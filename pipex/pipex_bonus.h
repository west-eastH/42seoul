/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 14:52:57 by dongseo           #+#    #+#             */
/*   Updated: 2023/08/21 20:03:56 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft/libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list
{
	int				fd;
	char			*st;
	struct s_list	*next;
}t_list;

typedef struct s_idx
{
	int		i;
	int		is_here_doc;
}t_idx;

size_t	gnl_ft_strlen(const char *s);
char	*gnl_ft_strdup(char *s1, size_t len);
char	*gnl_ft_strjoin(char *s1, char *s2, size_t s2_len);
t_list	*gnl_ft_find_fd(t_list *lst, int fd);
int		gnl_ft_backup(t_list **lst, int fd, char *buffer, int size);

int		gnl_is_line(char *backup);
char	*gnl_split(int fd, t_list **lst, int idx);
char	*gnl_no_line(int fd, t_list **lst, int size);
char	*get_next_line(int fd);
void	gnl_ft_free(t_list **lst, int fd);

void	first_child(int *fd[], char *argv[], char **envp);
void	middle_child(int *fd[], char *argv[], char **envp, int i);
void	last_child(int *fd[], char *argv[], char **envp, t_idx *idx);
int		is_group(char *str);
void	ft_execve(char **cmd, char **envp);

char	*set_path(char **envp);
char	*ft_cmdjoin(char const *s1, char const *s2);
void	ft_close(int cnt, int *fd[]);
int		**make_pipe(int cnt);
int		temp_open(char *argv[]);

void	ft_perror(char *msg);
int		ft_wait(int argc, char *argv[], int is_here_doc, int last_pid);
void	make_temp(char *argv[]);
void	ft_here_doc(int*argc, char *argv[], t_idx *idx);

void	ft_dup2(int fd, int fd2);
void	file_close(int fd);
int		file_open(char *file, int is_here_doc);
void	command_error(char **cmd);
#endif