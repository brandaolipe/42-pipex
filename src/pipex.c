/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: febranda <febranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:54:41 by febranda          #+#    #+#             */
/*   Updated: 2025/11/19 19:01:37 by febranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int	pipefd[2];
	pid_t	cpid;
	int	fd_in;
	int	fd_out;
	char *str;

	str = envp[0];
	if (argc == 5)
	{
		fd_in = get_infile_fd(argv[1]);
		fd_out = get_outfile_fd(argv[4]);
	
		if (pipe(pipefd) == -1)
			error_message();
		cpid = fork();
		if (cpid == -1)
			error_message();
	}
	else
	{
		ft_putstr_fd("How use: ./pipex file1 cmd1 cmd2 file2", 2);
		return (1);
	}
	return (0);
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