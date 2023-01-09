/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:50:14 by adrgonza          #+#    #+#             */
/*   Updated: 2023/01/09 16:50:21 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1)
	{
		s1 = malloc(1);
		s1[0] = '\0';
	}
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	i = -1;
	j = 0;
	while (s1[++i] != '\0')
		str[i] = s1[i];
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}

char	*ft_line_cut(char *str)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	tmp = malloc(i + 2);
	if (!tmp)
		return (NULL);
	tmp[i++] = '\0';
	i = -1;
	while (str[++i] && str[i] != '\n')
		tmp[i] = str[i];
	tmp[i] = str[i];
	tmp[++i] = '\0';
	return (tmp);
}

char	*ft_rest_str(char *str)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	tmp = malloc(ft_strlen(str) - i + 1);
	if (!tmp)
		return (NULL);
	i++;
	j = 0;
	while (str[i])
		tmp[j++] = str[i++];
	tmp[j] = '\0';
	free(str);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*str[OPEN_MAX];
	char		*line;
	char		tmp[BUFFER_SIZE + 1];
	int			nb;
	int			i;

	nb = 1;
	i = 0;
	while (nb != 0)
	{
		nb = read(fd, tmp, BUFFER_SIZE);
		if (nb == -1 && str[fd])
			free(str[fd]);
		if (nb == -1)
			return (str[fd] = NULL);
		tmp[nb] = '\0';
		str[fd] = ft_strjoin(str[fd], tmp);
		while (tmp[i] != '\n' && tmp[i] != '\0')
			i++;
		if (tmp[i] == '\n')
			break ;
	}
	line = ft_line_cut(str[fd]);
	str[fd] = ft_rest_str(str[fd]);
	return (line);
}
