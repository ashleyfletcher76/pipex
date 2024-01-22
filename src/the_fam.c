/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_fam.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:41:31 by asfletch          #+#    #+#             */
/*   Updated: 2024/01/22 17:12:50 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	execute_command(t_pipex pipex, int i, char **envp)
{
	if (pipex.path)
	{
		if (execve(pipex.path, pipex.command[i].args, envp) == -1)
		{
			perror("execve");
			free (pipex.path);
			clean_exit (pipex);
			exit (127);
		}
		free (pipex.path);
	}
	else
	{
		// ft_printf("Command not found: %s\n", pipex.command[i].cmd);
		my_two_write("Command not found: ", pipex.command[i].cmd, 127);
		clean_exit (pipex);
		exit (126);
	}
}

void	execute_child_one(t_pipex pipex, int i, char **envp)
{
	if (i == 0)
	{
		open_the_files(&pipex, 0);
		pipex.path = get_path(pipex, i, envp);
		if (!pipex.path)
		{
			//fprintf(stderr, "Debug: Command not found - %s\n", pipex.command[i].cmd);
			my_three_write("env: ", pipex.command[i].cmd, ": No such file or directory", 2);
			clean_exit (pipex);
			exit (127);
		}
		if (dup2(pipex.infile_fd, STDIN_FILENO) == - 1)
		{
			close (pipex.infile_fd);
			close_fds (pipex);
			clean_exit (pipex);
			exit (EXIT_FAILURE);
		}
		close(pipex.infile_fd);
		if (dup2(pipex.fd[1], STDOUT_FILENO) == - 1)
		{
			close_fds (pipex);
			clean_exit (pipex);
			exit (EXIT_FAILURE);
		}
		close_fds (pipex);
		execute_command(pipex, i, envp);
	}
	if (i == 1)
		execute_child_two(pipex, i, envp);
}

void	execute_child_two(t_pipex pipex, int i, char **envp)
{
	open_the_files (&pipex, 1);
	pipex.path = get_path(pipex, i, envp);
	if (dup2(pipex.fd[0], STDIN_FILENO) == - 1)
	{
		close_fds (pipex);
		close(pipex.outfile_fd);
		clean_exit (pipex);
		exit (EXIT_FAILURE);
	}
	if (dup2(pipex.outfile_fd, STDOUT_FILENO) == - 1)
	{
		close_fds (pipex);
		close(pipex.outfile_fd);
		clean_exit (pipex);
		exit (EXIT_FAILURE);
	}
	close_fds (pipex);
	close(pipex.outfile_fd);
	execute_command(pipex, i, envp);
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
	{
		exit(WEXITSTATUS(status));
	}
}
