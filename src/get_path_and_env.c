/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_and_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 07:29:54 by asfletch          #+#    #+#             */
/*   Updated: 2024/01/23 15:59:56 by asfletch         ###   ########.fr       */
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
	return ("NULL");
}

char	*check_absolute_path(char *cmd)
{
	if (cmd[0] == '/' || ft_strncmp (cmd, "./", 2) == 0
		|| ft_strncmp (cmd, "../", 3) == 0)
		return (ft_strdup(cmd));
	return (NULL);
}

char	*search__in_path(t_pipex pipex, int cmd_index, char *env_path)
{
	int		i;
	char	**all_paths;
	char	*temp_path;
	char	*full_path;

	i = 0;
	all_paths = ft_split(env_path, ':');
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
			return (free_arr(all_paths), full_path);
		i++;
		free (full_path);
	}
	my_write_two ("zsh: command not found: ", pipex.command[cmd_index].cmd, 2);
	return (clean_exit(pipex), free_arr (all_paths), exit (127), NULL);
}

char	*get_path(t_pipex pipex, int cmd_index, char **envp)
{
	char	*path;
	char	*path_env;

	path = check_absolute_path(pipex.command[cmd_index].cmd);
	if (path != NULL)
		return (path);
	if (envp != NULL)
		path_env = get_env("PATH", envp);
	else
		path_env = NULL;
	if (path_env == NULL)
	{
		clean_exit (pipex);
		exit (0);
	}
	path = search__in_path(pipex, cmd_index, path_env);
	if (path_env == NULL)
	{
		my_write_three ("pipex: ", pipex.command[cmd_index].cmd,
			": command not found", 2);
		clean_exit (pipex);
		exit (126);
	}
	return (path);
}
