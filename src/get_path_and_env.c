/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_and_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 07:29:54 by asfletch          #+#    #+#             */
/*   Updated: 2024/01/23 07:45:46 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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
	my_write_three ("pipex: ", pipex.command[cmd_index].cmd, ": command not found", 2);
	clean_exit (pipex);
	exit (127);
}
