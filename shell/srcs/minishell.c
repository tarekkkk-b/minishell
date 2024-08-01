/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:14:30 by tabadawi          #+#    #+#             */
/*   Updated: 2024/08/01 11:20:25 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	initializer(t_shell *shell)
{
	shell->environ = NULL;
	shell->exec = NULL;
	shell->parser = NULL;
	shell->counter = NULL;
	shell->fd = -1;
	shell->lastpid = -1;
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
		shell->exec[i]->fd[0] = -1;
		shell->exec[i]->fd[1] = -1;
		shell->exec[i]->heredoc_fd = -1;
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
		while (shell->environ->path[i] && shell->exec[index]->cmd[0])
		{
			shell->exec[index]->cmdpath = ft_strjoin2(shell->environ->path[i], "/", shell->exec[index]->cmd[0]); 
			if (!access(shell->exec[index]->cmdpath, X_OK | F_OK))
				execve(shell->exec[index]->cmdpath, shell->exec[index]->cmd, shell->environ->environment);
			ft_free((void **)&shell->exec[index]->cmdpath);
			i++;
		}
		if(shell->exec[index]->cmd[0] != NULL)
		{
			ft_putstr_fd(shell->exec[index]->cmd[0], 1);
			ft_putstr_fd(": command not found\n", 1);
		}
		mass_free(shell, 127);
		exit(127);
	}
	exit(127);
}

void	ft_close(t_shell *shell, int *fd)
{
	if ((*fd) >= 0)
		if (close(*fd) == -1)
			mass_free(shell, 1);
	(*fd) = -1;
}

void	inp_dup(t_shell *shell, int index, int temp_fd)
{
	int	fd;

	fd = -1;
	if (shell->exec[index]->inp_files && shell->exec[index]->inp_files[0])
	{
		if (shell->exec[index]->inp_flags[get_arrlen(shell->exec[index]->inp_files) - 1] == 1)
			fd = open("/tmp/.here_i_doc", O_RDONLY);
		else if (shell->exec[index]->inp_flags[get_arrlen(shell->exec[index]->inp_files) - 1] == 0)
			fd = open(shell->exec[index]->inp_files[get_arrlen(shell->exec[index]->inp_files) - 1], O_RDONLY);
		dup2(fd, STDIN_FILENO);
		ft_close(shell, &fd);
	}
	else if (index != 0)
		dup2(temp_fd, STDIN_FILENO);
	ft_close(shell, &shell->exec[index]->fd[READ_PIPE]);
}


void	opt_dup(t_shell *shell, int index)
{
	int	fd;

	fd = -1;
	if (shell->exec[index]->opt_files && shell->exec[index]->opt_files[0])
	{
		if (shell->exec[index]->opt_flags[get_arrlen(shell->exec[index]->opt_files) - 1])
			fd = open(shell->exec[index]->opt_files[get_arrlen(shell->exec[index]->opt_files) - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (!shell->exec[index]->opt_flags[get_arrlen(shell->exec[index]->opt_files) - 1])
			fd = open(shell->exec[index]->opt_files[get_arrlen(shell->exec[index]->opt_files) - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fd, STDOUT_FILENO);
		ft_close(shell, &fd);
	}
	else if (shell->exec[index + 1])
		dup2(shell->exec[index]->fd[WRITE_PIPE], STDOUT_FILENO);
	ft_close(shell, &shell->exec[index]->fd[WRITE_PIPE]);
}

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	if (!str1 || !str2)
		return (1);
	i = -1;
	if (ft_strlen(str1) == ft_strlen(str2))
	{
		while (str1[++i])
			if (str1[i] != str2[i])
				return (1);
	}
	else
		return (1);
	return (0);
}

void	collect_heredoc(t_shell *shell, int index)
{
	int		i;
	char	*str;

	i = -1;
	if (!shell->exec[index]->inp_files || !shell->exec[index]->inp_files[0])
		return ;
	while (shell->exec[index]->inp_files[++i])
	{
		if (shell->exec[index]->inp_flags[i])
		{
			signalhandler(2);
			shell->exec[index]->heredoc_fd = open("/tmp/.here_i_doc", O_CREAT | O_TRUNC | O_WRONLY, 0620);
			while (1)
			{
				str = readline("> ");
				if(g_signalnumber == SIGINT)
				{
					ft_close(shell, &shell->exec[index]->heredoc_fd);
					exit(1);
				}
				if(!str || (ft_strcmp(str, shell->exec[index]->inp_files[i]) == 0))
					break;
				str = ft_strjoin(str, "\n", 1);
				ft_putstr_fd(str, shell->exec[index]->heredoc_fd);
				ft_free((void **)&str);
			}
			ft_close(shell, &shell->exec[index]->heredoc_fd);
		}
	}
}

// void	collect_heredoc(t_shell *shell, int index)
// {
// 	int		i;
// 	char	*str;

// 	i = -1;
// 	if (!shell->exec[index]->inp_files || !shell->exec[index]->inp_files[0])
// 		return ;
// 	while (shell->exec[index]->inp_files[++i])
// 	{
// 		if (shell->exec[index]->inp_flags[i])
// 		{
// 			shell->exec[index]->heredoc_fd = open("/tmp/.here_i_doc", O_CREAT | O_TRUNC | O_WRONLY, 0620);
// 			str = readline("> ");
// 			while (str && (ft_strcmp(str, shell->exec[index]->inp_files[i]) != 0))
// 			{
// 				str = ft_strjoin(str, "\n", 1);
// 				ft_putstr_fd(str, shell->exec[index]->heredoc_fd);
// 				ft_free((void **)&str);
// 				str = readline("> ");
// 			}
// 			ft_close(shell, &shell->exec[index]->heredoc_fd);
// 		}
// 	}
// }

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

int	check_inp_files(t_shell *shell, int index)
{
	int i = 0;
	int fd= -1;
	while (shell->exec[index]->inp_files[i])
	{
		if (!shell->exec[index]->inp_flags[i])
		{
			fd = open(shell->exec[index]->inp_files[i], O_RDONLY);
			if (fd == -1)
			{
				printf("%s: no such file or directory found.\n", shell->exec[index]->inp_files[i]);
				return (0);
			}
			else
				ft_close(shell, &fd);
		}
		i++;
	}
	return (1);
}

int	check_opt_files(t_shell *shell, int index)
{
	int i = 0;
	int fd= -1;
	while (shell->exec[index]->opt_files[i])
	{
		if (!shell->exec[index]->opt_flags[i])
			fd = open(shell->exec[index]->opt_files[i], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else
			fd = open(shell->exec[index]->opt_files[i], O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd == -1)
		{
			printf("%s: couldn't open file.\n", shell->exec[index]->opt_files[i]);
			return (0);
		}
		else
			ft_close(shell, &fd);
		i++;
	}
	return (1);
}

void exec_loop(t_shell *shell)
{
    int i = 0;
    int temp_fd = -1;
	int j = 0;
    
    while (shell->exec[i])
    {
        if (shell->exec[i + 1])
            pipe(shell->exec[i]->fd);
		if(shell->exec[i]->inp_flags[0] == 1)
		{
			shell->child = fork();
			if (!shell->child)
			{
				collect_heredoc(shell, i);
				ft_close(shell, &shell->exec[i]->fd[READ_PIPE]);
				ft_close(shell, &shell->exec[i]->fd[WRITE_PIPE]);
				mass_free(shell, 0);
			}
		}
        shell->child = fork();
        if (shell->child == 0)
        {
            if (i == 0)
            {
                if (shell->exec[i + 1])
                    dup2(shell->exec[i]->fd[WRITE_PIPE], STDOUT_FILENO);
            }
            else if (shell->exec[i + 1]) // any command thats not the firs
            {
                dup2(temp_fd, STDIN_FILENO);
                dup2(shell->exec[i]->fd[WRITE_PIPE], STDOUT_FILENO);
            }
            else // this one is fro last command
            {
                dup2(temp_fd, STDIN_FILENO);
            }
			j = 0;
            while (j <= i) //ckose all fds
            {
                close(shell->exec[j]->fd[READ_PIPE]);
                close(shell->exec[j]->fd[WRITE_PIPE]);
				j++;
            }
			if(builtin_check(shell, i, 1) != 0)
            	execution(shell, i);
            exit(shell->environ->exit);
        }
        else if (shell->child > 0)
        {
            if (i > 0)
                close(temp_fd);
            if (shell->exec[i + 1])
            {
                close(shell->exec[i]->fd[WRITE_PIPE]);
                temp_fd = shell->exec[i]->fd[READ_PIPE];
            }
			else
			{
				close(shell->exec[i]->fd[READ_PIPE]);
				close(shell->exec[i]->fd[WRITE_PIPE]);
			}
			builtin_check(shell, i, 0);
			i++;
		}
	}
	// wit for all child processes to finish
	j = 0;
	while(j < i)
	{
		wait(NULL);
		j++;
	}
}

// void	exec_loop(t_shell *shell)
// {
// 	int	i;
// 	i = 0;
// 	while(shell->exec[i])
// 	{
// 		pipe(shell->exec[i]->fd);
// 		shell->child = fork();
// 		if (!shell->child)
// 		{
// 			collect_heredoc(shell, i);
// 			ft_close(shell, &shell->exec[i]->fd[READ_PIPE]);
// 			ft_close(shell, &shell->exec[i]->fd[WRITE_PIPE]);
// 			mass_free(shell, 0);
// 		}
// 		waiting(shell);
// 		if (check_inp_files(shell, i) && check_opt_files(shell, i))
// 		{
// 			shell->child = fork();
// 			if (!shell->child)
// 			{
// 				inp_dup(shell, i, shell->fd);
// 				ft_close(shell, &shell->fd);
// 				opt_dup(shell, i);
// 				ft_close(shell, &shell->exec[i]->heredoc_fd);
// 				unlink("/tmp/.here_i_doc");
// 				if (builtin_check(shell, i, 1) != 0)
// 					execution(shell, i);
// 			}
// 			builtin_check(shell, i, 0);
// 			ft_close(shell, &shell->exec[i]->heredoc_fd);
// 			ft_close(shell, &shell->fd);
// 			shell->fd = dup(shell->exec[i]->fd[READ_PIPE]);
// 			ft_close(shell, &shell->exec[i]->fd[READ_PIPE]);
// 			ft_close(shell, &shell->exec[i]->fd[WRITE_PIPE]);
// 			shell->lastpid = shell->child;
// 		}
// 		i++;
// 	}
// 	ft_close(shell, &shell->fd);
// }

void	minishell(t_shell *shell)
{
	if (!isatty(0))
		rl_outstream = stdin;
	while (1)
	{
		signalhandler(1);
		ft_free((void **)&shell->environ->cwd);
		shell->environ->cwd = getcwd(NULL, 0);
		if (isatty(0))
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
	create_env(env, &shell);
	minishell(&shell);
	mass_free(&shell, shell.environ->exit);
}
