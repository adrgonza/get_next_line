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

static char	*concat_rem(char *rem_txt, const char *const buff, int i, int j)
{
	char	*new_rem;

	if (!rem_txt)
	{
		rem_txt = malloc(1 * sizeof(char));
		if (!rem_txt)
			return (NULL);
		*rem_txt = 0;
	}
	while (rem_txt && rem_txt[i])
		i++;
	while (buff && buff[j])
		j++;
	new_rem = malloc((i + j + 1) * sizeof(char));
	if (!new_rem)
		return (free(rem_txt), rem_txt = NULL);
	i = -1;
	while (rem_txt[++i])
		new_rem[i] = rem_txt[i];
	j = 0;
	while (buff && buff[j])
		new_rem[i++] = buff[j++];
	return (new_rem[i] = 0, free(rem_txt), new_rem);
}

static char	*var_manage(char *line, char **rem_txt, int i, int j)
{
	char	*new_rem;

	while ((*rem_txt)[i] && (*rem_txt)[i] != '\n')
		i++;
	if (!(*rem_txt)[i])
		i--;
	line = malloc((i + 2) * sizeof(char));
	if (!line)
		return (free(*rem_txt), *rem_txt = NULL);
	line[i + 1] = 0;
	i = -1;
	while ((*rem_txt)[++i] && (*rem_txt)[i] != '\n')
		line[i] = (*rem_txt)[i];
	line[i] = (*rem_txt)[i];
	if (!(*rem_txt)[i])
		return (free(*rem_txt), *rem_txt = NULL, line);
	while ((*rem_txt)[j])
		j++;
	new_rem = malloc((j - i + 2) * sizeof(char));
	if (!new_rem)
		return (free(line), free(*rem_txt), *rem_txt = NULL);
	j = 0;
	while ((*rem_txt)[++i])
		new_rem[j++] = (*rem_txt)[i];
	return (new_rem[j] = 0, free(*rem_txt), *rem_txt = new_rem, line);
}

char	*get_next_line(int fd)
{
	static char	*rem_txt;
	char		*line;
	char		buffer[BUFFER_SIZE + 1];
	int			i;

	while (1)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == -1)
			return (free(rem_txt), rem_txt = NULL);
		buffer[i] = 0;
		rem_txt = concat_rem(rem_txt, buffer, 0, 0);
		if (!rem_txt)
			return (free(rem_txt), rem_txt = NULL);
		if (i == 0)
			break ;
		i = -1;
		while (buffer[++i] && buffer[i] != '\n')
			if (buffer[i + 1] == '\n')
				return (line = NULL, var_manage(line, &rem_txt, 0, 0));
	}
	if (!*rem_txt)
		return (free(rem_txt), rem_txt = NULL);
	return (line = NULL, var_manage(line, &rem_txt, 0, 0));
}
