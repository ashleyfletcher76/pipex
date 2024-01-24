/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 14:19:17 by asfletch          #+#    #+#             */
/*   Updated: 2024/01/23 09:13:38 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	dup_failure(t_pipex pipex)
{
	close_fds (pipex);
	clean_exit (pipex);
	exit (EXIT_FAILURE);
}

void	close_fds(t_pipex pipex)
{
	close (pipex.fd[0]);
	close (pipex.fd[1]);
}

void	clean_exit(t_pipex pipex)
{
	int	i;

	i = 0;
	if (pipex.command != NULL)
	{
		while (i < pipex.cmd_argc)
		{
			free_arr (pipex.command[i].args);
			i++;
		}
		free(pipex.command);
	}
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i] != NULL)
		{
			free (arr[i]);
			i++;
		}
		free (arr);
	}
}
