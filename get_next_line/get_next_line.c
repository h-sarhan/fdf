/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 12:43:45 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/16 17:14:53 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Reads from a file and returns the first line
// Repeated calls to the function return the next line
// Uses a static buffer to store a line
// Initializes the buffer if it is initially empty
char	*get_next_line(int fd)
{
	static char	*line_buffer;
	char		*line;
	int			bytes_read;

	if (fd < 0)
		return (NULL);
	if (line_buffer == NULL)
	{
		line_buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (line_buffer == NULL)
			return (NULL);
		bytes_read = read(fd, line_buffer, BUFFER_SIZE);
		if (bytes_read == 0 || bytes_read == -1)
		{
			free(line_buffer);
			line_buffer = NULL;
			return (NULL);
		}
		line_buffer[bytes_read] = '\0';
	}
	line = extract_line(fd, &line_buffer);
	return (line);
}

// Reads from the line buffer to find a line, extracts it from the line buffer,
// and returns it. This function also removes the line from the line buffer
char	*extract_line(int fd, char **line_buffer)
{
	int		i;
	char	*line;
	int		line_length;

	i = go_to_next_line(fd, line_buffer);
	if (i == -1)
		return (NULL);
	if ((*line_buffer)[0] == '\0')
	{
		free(*line_buffer);
		*line_buffer = NULL;
		return (NULL);
	}
	line_length = i + 1;
	line = create_line(line_buffer, line_length);
	if (line == NULL)
		return (NULL);
	i = 0;
	while ((*line_buffer)[i + line_length] != '\0')
	{
		(*line_buffer)[i] = (*line_buffer)[i + line_length];
		i++;
	}
	(*line_buffer)[i] = '\0';
	return (line);
}

// Iterates through the line buffer until it finds a new line.
// If we reach the end of the line buffer before finding a new line,
// we keep reading BUFFER_SIZE characters until we find a new line 
// or we reach the end of the file
int	go_to_next_line(int fd, char **line_buffer)
{
	int	i;
	int	max_buffer_size;
	int	bytes_read;

	i = 0;
	max_buffer_size = max(BUFFER_SIZE, ft_strlen(*line_buffer));
	while ((*line_buffer)[i] != '\n')
	{
		if ((*line_buffer)[i] == '\0')
		{
			bytes_read = read_into_buffer(line_buffer, fd, i, &max_buffer_size);
			if (bytes_read == -1)
				return (-1);
			if (bytes_read < BUFFER_SIZE)
			{
				while ((*line_buffer)[i] != '\n' && (*line_buffer)[i] != '\0')
					i++;
				break ;
			}
		}
		else
			i++;
	}
	return (i);
}

// Reads BUFFER_SIZE characters into the line buffer
// If the number of characters to be read is greater than what can be held in
// the buffer, the buffer will be resized to fit the characters.
int	read_into_buffer(char **line_buffer, int fd, int chars_read, int *max_size)
{
	int	bytes_read;

	if (chars_read + max(BUFFER_SIZE, 10) >= *max_size)
	{
		*max_size += max(BUFFER_SIZE, 10);
		*line_buffer = resize(line_buffer, chars_read, *max_size + 1);
		if (*line_buffer == NULL)
			return (-1);
	}
	bytes_read = read(fd, &(*line_buffer)[chars_read], BUFFER_SIZE);
	(*line_buffer)[chars_read + bytes_read] = '\0';
	return (bytes_read);
}

// This creates a new null terminated line from the characters in the 
// line buffer. Similar to substring.
char	*create_line(char **line_buffer, int line_length)
{
	char	*line;
	int		i;

	line = malloc(sizeof(char) * (line_length + 1));
	if (line == NULL)
	{
		free(*line_buffer);
		return (NULL);
	}
	i = 0;
	while (i < line_length)
	{
		line[i] = (*line_buffer)[i];
		i++;
	}
	line[line_length] = '\0';
	return (line);
}

// #include <fcntl.h>
// #include <stdio.h>
// int	main()
// {
// 	int i = 0;
// 	int fd = open("text.txt", O_RDONLY);
// 	while (i < 10)
// 	{
// 		printf("%s", get_next_line(fd));
// 		i++;
// 	}
// }