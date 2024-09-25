/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychattou <ychattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:13:31 by ychattou          #+#    #+#             */
/*   Updated: 2024/09/25 16:58:41 by ychattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	int		size_little;

	size_little = ft_strlen(little);
	i = 0;
	if (!big && len == 0)
		return (NULL);
	if (size_little == 0)
		return ((char *) big);
	while (big[i] && i + size_little <= len)
	{
		if (big[i] == little[0])
		{
			j = 0;
			while (little[j] && (big[i + j] == little[j]))
				j++;
			if (!little[j])
				return ((char *)(big + i));
		}
		i++;
	}
	return (NULL);
}
