/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:55:29 by asfletch          #+#    #+#             */
/*   Updated: 2024/01/20 17:01:26 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	parse_args(int argc, char **argv ,t_pipex *pipex)
{
	int	i;

	i = 0;
	pipex->cmd_argc = argc - 3;
	pipex->command = malloc(sizeof(t_command) * pipex->cmd_argc);
	if (!pipex->command)
		return (-1);
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile == - 1)
		return (-1);
	pipex->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile == - 1)
		return (-1);
	while (i < pipex->cmd_argc)
	{
		pipex->command[i].args = ft_split(argv[i + 2], ' ');
		pipex->command[i].cmd = pipex->command[i].args[0];
		pipex->command[i].cmd_arg = pipex->command[i].args[1];
		i++;
	}
	return (0);
}
