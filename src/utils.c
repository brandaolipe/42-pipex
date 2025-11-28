/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: febranda <febranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:28:42 by febranda          #+#    #+#             */
/*   Updated: 2025/11/28 19:28:10 by febranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_message(int	error_numb)
{
	perror("Error");
	exit(error_numb);
}

char	*handle_path_and_cmd(char *cmd, char **paths)
{
	char	*exec_path;
	char	*partial_path;
	char	**cmd_argv;
	int		i;

	cmd_argv = ft_split(cmd, ' ');
	if (!cmd_argv[0] || cmd_argv[0][0] == '\0')
	{
		free_split(cmd_argv);
		return (NULL);
	}
	i = 0;	
	while (paths[i])
	{
		partial_path = ft_strjoin(paths[i], "/");
		exec_path = ft_strjoin(partial_path, cmd_argv[0]);
		free(partial_path);
		if (access(exec_path, X_OK) == 0)
			break;
		i++;
		free(exec_path);
		exec_path = NULL;
	}
	free_split(cmd_argv);
	return (exec_path);
}

void	execute_cmd(char *exec_path, char *cmd, char **envp)
{
	char	**exec_argv;

	exec_argv = ft_split(cmd, ' ');
	execve(exec_path, exec_argv, envp);
	free_split(exec_argv);
	error_message(1);
	//exit(1);
}

void	free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
