/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:40:22 by dongseo           #+#    #+#             */
/*   Updated: 2023/09/01 13:44:17 by yusekim          ###   ########.fr       */
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
	char	**envp;
	t_env	*origin_head;
	t_env	*origin_last;
	t_env	*sorted_head;
}	t_package;

void	init_env(char **envp, t_package *package);
void	add_env_node(t_package *pack, char *name, char *value);
void	add_sorted_node(t_env	**head, t_env *new);
void	delete_env(char *name, t_package *package);
t_env	*find_env(char *name, t_package *package);
void	set_new_env(t_package *pack, t_env *new);

#endif
