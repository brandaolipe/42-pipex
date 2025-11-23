/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: febranda <febranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:28:42 by febranda          #+#    #+#             */
/*   Updated: 2025/11/23 18:49:47 by febranda         ###   ########.fr       */
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
	int		i;

	i = 0;
	while (paths[i])
	{
		partial_path = ft_strjoin(paths[i], "/");
		exec_path = ft_strjoin(partial_path, cmd);
		free(partial_path);
		if (access(exec_path, X_OK) == 0)
			return (exec_path);
		free(exec_path);
	}
	return (NULL);
}
