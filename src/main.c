/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:07:43 by asfletch          #+#    #+#             */
/*   Updated: 2024/01/22 21:04:19 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	leaks(void)
{
	system ("leaks pipex");
}

int	following_main(t_pipex pipex, char **envp)
{
	int		i;

	i = 0;
	while (i < pipex.cmd_argc)
	{
		pipex.pid[i] = fork();
		if (pipex.pid[i] == 0)
			execute_child_one (pipex, i, envp);
		else if (pipex.pid[i] < 0)
		{
			clean_exit (pipex);
			perror ("Fork failure");
			return (1);
		}
		i++;
	}
	clean_exit (pipex);
	close(pipex.fd[0]);
	close(pipex.fd[1]);
	wait_for_child(pipex, pipex.cmd_argc);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	if (argc != 5)
		exit (1);
	// init_struct (pipex);
	parse_args (argc, argv, &pipex);
	pipex.infile = argv[1];
	pipex.outfile = argv[argc - 1];
	if (pipe(pipex.fd) == -1)
	{
		clean_exit (pipex);
		perror ("Pipe error!\n");
		return (128);
	}
	following_main(pipex, env);
	//atexit (leaks);
	return (EXIT_SUCCESS);
}

// void	init_struct(t_pipex pipex)
// {
// 	pipex.infile_fd = - 1;
// 	pipex.outfile_fd = - 1;
// 	pipex.cmd_argc = 0;
// 	pipex.path = NULL;
// 	pipex.command->cmd = NULL;
// 	pipex.fd[0] = -1;
// 	pipex.fd[1] = -1;
// }
