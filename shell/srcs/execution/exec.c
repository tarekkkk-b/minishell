/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:45:53 by tabadawi          #+#    #+#             */
/*   Updated: 2024/08/05 12:51:02 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void exec_loop(t_shell *shell)
{
    int i = 0;
    int temp_fd = -1;
	pid_t	id = 0;
	int 	temp;
    
    while (shell->exec[i])
    {
        if (shell->exec[i + 1])
            pipe(shell->exec[i]->fd);
		if(shell->exec[i]->inp_flags && shell->exec[i]->inp_flags[0] == 1)
		{		
			signal(SIGINT, SIG_IGN);		
			signal(SIGQUIT, SIG_IGN);		
			shell->child = fork();
			if (!shell->child)
			{
				signal(SIGINT, do_nothing);
				collect_heredoc(shell, i);
				ft_close(shell, &shell->exec[i]->fd[READ_PIPE]);
				ft_close(shell, &shell->exec[i]->fd[WRITE_PIPE]);
				mass_free(shell, 0);
			}
			while(id != -1)
			{
				id = wait(&temp);
				if (id == shell->lastpid)
					if (WEXITSTATUS(temp) == 1)
						return;
			}
		}
		if (check_inp_files(shell, i) && check_opt_files(shell, i))
		{
			signal(SIGINT, SIG_IGN);		
			signal(SIGQUIT, SIG_IGN);		
        	shell->child = fork();
        	if (shell->child == 0)
        	{
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, SIG_DFL);
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
				inp_dup(shell, i, temp_fd);
				opt_dup(shell, i);
				ft_close(shell, &shell->exec[i]->fd[READ_PIPE]);
				ft_close(shell, &shell->exec[i]->fd[WRITE_PIPE]);
				ft_close(shell, &temp_fd);
				unlink("/tmp/.here_i_doc");
				if(builtin_check(shell, i, 1) != 0)
        	    	execution(shell, i);
        	    mass_free(shell, shell->environ->exit);
        	}
        	else if (shell->child > 0)
        	{
        	    if (i > 0)
        	        ft_close(shell, &temp_fd);
        	    if (shell->exec[i + 1])
        	    {
        	        ft_close(shell, &shell->exec[i]->fd[WRITE_PIPE]);
        	        temp_fd = shell->exec[i]->fd[READ_PIPE];
				}
				else
				{
					ft_close(shell, &shell->exec[i]->fd[READ_PIPE]);
					ft_close(shell, &shell->exec[i]->fd[WRITE_PIPE]);
					ft_close(shell, &temp_fd);					
				}
				builtin_check(shell, i, 0);
			}
		}
		i++;
	}
}


void	execution(t_shell *shell, int index)
{
	int i = 0;
	
	shell->environ->environment = arr(shell->environ->env, shell);
	shell->environ->path = set_up_path(shell);
	if (!access(shell->exec[index]->cmd[0], F_OK))
	{
		 if (access(shell->exec[index]->cmd[0], X_OK) == -1)
		{
			ft_putstr_fd(shell->exec[index]->cmd[0], 1);
			ft_putstr_fd(": Permission denied\n", 1);
			shell->environ->exit = 126;
			mass_free(shell, 126);
		}
		else
			execve(shell->exec[index]->cmd[0], shell->exec[index]->cmd, shell->environ->environment);
	}
	if (shell->environ->path)
	{
		while (shell->environ->path[i] && shell->exec[index]->cmd[0])
		{
			shell->exec[index]->cmdpath = ft_strjoin2(shell->environ->path[i], "/", shell->exec[index]->cmd[0]); 
			if (!access(shell->exec[index]->cmdpath, F_OK))
			{
				if (access(shell->exec[index]->cmdpath, X_OK) == -1)
				{
					ft_putstr_fd(shell->exec[index]->cmd[0], 1);
					ft_putstr_fd(": Permission denied\n", 1);
					shell->environ->exit = 126;
					mass_free(shell, 126);
				}
				else
					execve(shell->exec[index]->cmdpath, shell->exec[index]->cmd, shell->environ->environment);
			}
			ft_free((void **)&shell->exec[index]->cmdpath);
			i++;
		}
		ft_putstr_fd(shell->exec[index]->cmd[0], 1);
		ft_putstr_fd(": command not found\n", 1);
		mass_free(shell, 127);
	}
}
