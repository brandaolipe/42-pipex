/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: febranda <febranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:54:41 by febranda          #+#    #+#             */
/*   Updated: 2025/11/12 19:05:06 by febranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int	pipefd[2];
	pid_t	cpid;
	int	fd_in;
	int	fd_out;

	if (argc < 5)
	{
		printf("How use: ./pipex file1 cmd1 cmd2 file2");
		return (1);
	}
	fd_in = get_infile_fd(argv[1]);
	fd_out = get_outfile_fd(argv[4]);
	
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	cpid = fork();
	if (cpid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	return (0);
}
