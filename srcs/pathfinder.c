/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychattou <ychattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:23:10 by ychattou          #+#    #+#             */
/*   Updated: 2024/09/25 18:47:11 by ychattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	error_msg_child_process(void)
{
	perror("Error : pathfinder.c");
	exit(EXIT_FAILURE);
}

static char	**planet_pathfinder(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		error_msg_child_process();
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	if (!envp[i])
		error_msg_child_process();
	return (ft_split(envp[i] + 5, ':'));
}

char	*pathfinder(char *cmd, char **envp)
{
	char	**path_split;
	char	*temp_path;
	char	*path_res;
	int		i;

	i = 0;
	path_split = planet_pathfinder(envp);
	while (path_split[i])
	{
		temp_path = ft_strjoin(path_split[i], "/");
		path_res = ft_strjoin(temp_path, cmd);
		free(temp_path);
		if (access(path_res, F_OK) == 0)
			return (path_res);
		free(path_res);
		i++;
	}
	i = 0;
	while (path_split[i])
	{
		free(path_split[i]);
		i++;
	}
	free(path_split);
	return (0);
}
