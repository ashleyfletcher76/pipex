/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:08:52 by asfletch          #+#    #+#             */
/*   Updated: 2024/01/22 14:17:04 by asfletch         ###   ########.fr       */
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
	int			infile_fd;
	char		*infile;
	char		*outfile;
	int			outfile_fd;
	int			cmd_argc;
	char		*path;
	int			fd[2];
	pid_t		pid[2];
	t_command	*command;
}	t_pipex;

int		main(int argc, char **argv, char **env);
int		parse_args(int argc, char **argv, t_pipex *pipex);
int		open_the_files(t_pipex *pipex, int index);
char	*get_path(t_pipex pipex, int cmd_index, char **envp);
char	*get_env(const char *name, char **envp);

void	execute_child_one(t_pipex pipex, int i, char **envp);
void	execute_child_two(t_pipex pipex, int i, char **envp);
void	execute_command(t_pipex pipex, int i, char **envp);

void	my_two_write(char *s, char *s1, int fd);
void	my_three_write(char *s, char *s1, char *s2, int fd);

void	wait_for_child(t_pipex pipex, int num_children);

void	arg_failues(t_pipex pipex, int cmd_index);
void	free_arr(char **arr);
void	close_fds(t_pipex pipex);
void	clean_exit(t_pipex pipex);

#endif
