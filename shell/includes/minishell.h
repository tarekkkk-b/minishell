/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:15:11 by tabadawi          #+#    #+#             */
/*   Updated: 2024/08/11 13:04:43 by ahaarij          ###   ########.fr       */
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
# include <fcntl.h>
# include <sys/wait.h>
// # include <sys/syslimits.h>
// useful header ^^^
# include <readline/history.h>
# include <readline/readline.h>
# include "../../libft/libft.h"

//		definitions		//

typedef struct s_environ	t_environ;
typedef struct s_exec		t_exec;
typedef struct s_parser		t_parser;
typedef struct s_counter	t_counter;

# define READ_PIPE 0
# define WRITE_PIPE 1

extern int					g_signalnumber;

//		shell struct		//
typedef struct s_shell
{
	int			fd;
	int			temp_in;
	int			temp_out;
	pid_t		child;
	pid_t		lastpid;
	char		*str;
	t_environ	*environ;
	t_parser	*parser;
	t_exec		**exec;
	t_counter	**counter;
}	t_shell;

//		env structs		//
typedef struct s_values
{
	char			*key;
	char			*value;
	char			*string;
	t_shell			*shell;
	struct s_values	*next;
}	t_values;

typedef struct s_environ
{
	int			exit;
	int			shlvl;
	char		*cwd;
	char		*owd;
	char		**path;
	char		**environment;
	t_values	*env;
	t_shell		*shell;
}	t_environ;

//		parsing structs		//

typedef enum s_tokens
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

typedef struct s_noding
{
	char			*value;
	t_tokens		type;
	int				pop_out;
	struct s_noding	*next;
	t_shell			*shell;
}	t_noding;

typedef struct s_parser
{
	int			pipe_count;
	t_noding	*noding;
	t_shell		*shell;
}	t_parser;

//		exec struct		//

typedef struct s_counter
{
	int		commands;
	int		inp_files;
	int		opt_files;
}	t_counter;

typedef struct s_exec
{
	int				fd[2];
	int				heredoc_fd;
	char			**cmd;
	char			**opt_files;
	int				*opt_flags;
	char			**inp_files;
	int				*inp_flags;
	char			*cmdpath;
	t_shell			*shell;
}	t_exec;

typedef struct s_export
{
	char		*key;
	char		*equal;
	char		*value;
}	t_export;

typedef struct s_indices
{
	int			i;
	int			j;
}	t_indices;

//			parsing			//

int			parsing_hub(t_shell *shell, char *str);
int			assign_space(char *str, int index, t_shell *shell);
int			assign_word(char *str, int index, t_shell *shell);
int			valid_name(char character, int current, int first);
int			end_of_var(char *str, int start, int index, int res);
int			assign_variable(char *str, int index, t_shell *shell);
int			assign_redirection(char *str, int index, t_shell *shell);
int			assign_quotes(char *str, int index, t_shell *shell);
int			invalid_token(t_shell *shell);
int			operater_tokens(t_noding *node);
int			delimeter_char(char character);
int			invalid_chars(char c);
void		assignation(t_shell *shell, char *str);
void		assign_node(t_shell *shell, t_noding *new, t_tokens type, \
int popout);
void		assign_pipe(t_shell *shell);
void		assign_invalid(t_shell *shell, char *str, int index);
void		add_token(t_shell *shell, t_noding *new);
void		popout_token(t_shell *shell, t_noding *token);
void		add_token(t_shell *shell, t_noding *new);
void		get_delimeter(t_shell *shell);
void		quotes(t_shell *shell);
void		expand_vars(t_shell *shell);
void		join_tokens(t_shell *shell);
void		assign_files(t_shell *shell);
t_noding	*prev_node(t_shell *shell, t_noding *target);
t_noding	*last_node(t_noding *nodes);
t_noding	*prev_node(t_shell *shell, t_noding *target);
t_noding	*last_node(t_noding *nodes);
//			others		//

