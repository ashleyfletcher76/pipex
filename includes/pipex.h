/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:08:52 by asfletch          #+#    #+#             */
/*   Updated: 2024/01/21 14:59:26 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "../libft/includes/libft.h"

typedef struct s_command
{
	char	*cmd;
	char	*cmd_arg;
	char	**args;
}	t_command;

typedef struct s_pipex
{
	int			infile;
	char		*outfile;
	int			outfile_fd;
	int			cmd_argc;
	int			fd[2];
	pid_t		pid[2];
	t_command	*command;
}	t_pipex;

int		main(int argc, char **argv, char **env);
int		parse_args(int argc, char **argv, t_pipex *pipex);
char	*get_path(char *cmd, char **envp);
char	*get_env(const char *name, char **envp);
void	execute_child(t_pipex pipex, int i, char **envp);
void	wait_for_child(t_pipex pipex, int num_children);
void	execute_command(char *cmd, char **args, char **envp);
void	free_arr(char **arr);

#endif
