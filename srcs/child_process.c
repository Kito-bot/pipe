/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychattou <ychattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:42:56 by ychattou          #+#    #+#             */
/*   Updated: 2024/09/25 19:19:54 by ychattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	error_msg_child_process(void)
{
	perror("Error : child_process.c");
	exit(EXIT_FAILURE);
}

void	child_process(int fd[2], char **argv, char **envp)
{
	int	infile_fd;

	infile_fd = open(argv[1], O_RDONLY, 0777);
	if (infile_fd == -1)
		error_msg_child_process();
	close(fd[0]);
	dup2(infile_fd, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	close(infile_fd);
	command_exec(argv[2], envp);
}
