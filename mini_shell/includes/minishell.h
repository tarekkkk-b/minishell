/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:15:11 by tabadawi          #+#    #+#             */
/*   Updated: 2024/06/24 10:00:32 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//		libraries		//

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "../../libft/libft.h"

//		definitions		//

typedef struct	s_environ	t_environ;
typedef	struct	s_exec		t_exec;
typedef struct	s_parser	t_parser;

//		shell struct		//

typedef	struct	s_shell
{
	pid_t		child;
	pid_t		lastpid;
	t_environ	*environ;
	t_parser	*parser;
	t_exec		*exec;
}	t_shell;

//		env structs		//

typedef	struct	s_values
{
	char			*key;
	char			*value;
	char			*string;
	t_shell			*shell;
	struct s_values	*next;
}	t_values;

typedef struct	s_environ
{
	int			exit;
	int			shlvl;
	char		*cwd;
	char		*owd;
	char		**path;
	t_values	*env;
	t_shell		*shell;
}	t_environ;

//		parsing structs		//

typedef enum	s_tokens
{
	command,
	option,
	pipes,
	inp_redir,
	inp_file,
	opt_redir,
	opt_file,
	here_doc,
	delimiter,
	append,
	space,
	variable,
	invalid
}	t_tokens;

typedef struct	s_noding
{
	char			*value;
	t_tokens		type;
	struct s_noding	*next;
	t_shell			*shell;
}	t_noding;

typedef struct	s_parser
{
	t_noding	*noding;
	t_shell		*shell;
}	t_parser;

//		exec struct		//

typedef	struct	s_exec
{
	int				*fd;
	int				redirections;
	char			**cmd;
	char			**files;
	char			*cmdpath;
	char			*src;
	char			*final_destination;
	t_shell			*shell;
	struct s_exec	*next;
}	t_exec;

void		assign_nodes(char **env, t_shell *shell, t_values *node, int i);
char    	*ft_strjoin2(char *str1, char *str2, char *str3);
char		*get_key(char *env_var);
char		**arr(t_values *environ);
void		create_env(char **env, t_shell *shell);
void		addnode(t_environ *environ, t_values *node);
t_values	*lstlast(t_values *lst);
int			get_arrlen(char **arr);
void		custom_node(t_shell *shell, char *key, char *value);
void		adjust_lvl(t_shell *shell);
void		popout(t_shell	*shell, char *target);
void		free_values(t_values *env);
// void    free_node(t_values *node);
// void    free_list(t_values *head);
void	recieve_str(t_shell *shell, char *str);


#endif