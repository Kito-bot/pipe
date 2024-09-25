/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychattou <ychattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:50:59 by ychattou          #+#    #+#             */
/*   Updated: 2024/09/25 19:32:47 by ychattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	error_msg_parent_process(void)
{
	perror("Error : parent_process.c");
	exit(EXIT_FAILURE);
}

void	parent_process(int fd[2], char **argv, char **envp)
{
	int	outfile_fd;

	outfile_fd = open(argv[4], O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (outfile_fd == -1)
		error_msg_parent_process();
	close(fd[1]);
	dup2(outfile_fd, STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	close(outfile_fd);
	close(fd[0]);
	command_exec(argv[3], envp);
}
