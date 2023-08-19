
#ifndef LEXER_H
# define LEXER_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

enum	e_types
{
	L_ERROR = -1,
	L_WORD,
	L_SPACE,
	L_PIPE,
	L_LESSER,
	L_GREATER
};

typedef struct s_token
{
	enum e_types	type;
	char			*data;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

t_token	*lexer(char *readline, t_token **head);
void	clear_token_list(t_token **head);

#endif
