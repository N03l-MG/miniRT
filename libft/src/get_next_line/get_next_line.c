/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:27:08 by nmonzon           #+#    #+#             */
/*   Updated: 2024/10/28 11:00:58 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*clear_buffer(t_buffer *bs);
static void	set_buffer(size_t *j, int fd, t_buffer *bs);
static int	process_buffer_loop(char **line, t_buffer *bs, size_t *j, int fd);
static int	check_errors(t_buffer *bs, char **line);

// Gets the next line in fd after successive calls. Reads specified buffer size.
char	*get_next_line(int fd)
{
	static t_buffer	bufferstruct;
	size_t			j;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (clear_buffer(&bufferstruct));
	line = NULL;
	if (!bufferstruct.buffer)
	{
		set_buffer(&j, fd, &bufferstruct);
		if (!bufferstruct.buffer)
			return (clear_buffer(&bufferstruct));
	}
	else
		j = bufferstruct.i;
	while (bufferstruct.bytes_read > 0)
	{
		if (process_buffer_loop(&line, &bufferstruct, &j, fd))
			break ;
	}
	if (check_errors(&bufferstruct, &line))
		return (NULL);
	if (bufferstruct.bytes_read == 0)
		clear_buffer(&bufferstruct);
	return (line);
}

// Clears the buffer if an error happens.
static char	*clear_buffer(t_buffer *bs)
{
	free(bs->buffer);
	bs->buffer = NULL;
	return (NULL);
}

// If the buffer is empty from last call, set it up.
static void	set_buffer(size_t *j, int fd, t_buffer *bs)
{
	*j = 0;
	bs->buffer = (char *)malloc(BUFFER_SIZE);
	if (!bs->buffer)
	{
		bs->bytes_read = -1;
		return ;
	}
	bs->i = 0;
	bs->bytes_read = read(fd, bs->buffer, BUFFER_SIZE);
}

// Updates the buffer until a new line is found.
static int	process_buffer_loop(char **line, t_buffer *bs, size_t *j, int fd)
{
	while (bs->i < bs->bytes_read && bs->buffer[bs->i] != '\n')
		bs->i++;
	*line = join_range(*line, bs->buffer, *j, bs->i);
	if (!*line)
		return (1);
	if (bs->i < bs->bytes_read && bs->buffer[bs->i] == '\n')
	{
		*line = join_range(*line, bs->buffer, bs->i, bs->i + 1);
		bs->i++;
		return (1);
	}
	bs->i = 0;
	*j = 0;
	bs->bytes_read = read(fd, bs->buffer, BUFFER_SIZE);
	if (bs->bytes_read == (unsigned long)-1)
	{
		free(bs->buffer);
		bs->buffer = NULL;
		bs->i = 0;
	}
	return (0);
}

// Check if there was an error and return NULL if so.
static int	check_errors(t_buffer *bs, char **line)
{
	if (bs->bytes_read == (unsigned long)-1
		|| (*line && ft_strlen(*line) == 0) || !*line)
	{
		free(*line);
		*line = NULL;
		clear_buffer(bs);
		bs->i = 0;
		return (1);
	}
	return (0);
}
