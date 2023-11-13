/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 01:50:39 by adrgonza          #+#    #+#             */
/*   Updated: 2023/10/18 14:57:57 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char *s1, char *s2, int i, int j)
{
	char	*str;

	if (!s1)
	{
		s1 = malloc(1);
		s1[0] = 0;
	}
	while (s1 && s1[i])
		i++;
	while (s2[j])
		j++;
	str = malloc(i + j + 1);
	i = -1;
	j = 0;
	while (s1 && s1[++i])
		str[i] = s1[i];
	while (s2[j])
		str[i++] = s2[j++];
	return (str[i] = '\0', free(s1), str);
}

char	*line_tools(char *line, char **str, int i, int j)
{
	char	*tmp;

	while ((*str)[i] && (*str)[i] != '\n')
		i++;
	line = malloc(i + 2);
	line[i + 1] = '\0';
	i = -1;
	while ((*str)[++i] && (*str)[i] != '\n')
		line[i] = (*str)[i];
	line[i] = (*str)[i];
	if (!(*str)[i])
		return (free(*str), *str = NULL, line);
	while ((*str)[j])
		j++;
	tmp = malloc(j - i + 2);
	j = 0;
	while ((*str)[++i])
		tmp[j++] = (*str)[i];
	return (tmp[j] = '\0', free(*str), *str = tmp, line);
}

char	*get_next_line(int fd)
{
	static char	*str = NULL;
	char		*line;
	char		tmp[BUFFER_SIZE + 1];
	int			i;

	i = 1;
	while (i != 0)
	{
		i = read(fd, tmp, BUFFER_SIZE);
		if (i == -1)
			return (free(str), str = NULL);
		tmp[i] = '\0';
		str = ft_strjoin(str, tmp, 0, 0);
		i = 0;
		while (tmp[i] != '\n' && tmp[i] != '\0')
			i++;
		if (tmp[i] == '\n')
			break ;
	}
	if (!str[0])
		return (free(str), str = NULL);
	return (line = NULL, line_tools(line, &str, 0, 0));
}
