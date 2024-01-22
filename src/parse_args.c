/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:55:29 by asfletch          #+#    #+#             */
/*   Updated: 2024/01/22 19:16:32 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	parse_args(int argc, char **argv, t_pipex *pipex)
{
	int	i;

	i = 0;
	pipex->cmd_argc = argc - 3;
	pipex->command = malloc(sizeof(t_command) * pipex->cmd_argc);
	if (!pipex->command)
		exit (EXIT_FAILURE);
	while (i < pipex->cmd_argc)
	{
		pipex->command[i].args = ft_split(argv[i + 2], ' ');
		if (!pipex->command[i].args)
		{
			clean_exit (*pipex);
			exit (EXIT_FAILURE);
		}
		pipex->command[i].cmd = pipex->command[i].args[0];
		pipex->command[i].cmd_arg = pipex->command[i].args[1];
		i++;
	}
	return (0);
}
