/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarekkkk <tarekkkk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:14:30 by tabadawi          #+#    #+#             */
/*   Updated: 2024/07/24 21:36:55 by tarekkkk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	initializer(t_shell *shell)
{
	shell->environ = NULL;
	shell->exec = NULL;
	shell->parser = NULL;
	shell->counter = NULL;
}

void	count_items(t_shell *shell, t_noding *traveler, t_counter *counter)
{
	(void)shell;
	counter->commands = 0;
	counter->inp_files = 0;
	counter->opt_files = 0;
	while (traveler && traveler->type != PIPES)
	{
		if (traveler->type == ARG)
			counter->commands++;
		if (traveler->type == OPT_FILE)
			counter->opt_files++;
		if (traveler->type == INP_FILE || traveler->type == DELIMITER)
			counter->inp_files++;
		traveler = traveler->next;
	}
}

//inp:
//0 = inpfile
//1 = here_doc

//opt:
//0 = optfile
//1 = append

void	setup_exec_struct(t_shell *shell)
{
	t_noding	*traveler;
	t_noding	*traveler2;

	int i = 0;
	int	command = 0;
	int opt_file = 0;
	int inp_file = 0;
	shell->counter = ft_malloc((sizeof(t_counter *) * (shell->parser->pipe_count + 2)), shell);
	shell->exec = ft_malloc((sizeof(t_exec *) * (shell->parser->pipe_count + 2)), shell);
	traveler = shell->parser->noding;
	while (traveler)
	{
		shell->counter[i] = ft_malloc(sizeof(t_counter), shell);
		shell->exec[i] = ft_malloc(sizeof(t_exec), shell);
		command = 0;
		opt_file = 0;
		inp_file = 0;
		traveler2 = traveler;
		count_items(shell, traveler2, shell->counter[i]);
		shell->exec[i]->cmd = ft_malloc((sizeof(char *) * (shell->counter[i]->commands + 1)), shell);
		shell->exec[i]->inp_files = ft_malloc((sizeof(char *) * (shell->counter[i]->inp_files + 1)), shell);
		shell->exec[i]->inp_flags = ft_malloc((sizeof(int) * (shell->counter[i]->inp_files + 1)), shell);
		shell->exec[i]->opt_files = ft_malloc((sizeof(char *) * (shell->counter[i]->opt_files + 1)), shell);
		shell->exec[i]->opt_flags = ft_malloc((sizeof(int) * (shell->counter[i]->opt_files + 1)), shell);
		while (traveler && traveler->type != PIPES)
		{
			if (traveler->type == ARG)
			{
				shell->exec[i]->cmd[command] = ft_strdup(traveler->value);
				command++;
			}
			if (traveler->type == OPT_REDIR)
			{
				shell->exec[i]->opt_files[opt_file] = ft_strdup(traveler->next->value);
				shell->exec[i]->opt_flags[opt_file] = 0;
				opt_file++;
			}
			if (traveler->type == APPEND)
			{
				shell->exec[i]->opt_files[opt_file] = ft_strdup(traveler->next->value);
				shell->exec[i]->opt_flags[opt_file] = 1;
				opt_file++;
			}
			if (traveler->type == INP_REDIR)
			{
				shell->exec[i]->inp_files[inp_file] = ft_strdup(traveler->next->value);
				shell->exec[i]->inp_flags[inp_file] = 0;
				inp_file++;
			}
			if (traveler->type == HERE_DOC)
			{
				shell->exec[i]->inp_files[inp_file] = ft_strdup(traveler->next->value);
				shell->exec[i]->inp_flags[inp_file] = 1;
				inp_file++;
			}
			traveler = traveler->next;
		}
		shell->exec[i]->cmd[command] = NULL;
		shell->exec[i]->opt_files[opt_file] = NULL;
		shell->exec[i]->inp_files[inp_file] = NULL;
		i++;
		if (traveler)
			traveler = traveler->next;
	}
	shell->exec[i] = NULL;
	shell->counter[i] = NULL;
}


void	printf_exec(t_shell *shell)
{
	int i = 0;
	int j = 0;
	while (shell->exec[i])
	{
		printf("set no. %d\n", i + 1);
		j = 0;
		printf("commands: ");
		while (shell->exec[i]->cmd[j])
		{
			printf("<<%s>> ", shell->exec[i]->cmd[j]);
			j++;		
		}
		printf("\n\n");
		j = 0;
		printf("inp files: ");
		while (shell->exec[i]->inp_files[j])
		{
			printf("<<%s>> ", shell->exec[i]->inp_files[j]);
			j++;		
		}
		printf("\n");
		j = 0;
		printf("inp types: ");
		while (j < shell->counter[i]->inp_files)
		{
			printf("<<%d>> ", shell->exec[i]->inp_flags[j]);
			j++;		
		}
		printf("\n\n");
		j = 0;
		printf("opt files: ");
		while (shell->exec[i]->opt_files[j])
		{
			printf("<<%s>> ", shell->exec[i]->opt_files[j]);
			j++;		
		}
		j = 0;
		printf("\n");
		printf("opt types: ");
		while (j < shell->counter[i]->opt_files)
		{
			printf("<<%d>> ", shell->exec[i]->opt_flags[j]);
			j++;		
		}
		printf("\n\n");
		i++;
	}
}

char	**set_up_path(t_shell *shell)
{
	t_values	*locate;

	char	**path;
	locate = locate_node(shell->environ->env, "PATH");
	if (!locate)
		return (NULL);
	path = ft_split(locate->value, ':');
	path[0] = ft_strtrim(path[0], "PATH=");
	return (path);
}

void	execution(t_shell *shell, int index)
{
	int i = 0;
	
	shell->environ->environment = arr(shell->environ->env, shell);
	shell->environ->path = set_up_path(shell);
	if (!access(shell->exec[index]->cmd[0], X_OK | F_OK))
		execve(shell->exec[index]->cmd[0], shell->exec[index]->cmd, shell->environ->environment);
	if (shell->environ->path)
	{
		while (shell->environ->path[i])
		{
			shell->exec[index]->cmdpath = ft_strjoin2(shell->environ->path[i], "/", shell->exec[index]->cmd[0]); 
			if (!access(shell->exec[index]->cmdpath, X_OK | F_OK))
				execve(shell->exec[index]->cmdpath, shell->exec[index]->cmd, shell->environ->environment);
			ft_free((void **)&shell->exec[index]->cmdpath);
			i++;
		}
		ft_putstr_fd(shell->exec[index]->cmd[0], 1);
		ft_putstr_fd(": command not found\n", 1);
		mass_free(shell, 127);
		exit(127);
	}
	exit(127);
}

void	child_dup(t_shell *shell, int index)
{
	int	fd_in;
	int	fd_out;
	close(shell->fd[0]);
	shell->fd[0] = -1;
	if (shell->exec[index]->inp_files)
	{
		fd_in = open(shell->exec[index]->inp_files[get_arrlen(shell->exec[index]->inp_files)], O_RDONLY);
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
		fd_in = -1;
	}
	else
	{
		if (index != 0)
		{
			dup2(shell->fd[1], STDIN_FILENO);
			close(shell->fd[1]);
			shell->fd[1] = -1;
		}
	}
	if (shell->exec[index]->opt_files)
	{
		if (shell->exec[index]->opt_flags[get_arrlen(shell->exec[index]->opt_files)])
			fd_out = open(shell->exec[index]->opt_files[get_arrlen(shell->exec[index]->opt_files)], O_WRONLY | O_CREAT | O_APPEND)
		else
			fd_out = open(shell->exec[index]->opt_files[get_arrlen(shell->exec[index]->opt_files)], O_WRONLY | O_CREAT | O_TRUNC)
		close(fd_out);
		fd_out = -1;
	}
	else
	{
		if (shell->exec[index + 1])
		{
			dup2(shell->fd)
		}
	}
}

void	parent_dup(t_shell *shell, int index)
{
	close(shell->fd[1]);
	shell->fd[1] = -1;
	dup2(shell->fd[0], STDIN_FILENO);
	close(shell->fd[0]);
	shell->fd[0] = -1;
}

void	exec_loop(t_shell *shell)
{
	int i = 0;
	while(shell->exec[i])
	{
		pipe(shell->fd);
		shell->child = fork();
		if (!shell->child)
		{
			child_dup(shell, i);
			execution(shell, i);
		}
		parent_dup(shell, i);
		shell->lastpid = shell->child;
		i++;
	}
}

void	waiting(t_shell *shell)
{
	pid_t	id = 0;
	int 	temp;

	while(id != -1)
	{
		id = wait(&temp);
		if (id == shell->lastpid)
			shell->environ->exit = WEXITSTATUS(temp);
	}
}

void	minishell(t_shell *shell)
{
	while (1)
	{
		signalhandler();
		ft_free((void **)&shell->environ->cwd);
		shell->environ->cwd = getcwd(NULL, 0);
		shell->str = readline("𝓯𝓻𝓮𝓪𝓴𝔂𝓼𝓱𝓮𝓵𝓵 > ");
		if (!shell->str)
			break ;
		if (strcmp(shell->str, "") == 0)
			continue ;
		if (shell->str[0] != '\0')
			add_history(shell->str);
		if (parsing_hub(shell, shell->str))
		{
			setup_exec_struct(shell);
			// printf_exec(shell);
			if (!builtin_check(shell))
				exec_loop(shell);
		}
		waiting(shell);
		free_tokenization(shell);
		free (shell->str);
	}
}

int	main(int ac, char **av, char **env)
{
	t_shell		shell;

	shell.environ = NULL;
	(void)av;
	if (ac != 1)
		return (-1);
	initializer(&shell);
	printf("\e[1;1H\e[2J");
	create_env(env, &shell);
	minishell(&shell);
	mass_free(&shell, shell.environ->exit);
}
