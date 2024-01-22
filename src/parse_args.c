/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:55:29 by asfletch          #+#    #+#             */
/*   Updated: 2024/01/22 20:59:12 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	parse_args(int argc, char **argv, t_pipex *pipex)
{
	int	i;

	i = 0;
	pipex->cmd_argc = argc - 3;
	pipex->command = ft_calloc(1, sizeof(t_command) * pipex->cmd_argc);
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
		if (pipex->command[i].cmd == NULL)
		{
			ft_printf("zsh: command not found: \n");
			clean_exit (*pipex);
			exit (EXIT_FAILURE);
		}
		if (is_empty_or_white(pipex->command[i].cmd))
		{
			clean_exit (*pipex);
			exit (EXIT_FAILURE);
		}
		if (pipex->command[i].args[1] != NULL)
			pipex->command[i].cmd_arg = pipex->command[i].args[1];
		else
			pipex->command[i].cmd_arg = NULL;
		i++;
	}
	return (0);
}

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' ||
		c == '\f' || c == '\r');
}

int	is_empty_or_white(const char *str)
{
	while (*str)
	{
		if (!is_whitespace(*str))
			return (0);
		str++;
	}
	return (1);
}
