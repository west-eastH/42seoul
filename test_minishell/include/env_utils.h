/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youwin0802 <youwin0802@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:40:22 by dongseo           #+#    #+#             */
/*   Updated: 2023/08/26 21:47:15 by youwin0802       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_UTILS_H
# define ENV_UTILS_H

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*origin_prev;
	struct s_env	*origin_next;
	struct s_env	*sorted_prev;
	struct s_env	*sorted_next;
}	t_env;

typedef struct s_package
{
	int		exit_status;
	t_env	*origin_head;
	t_env	*origin_last;
	t_env	*sorted_head;
}	t_package;

t_package	g_package;
void		init_env(char **envp, t_package *package);
void		add_env_node(t_package *pack, char *name, char *value);
void		delete_env(char *name);
t_env		*find_env(char *name);
#endif