// int		just_test(t_readline rl);
int			get_arrlen(char **arr);
int			signalhandler(int i);
int			ft_lstsizee(t_values *lst);
int			checker(t_shell *shell);
char		*ft_strjoin2(char *str1, char *str2, char *str3);
char		*get_key(char *env_var, t_shell *shell);
char		**arr(t_values *environ, t_shell *shell);
void		change_node(t_values *node, char *new);
// void		assign_nodes(char **env, t_shell *shell, t_values *node, int i);
void		create_env(char **env, t_shell *shell);
void		addnode(t_environ *environ, t_values *node);
void		custom_node(t_shell *shell, char *key, char *value);
void		adjust_lvl(t_shell *shell);
void		popout(t_shell	*shell, char *target);
// void		free_values(t_values *env);
// void		free_node(t_values *node);
// void		free_list(t_values *head);
void		recieve_str(t_shell *shell, char *str);
void		handle_sigint(int sig);
void		rl_replace_line(const char *s, int c);
void		*ft_malloc(size_t size, t_shell *shell);
void		ft_free(void **ptr);
void		free_env(t_shell *shell);
void		free_tokenization(t_shell *shell);
void		mass_free(t_shell *shell, int exit);
t_values	*lstlast(t_values *lst);
t_values	*locate_node(t_values *temp, char *target_key);

//**	builtins & its utils	**//

int			builtin_check(t_shell *shell, int index, int flag);
int			builtin_env(t_environ *environ);
int			builtin_exit(t_shell *shell, int argc, int index);
int			builtin_pwd(t_shell *shell);
int			builtin_echo(t_shell *shell, int index, int i);
int			builtin_cd(t_shell *shell, int i, int args);
int			builtin_unset(t_shell *shell, int argc, int i);
int			update_pwd(t_shell *shell, char *directory);
int			change_nodeee(t_values *node, char *new);
int			is_num(char *str);
int			export(int argc, t_shell *shell, int i);
int			count_values(t_values *env);
int			check_invalid(char *str);
int			check_inp_files(t_shell *shell, int index);
int			check_opt_files(t_shell *shell, int index);
int			waiting_heredoc(t_shell *shell, pid_t id);
int			opt_file_dup(t_exec	*exec);
int			inp_file_dup(t_exec	*exec);
char		*get_directory(int args_count, t_shell *shell, int i);
char		*find_node_aarij(t_values *temp, char *target_key);
void		sort_it_out(char **arr, int n, int i, int j);
void		printarray(char **arr, int n, t_shell *shell);
void		ft_close(t_shell *shell, int *fd);
void		free_exec(t_shell *shell);
void		setup_exec_struct(t_shell *shell);
void		count_items(t_shell *shell, t_noding *traveler, t_counter *counter);
char		**set_up_path(t_shell *shell);
void		exec_loop(t_shell *shell);
void		execution(t_shell *shell, int index);
void		inp_dup(t_shell *shell, int index, int temp_fd);
void		ft_close(t_shell *shell, int *fd);
void		opt_dup(t_shell *shell, int index);
void		collect_heredoc(t_shell *shell, int index);
void		do_nothing(int sig);
void		waiting(t_shell *shell);
void		mass_close(t_shell *shell);
void		closer(t_shell *shell, t_exec *exec, int f1, int f2);
char		*ft_strncpy(char *dest, const char *src, int n);
int			ft_strcmpaarij(char *s1, char *s2);
int			mass_check(char *str);
void		dupingcall(t_shell *shell, int i);
int			heredoc(t_shell *shell, t_exec *exec, pid_t id, int i);
int			check_heredoc(t_exec *exec);
void		first_cmd(t_shell *shell, t_exec *exec);
void		middle_cmd(t_shell *shell, t_exec *exec);
void		last_cmd(t_shell *shell, t_exec *exec);
int			ft_strcmp(char *str1, char *str2);

#endif