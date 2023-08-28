/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:38:48 by dongseo           #+#    #+#             */
/*   Updated: 2023/08/27 22:27:34 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "lexer.h"
# include "env_utils.h"

typedef struct s_redir
{
	char			**filename;
	int				fd;
	enum e_type		type;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**cmd_args;
	int				prev_fd;
	t_redir			*redirection;
	t_redir			*infile;
	t_redir			*outfile;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

// yusekim typedef
typedef struct s_cmd_info
{
	char	***cmds;
	char	*str;
	int		idx;
	int		len;
	int		flag;
	int		expand_flag;
}	t_cmd_info;

t_cmd	*parser(t_token *head);
int		check_syntax(t_token *head);
t_token	*build_simple_cmd(t_cmd **head, t_cmd **last, t_token *tok_head);
void	append_redir(t_cmd *new_cmd, t_token **temp);
char	**expand_scanner(char ***cmds, char *data, int check);
void	init_info(t_cmd_info *info, char ***cmds);
int		is_target(char c, int flag, int check);
int		check_envlen(char *str);
char	**add_str(char **str, char *add);
void	update_string(t_cmd_info *info, char *data, int cur_flag, int exp_flag);
char	*expand(t_cmd_info *info, char *data);
char	*split_join(t_cmd_info *info, t_env *env);
char	*check_split(t_cmd_info *info, t_env *env, char **split);
char	*join_n_add(t_cmd_info *info, char *split);
void	free_strings(char **strings);

#endif
