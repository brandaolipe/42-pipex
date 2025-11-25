/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: febranda <febranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:22:33 by febranda          #+#    #+#             */
/*   Updated: 2025/11/25 19:05:48 by febranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include <stdio.h>

//int		get_infile_fd(const char *infile);
//int		get_outfile_fd(const char *outfile);
int		pipex(char **argv, char **envp, int *pipe_fd);
char	**get_paths(char **envp);
void	child_process_1(char *cmd1, char **envp, int *pipe_fd, char *infile);
void	child_process_2(char *cmd2, char **envp, int *pipe_fd, char *outfile);
void	error_message(void);
char	*handle_path_and_cmd(char *cmd, char **paths);
void	execute_cmd(char *exec_path, char *cmd, char **envp);

#endif
