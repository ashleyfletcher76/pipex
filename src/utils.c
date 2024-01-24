/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 09:24:27 by asfletch          #+#    #+#             */
/*   Updated: 2024/01/23 09:17:51 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	open_the_files(t_pipex *pipex, int index)
{
	if (index == 0)
	{
		pipex->infile_fd = open(pipex->infile, O_RDONLY);
		if (pipex->infile_fd == -1)
		{
			my_write_three ("pipex: ", pipex->infile,
				": No such file or directory", 2);
			clean_exit (*pipex);
			exit (EXIT_FAILURE);
		}
	}
	if (index == 1)
	{
		pipex->outfile_fd = open(pipex->outfile,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (pipex->outfile_fd == -1)
		{
			perror ("pipex: output\n");
			clean_exit (*pipex);
			exit (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

void	my_write_two(char *s, char *s1, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putstr_fd(s1, fd);
	ft_putchar_fd('\n', fd);
}

void	my_write_three(char *s, char *s1, char *s2, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putstr_fd(s1, fd);
	ft_putstr_fd(s2, fd);
	ft_putchar_fd('\n', fd);
}
