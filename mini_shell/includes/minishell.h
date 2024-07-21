/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:15:11 by tabadawi          #+#    #+#             */
/*   Updated: 2024/07/21 21:44:41 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//		libraries		//

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <string.h>
// # include <sys/syslimits.h>
// useful header ^^^
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
	char		*str;
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
	COMMAND,
	ARG,
	PIPES,
	INP_REDIR,
	INP_FILE,
	OPT_REDIR,
	OPT_FILE,
	HERE_DOC,
	DELIMITER,
	APPEND,
	SPACES,
	VARIABLE,
	DQUOTES,
	INVALID
}	t_tokens;

typedef struct	s_noding
{
	char			*value;
	t_tokens		type;
	int				pop_out;
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


//			parsing			//

int			parsing_hub(t_shell *shell, char *str);
void		assignation(t_shell *shell, char *str);
void		assign_pipe(t_shell *shell);
int			assign_space(char *str, int index, t_shell *shell);
void		assign_invalid(t_shell *shell, char *str, int index);
int			assign_word(char *str, int index, t_shell *shell);
void		assign_node(t_shell *shell, t_noding *new, t_tokens type, int popout);
int			valid_name(char character, int current, int first);
int			end_of_var(char *str, int start, int index, int res);
int			assign_variable(char *str, int index, t_shell *shell);
int			assign_redirection(char *str, int index, t_shell *shell);
int			assign_quotes(char *str, int index, t_shell *shell);
void		add_token(t_shell *shell, t_noding *new);
void		popout_token(t_shell *shell, t_noding *token);
t_noding	*prev_node(t_shell *shell, t_noding *target);
t_noding	*last_node(t_noding *nodes);
int			invalid_token(t_shell *shell);
int			operater_tokens(t_noding *node);
int			delimeter_char(char character);
int			invalid_chars(char c);
void		add_token(t_shell *shell, t_noding *new);
t_noding	*prev_node(t_shell *shell, t_noding *target);
t_noding	*last_node(t_noding *nodes);
void		get_delimeter(t_shell *shell);
void		quotes(t_shell *shell);
void		expand_vars(t_shell *shell);
void		join_tokens(t_shell *shell);
void		assign_files(t_shell *shell);

//			others			//

// void		assign_nodes(char **env, t_shell *shell, t_values *node, int i);
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
// void		free_values(t_values *env);
// void    free_node(t_values *node);
// void    free_list(t_values *head);
void	recieve_str(t_shell *shell, char *str);
int    signalhandler(void);
void    handle_sigint(int sig);
void 	rl_replace_line (const char * s, int c);
// int		just_test(t_readline rl);
t_values	*locate_node(t_values *temp, char *target_key);

int    	checker(t_shell *shell);
void	*ft_malloc(size_t size);
void	ft_free(void **ptr);
void	free_env(t_shell *shell);
void	free_tokenization(t_shell *shell);
void    mass_free(t_shell *shell);


//**	builtins	**//

// int 	builtin_check(t_readline rl, t_shell *shell);
int 	builtin_env(t_environ *environ);
// int 	builtin_exit(t_readline rl);
int		builtin_pwd(t_shell *shell);
int 	builtin_echo(char *str);
int 	builtin_cd(t_shell *shell);

int 	update_pwd(t_shell *shell, char *directory);
char    *get_directory(int args_count, t_shell *shell);
char	*find_node_aarij(t_values *temp, char *target_key);
int 	change_nodeee(t_values *node, char *new);

#endif