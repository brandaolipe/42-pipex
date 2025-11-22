/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: febranda <febranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:54:41 by febranda          #+#    #+#             */
/*   Updated: 2025/11/21 18:43:44 by febranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		pipe_fd[2];

	if (argc == 5)
	{
		if (pipe(pipe_fd) == -1)
			error_message();
		pipex(argv, envp, pipe_fd);
	}
	else
		ft_putstr_fd("How use: ./pipex file1 cmd1 cmd2 file2", 2);
	return (0);
}

int	pipex(char **argv, char **envp, int *pipe_fd)
{
	pid_t	pid1;
	pid_t	pid2;

	pid1 = fork();
	if (pid1 == -1)
		error_message();
	if (pid1 == 0)
		child_process_1(argv, envp, pipe_fd);
	pid2 = fork();
	if (pid2 == -1)
		error_message();
	if (pid2 == 0)
		child_process_2(argv, envp, pipe_fd);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}

void	child_process(char **argv, char **envp, int *pipe_fd)
{
	
}

int	get_infile_fd(const char *infile)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd < 0)
	{
		perror("It`s not possible to open the infile");
		return (0);
	}
	return (fd);
}

int	get_outfile_fd(const char *outfile)
{
	int	fd;

	fd = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("It`s not possible to open the outfile");
		return (0);
	}
	return (1);
}
