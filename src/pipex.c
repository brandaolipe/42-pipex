/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: febranda <febranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:54:41 by febranda          #+#    #+#             */
/*   Updated: 2025/11/28 19:29:08 by febranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		pipe_fd[2];
	int		status;
	
	status = 0;
	if (argc == 5)
	{
		if (pipe(pipe_fd) == -1)
			error_message(1);
		status = pipex(argv, envp, pipe_fd);
	}
	else
		ft_putstr_fd("How use: ./pipex file1 cmd1 cmd2 file2", 2);
	return (status);
}

int	pipex(char **argv, char **envp, int *pipe_fd)
{
	pid_t	pid1;
	pid_t	pid2;
	char	*infile;
	char	*outfile;
	int		status;

	infile = argv[1];
	outfile = argv[4];
	pid1 = fork();
	if (pid1 == -1)
		error_message(1);
	if (pid1 == 0)
		child_process_1(argv[2], envp, pipe_fd, infile);
	pid2 = fork();
	if (pid2 == -1)
		error_message(1);
	if (pid2 == 0)
		child_process_2(argv[3], envp, pipe_fd, outfile);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}

char	**get_paths(char **envp)
{
	char	**paths;
	char	*path;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!(ft_strncmp(envp[i], "PATH=", 5)))
			path = envp[i];
		i++;
	}
	paths = ft_split(path + 5, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

void	child_process_1(char *cmd1, char **envp, int *pipe_fd, char *infile)
{
	char	**paths;
	char	*exec_path;
	int		fd;

	exec_path = NULL;
	close(pipe_fd[0]);
	fd = open(infile, O_RDONLY);
	if (fd < 0)
	{
		close(pipe_fd[1]);
		error_message(1);
	}
	paths = get_paths(envp);
	if (!paths)
		error_message(1);
	exec_path = handle_path_and_cmd(cmd1, paths);
	if (!exec_path)
	{
		free_split(paths);
		error_message(127);
	}
	dup2(fd, STDIN_FILENO);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	close(fd);
	execute_cmd(exec_path, cmd1, envp);
	free_split(paths);
	free(exec_path);
	error_message(1);
}

void	child_process_2(char *cmd2, char **envp, int *pipe_fd, char *outfile)
{
	char	**paths;
	char	*exec_path;
	int		fd;

	exec_path = NULL;
	close(pipe_fd[1]);
	fd = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		close(pipe_fd[0]);
		error_message(1);
	}
	paths = get_paths(envp);
	if (!paths)
		error_message(1);
	exec_path = handle_path_and_cmd(cmd2, paths);
	if (!exec_path)
	{	
		free_split(paths);
		error_message(127);
	}
	dup2(pipe_fd[0], STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(pipe_fd[0]);
	close(fd);
	execute_cmd(exec_path, cmd2, envp);
	free_split(paths);
	free(exec_path);
	error_message(1);
}
