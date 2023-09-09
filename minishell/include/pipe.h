/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 12:12:23 by yusekim           #+#    #+#             */
/*   Updated: 2023/09/06 14:21:04 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H
# include "env_utils.h"
# include "parser.h"

void	pipe_exec(t_cmd	*cur, t_package *pack);
char	*set_path(t_package *pack);
char	*ft_cmdjoin(char const *s1, char const *s2);
void	ft_execve(char **cmd, t_package *pack, char **envp);
int		is_route(char *str);
int		is_dir(char *str);

#endif
