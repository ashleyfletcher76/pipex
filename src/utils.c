/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 09:24:27 by asfletch          #+#    #+#             */
/*   Updated: 2024/01/22 19:28:50 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	open_the_files(t_pipex *pipex, int index)
{
	if (index == 0)
	{
		pipex->infile_fd = open(pipex->infile, O_RDONLY);
		if (pipex->infile_fd == -1)
		{
			my_three_write ("pipex: ", pipex->infile, ": No such file or directory", 2);
			clean_exit (*pipex);
			exit (EXIT_FAILURE);
		}
	}
	if (index == 1)
	{
		pipex->outfile_fd = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (pipex->outfile_fd == - 1)
		{
			perror ("pipex: output\n");
			clean_exit (*pipex);
			exit (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

char	*get_env(const char *name, char **envp)
{
	int	i;
	int	len;

	len = ft_strlen(name);
	i = 0;
	while (envp[i] != NULL)
	{
		if (strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
	//return (envp[0]);
}

char	*get_path(t_pipex pipex, int cmd_index, char **envp)
{
	int		i;
	char	**all_paths;
	char	*temp_path;
	char	*full_path;

	i = 0;
	if (pipex.command[cmd_index].cmd[0] == '/')
		return strdup(pipex.command[cmd_index].cmd);
	all_paths = ft_split(get_env("PATH", envp), ':');
	if (!all_paths)
	{
		clean_exit (pipex);
		exit (EXIT_FAILURE);
	}
	while (all_paths[i] != NULL)
	{
		temp_path = ft_strjoin(all_paths[i], "/");
		full_path = ft_strjoin(temp_path, pipex.command[cmd_index].cmd);
		free (temp_path);
		if (access(full_path, X_OK) == 0)
		{
			free_arr (all_paths);
			return (full_path);
		}
		i++;
		free (full_path);
	}
	free_arr (all_paths);
	// free (full_path);
	my_two_write("zsh: command not found: ", pipex.command[cmd_index].cmd, 2);
	clean_exit (pipex);
	exit (127);
}

void	my_two_write(char *s, char *s1, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putstr_fd(s1, fd);
	ft_putchar_fd('\n', fd);
}

void	my_three_write(char *s, char *s1, char *s2, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putstr_fd(s1, fd);
	ft_putstr_fd(s2, fd);
	ft_putchar_fd('\n', fd);
}
