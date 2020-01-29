/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdnaya <zdnaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 17:09:10 by zdnaya            #+#    #+#             */
/*   Updated: 2020/01/25 17:30:27 by zdnaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char		*freez(char **buff)
{
	if (buff != NULL && *buff != NULL)
	{
		free(*buff);
		*buff = NULL;
	}
	return (NULL);
}

static int		ft_next(char **str, char **line, int r)
{
	char		*tmp;
	char		*endl;

	if (r == 0 && (*str == NULL || *str == '\0'))
	{
		*line = ft_strdup("");
		return (0);
	}
	if ((endl = ft_strchr(*str, '\n')))
	{
		endl[0] = 0;
		*line = ft_strdup(*str);
		tmp = *str;
		*str = endl[1] ? ft_strdup(endl + 1) : freez(str);
		if (*str)
			free(tmp);
	}
	else if (*str && r == 0)
	{
		*line = *str;
		freez(str);
		return (0);
	}
	return (1);
}

int				get_next_line(int fd, char **line)
{
	char		*buff;
	int			r;
	char		*tmp;
	static char *str[4684];

	buff = NULL;
	if (!(buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))) || fd < 0 ||
			line == NULL || fd >= 4864)
	{
		freez(&buff);
		return (-1);
	}
	while ((r = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[r] = '\0';
		tmp = str[fd];
		str[fd] = !str[fd] ? ft_strdup(buff) : ft_strjoin(str[fd], buff);
		ft_bzero(buff, BUFFER_SIZE + 1);
		if (tmp)
			free(tmp);
		if ((tmp = ft_strchr(str[fd], '\n')))
			break ;
	}
	freez(&buff);
	return (r < 0 ? -1 : ft_next(&str[fd], line, r));
}
