/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 15:28:01 by yusekim           #+#    #+#             */
/*   Updated: 2023/08/17 14:10:03 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tok(t_token	*head)
{
	t_token	*temp;
	int		idx;

	temp = head;
	idx = 0;
	if (!temp)
		printf("NO NODE\n");
	while (temp)
	{
		printf("%d token data: [%d][%s]\n",
			idx++, temp->type, temp->data);
		temp = temp->next;
	}
}

void	append_sorted(t_env **head, t_env *new)
{
	t_env	*temp;
	t_env	*temp_next;

	temp = *head;
	if (ft_strcmp(new->name, temp->name) < 0)
	{
		*head = new;
		new->sorted_next = temp;
		return ;
	}
	while (temp->sorted_next
			&& ft_strcmp(new->name, temp->sorted_next->name) > 0)
		temp = temp->sorted_next;
	temp_next = temp->sorted_next;
	temp->sorted_next = new;
	new->sorted_next = temp_next;
}

void	push_env(t_package *pack, char *name, char *val)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		exit(1);
	new->name = name;
	new->value = val;
	new->origin_next = 0;
	new->sorted_next = 0;
	if (!(pack->origin_head))
	{
		pack->origin_head = new;
		pack->origin_last = new;
		pack->sorted_head = new;
	}
	else
	{
		pack->origin_last->origin_next = new;
		pack->origin_last = new;
		append_sorted(&(pack->sorted_head), new);
	}
}

void	init(char **envp, t_package *package)
{
	int		i;
	char	*name;
	char	*value;
	char	*temp;

	i = 0;
	while (envp[i])
	{
		temp = ft_strchr(envp[i], '=');
		*temp = '\0';
		name = ft_strdup(envp[i]);
		value = ft_strdup(temp + 1);
		push_env(package, name, value);
		i++;
	}
}

void	print_env(t_env *head)
{
	while (head)
	{
		printf("env : %s=%s\n", head->name, head->value);
		head = head->origin_next;
	}
}

void	print_export(t_env *head)
{
	while (head)
	{
		printf("sorted: %s=%s\n", head->name, head->value);
		head = head->sorted_next;
	}
}

int	main(int argc, char *argv[], char **envp)
{
	char		*str;
	t_token		*head;

	(void)argc;
	(void)argv;
	package.origin_head = 0;
	init(envp, &package);
	print_env(package.origin_head);
	print_export(package.sorted_head);
	head = 0;
	while (1)
	{
		str = readline("minishell😎$ ");
		printf("\n[%s]\n", str);
		print_tok(lexer(str, &head));
		parser(head);
		add_history(str);
		free(str);
		clear_token_list(&head);
	}
	rl_clear_history();
	return (0);
}
