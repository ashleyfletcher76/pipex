/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_fam.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:41:31 by asfletch          #+#    #+#             */
/*   Updated: 2024/01/21 15:45:23 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_command(char *cmd, char **args, char **envp)
{
	char	*path;

	path = get_path(cmd, envp);
	if (path)
	{
		if (execve(path, args, NULL) == -1)
		{
			perror("execve");
			free (path);
			exit (EXIT_FAILURE);
		}
		free (path);
	}
	else
	{
		ft_printf("Command not found: %s\n", cmd);
		exit (EXIT_FAILURE);
	}
}

void	execute_child(t_pipex pipex, int i, char **envp)
{
	int		fd;
	char	*path;

	if (i == 0)
	{
		path = get_path(pipex.command[i].cmd, envp);
		dup2(pipex.infile, STDIN_FILENO);
		close(pipex.infile);
		dup2(pipex.fd[1], STDOUT_FILENO);
		close(pipex.fd[0]);
		close(pipex.fd[1]);
		execute_command(pipex.command[i].cmd, pipex.command[i].args, envp);
	}
	if (i == 1)
	{
		path = get_path(pipex.command[i].cmd, envp);
		fd = open(pipex.outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		dup2(pipex.fd[0], STDIN_FILENO);
		dup2(fd, STDOUT_FILENO);
		close(pipex.fd[0]);
		close(pipex.fd[1]);
		close(fd);
		execute_command(pipex.command[i].cmd, pipex.command[i].args, envp);
	}
}

void	wait_for_child(t_pipex pipex, int num_children)
{
	int	status;
	int	i;

	i = 0;
	while (i < num_children)
	{
		waitpid(pipex.pid[i], &status, 0);
		i++;
	}
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
}
