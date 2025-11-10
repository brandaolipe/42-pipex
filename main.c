/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: febranda <febranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:54:41 by febranda          #+#    #+#             */
/*   Updated: 2025/11/10 19:05:04 by febranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	if (argc < 5)
	{
		printf("How use: ./pipex file1 cmd1 cmd2 file2");
		return (1);
	}
	verify_infile(argv[1]);
	verify_outfile(argv[4]);
	return (0);
}
