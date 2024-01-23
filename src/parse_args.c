/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:55:29 by asfletch          #+#    #+#             */
/*   Updated: 2024/01/23 07:34:42 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	parse_args(int argc, char **argv, t_pipex *pipex)
{
	int	i;
	int	check_index;

	i = 0;
	pipex->cmd_argc = argc - 3;
	pipex->command = ft_calloc(1, sizeof(t_command) * pipex->cmd_argc);
	if (!pipex->command)
		exit (EXIT_FAILURE);
	while (i < pipex->cmd_argc)
	{
		pipex->command[i].args = ft_split(argv[i + 2], ' ');
		check_index = 0;
		check_cmd_or_empty (pipex, i, check_index);
		pipex->command[i].cmd = pipex->command[i].args[0];
		check_index = 1;
		check_cmd_or_empty (pipex, i, check_index);
		if (pipex->command[i].args[1] != NULL)
			pipex->command[i].cmd_arg = pipex->command[i].args[1];
		else
			pipex->command[i].cmd_arg = NULL;
		i++;
	}
	return (0);
}

void	check_cmd_or_empty(t_pipex *pipex, int i, int check_index)
{
	if (check_index == 0 && !pipex->command[i].args)
	{
		clean_exit (*pipex);
		exit (127);
	}
	else if (check_index == 1)
	{
		if (!pipex->command[i].cmd)
		{
			ft_putendl_fd ("zsh: command not found: ", 0);
			clean_exit (*pipex);
			exit (127);
		}
	if (is_empty_or_white(pipex->command[i].cmd))
		{
			clean_exit (*pipex);
			exit (127);
		}
	}
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

// int	parse_args(int argc, char **argv, t_pipex *pipex)
// {
// 	int	i;
// 	int	check_index;
// 	int	error_checker;

// 	i = 0;
// 	error_checker = 0;
// 	pipex->cmd_argc = argc - 3;
// 	pipex->command = ft_calloc(1, sizeof(t_command) * pipex->cmd_argc);
// 	if (!pipex->command)
// 		exit (EXIT_FAILURE);
// 	while (i < pipex->cmd_argc)
// 	{
// 		pipex->command[i].args = ft_split(argv[i + 2], ' ');
// 		check_index = 0;
// 		if (check_cmd_or_empty(pipex, i, check_index) < 0)
// 			error_checker = 1;
// 		if (pipex->command[i].args && pipex->command[i].args[0])
// 		{
// 			pipex->command[i].cmd = pipex->command[i].args[0];
// 				check_index = 1;
// 			if (check_cmd_or_empty(pipex, i, check_index) < 0)
// 				error_checker = 1;
// 		}
// 		else
// 			error_checker = 1;
// 		i++;
// 	}
// 	if (error_checker)
// 		error_occured (pipex);
// 	return (0);
// }

// void	error_occured(t_pipex *pipex)
// {
// 	clean_exit (*pipex);
// 	exit (127);
// }

// int	check_cmd_or_empty(t_pipex *pipex, int i, int check_index)
// {
// 	if (check_index == 0 && !pipex->command[i].args)
// 		return (-1);
// 	else if (check_index == 1)
// 	{
// 		if (!pipex->command[i].cmd)
// 		{
// 			my_two_write ("zsh: command not found: ", pipex->command[i].cmd, 0);
// 			return (-1);
// 		}
// 	if (is_empty_or_white(pipex->command[i].cmd))
// 		return (-1);
// 	}
// 	return (0);
// }
