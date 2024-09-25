/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychattou <ychattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:31:11 by ychattou          #+#    #+#             */
/*   Updated: 2024/09/25 14:44:58 by ychattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static int	words(char const *str, char c)
{
	int	i;
	int	j;
	int	res;

	res = 0;
	i = 0;
	while (str[i])
	{
		j = 0;
		if (!(str[i] == c))
		{
			while (str[i + j] && !(str[i + j] == c))
				j++;
			i += j;
			res++;
		}
		else
			i++;
	}
	return (res);
}

// info [current index in str, current line]
static int	write_line(char const *str, char c, char **res, int info[2])
{
	int	j;
	int	count;

	count = 0;
	while (str[info[0]] == c)
		info[0]++;
	while (str[count + info[0]] && !(str[count + info[0]] == c))
		count++;
	res[info[1]] = malloc((count + 1) * sizeof(char));
	if (!res[info[1]])
		return (0);
	j = count;
	res[info[1]][count] = '\0';
	count--;
	while (count > -1)
	{
		res[info[1]][count] = str[count + info[0]];
		count--;
	}
	info[0] += j;
	return (j);
}

static void	*ft_free(char **s, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		info[2];
	char	**res;
	int		j;

	if (words(s, c) == 0)
	{
		res = malloc(1 * sizeof(char *));
		res[0] = NULL;
		return (res);
	}
	res = malloc((words(s, c) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	info[0] = 0;
	info[1] = 0;
	while (info[1] < words(s, c))
	{
		j = write_line(s, c, res, info);
		if (j == 0)
			return (ft_free(res, info[1]));
		info[1]++;
	}
	res[info[1]] = NULL;
	return (res);
}
