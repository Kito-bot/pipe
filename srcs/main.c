/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychattou <ychattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:04:16 by ychattou          #+#    #+#             */
/*   Updated: 2024/09/25 19:25:20 by ychattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	error_msg_main(int n)
{
	if (n == 0)
	{
		perror("Error : pipe(fd) = -1");
		exit(EXIT_FAILURE);
	}
	if (n == 1)
	{
		perror("Error : pid1 = -1");
		exit(EXIT_FAILURE);
	}
	if (n == 2)
	{
		ft_putstr_fd("Wrong Number of arguments\n", 2);
		ft_putstr_fd("Please use the following format :\n", 2);
		ft_putstr_fd("./pipex <file1> <cmd1> <cmd2> <file2>", 2);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	pid_t	pid1;
	int		fd[2];

	if (argc != 5)
	{
		error_msg_main(2);
		return (0);
	}
	if (pipe(fd) == -1)
		error_msg_main(0);
	pid1 = fork();
	if (pid1 == -1)
		error_msg_main(1);
	if (pid1 == 0)
		child_process(fd, argv, envp);
	waitpid(pid1, NULL, 0);
	parent_process(fd, argv, envp);
	return (0);
}
