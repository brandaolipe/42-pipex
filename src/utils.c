/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: febranda <febranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:28:42 by febranda          #+#    #+#             */
/*   Updated: 2025/11/26 20:20:09 by febranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_message(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

char	*handle_path_and_cmd(char *cmd, char **paths)
{
	char	*exec_path;
	char	*partial_path;
	char	**cmd_argv;
	int		i;

	cmd_argv = ft_split(cmd, ' ');
	i = 0;
	while (paths[i])
	{
		partial_path = ft_strjoin(paths[i], "/");
		exec_path = ft_strjoin(partial_path, cmd_argv[0]);
		free(partial_path);
		if (access(exec_path, X_OK) == 0)
			return (exec_path);
		i++;
		free(exec_path);
	}
	return (NULL);
}

void	execute_cmd(char *exec_path, char *cmd, char **envp)
{
	char	**exec_argv;

	exec_argv = ft_split(cmd, ' ');
	execve(exec_path, exec_argv, envp);
	free(exec_argv);
	exit(1);
}
