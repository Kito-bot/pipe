/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychattou <ychattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:05:28 by ychattou          #+#    #+#             */
/*   Updated: 2024/09/25 19:26:22 by ychattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	error_msg_command_exec(void)
{
	perror("Error : command_exec.c");
	exit(EXIT_FAILURE);
}

void	command_exec(char *argv, char **envp)
{
	char	*path;
	char	**command;
	int		i;

	command = ft_split(argv, ' ');
	path = pathfinder(command[0], envp);
	i = 0;
	if (!path)
	{
		while (command[i])
		{
			free(command[i]);
			i++;
		}
		free(command);
		error_msg_command_exec();
	}
	if (execve(path, command, envp) == -1)
		error_msg_command_exec();
}
