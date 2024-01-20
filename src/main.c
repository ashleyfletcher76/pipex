/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:07:43 by asfletch          #+#    #+#             */
/*   Updated: 2024/01/20 17:05:19 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	following_main(t_pipex pipex, char **envp)
{
	int		i;
	int		status;
	char	*path;

	i = 0;
	while (i < pipex.cmd_argc)
	{
		path = get_path(*pipex.command[i].args, envp);
		if (path)
		{
			pipex.pid = fork();
			if (pipex.pid == 0)
				execute_child(pipex, envp);
			else if (pipex.pid < 0)
				execute_parent(pipex, envp);
			waitpid(pipex.pid, &status, 0);
			free (path);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	if (!argc >= 5)
		exit (1);
	parse_args(argc, argv, &pipex);
	pipex.infile = open(argv[1], O_RDONLY);
	if (pipex.infile == - 1)
		return (-1);
	if (pipe(pipex.fd) == -1)
		return (-1);
	following_main(pipex, env);
	return (0);
}

// int	main(int argc, char **argv, char **env)
// {
// 	int i;
// 	int	file1;

// 	i = 0;
// 	(void)argv;
// 	file1 = 25;
// 	argc = 2;
// 	while (!(strncmp(env[i], "PATH=", 5) == 0))
// 		i++;
// 	int fd;
// 	fd = open("text.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 	dup2(fd, STDIN_FILENO);
// 	printf("env ==  %s\n", env[i]);



// 	printf("asndlsg\n");
// 	execve("/path/to/program", argv, env);

// 	return (0);
// }
