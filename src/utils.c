/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 09:24:27 by asfletch          #+#    #+#             */
/*   Updated: 2024/01/21 15:24:43 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	return (envp[0]);
}

char	*get_path(char *cmd, char **envp)
{
	int		i;
	char	**all_paths;
	char	*temp_path;
	char	*full_path;

	i = 0;
	all_paths = ft_split(get_env("PATH", envp), ':');
	while (all_paths[i] != NULL)
	{
		temp_path = ft_strjoin(all_paths[i], "/");
		full_path = ft_strjoin(temp_path, cmd);
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
	ft_printf("zsh: command not found: %s\n", cmd);
	exit (EXIT_FAILURE);
}
