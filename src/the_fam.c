/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_fam.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:41:31 by asfletch          #+#    #+#             */
/*   Updated: 2024/01/20 17:01:36 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_child(t_pipex pipex, char **envp)
{
	int	fd;

	pipex->infile = open(argv[1], O_RDONLY);
}

void	execute_parent(t_pipex pipex, char **envp)
{

}
