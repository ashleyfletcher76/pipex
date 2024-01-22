/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 14:19:17 by asfletch          #+#    #+#             */
/*   Updated: 2024/01/22 19:14:56 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

// void	arg_failues(t_pipex pipex, int cmd_index)
// {

// }

void	close_fds(t_pipex pipex)
{
	close (pipex.fd[0]);
	close (pipex.fd[1]);
}

void	clean_exit(t_pipex pipex)
{
	int	i;

	i = 0;
	while (i < pipex.cmd_argc)
	{
		free_arr (pipex.command[i].args);
		i++;
	}
	free(pipex.command);
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
