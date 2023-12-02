#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

void	error(char *msg)
{
	perror(msg);
	exit(1);
}

/**
 * Function checks for the first and last occurrence of digits in numerical
 * form from the puzzle string.
 * @param puzzle The puzzle string
 * @return Function returns the joined value of the first and last digits
*/
int		get_calibration_value(char *puzzle)
{
	int	start;
	int	end;
	int	len;
	int	value;

	len = strlen(puzzle);
	start = -1;
	end = len;
	while (++start < len)
	{
		if (puzzle[start] >= 48 && puzzle[start] <= 57)
			break ;
	}
	while (--end >= 0)
	{
		if (puzzle[end] >= 48 && puzzle[end] <= 57)
			break ;
	}
	value = (puzzle[start] - '0') * 10 + (puzzle[end] - '0');
	return (value);
}

/**
 * Function returns a line from a file.
 * @param fd The file descriptor of the opened puzzle file
 * @return A string derived from a line from the puzzle file
*/
char	*get_line(int fd)
{
	int 	index;
	int		bytes;
	char	character;
	char	*buffer;

	index = 0;
	bytes = read(fd, &character, 1);
	buffer = (char *)malloc(sizeof(char) * (1000));
	while (bytes > 0)
	{
		buffer[index++] = character;
		if (character == '\n')
			break ;
		bytes = read(fd, &character, 1);
	}
	if ((bytes <= 0) && (index == 0))
		return (free(buffer), NULL);
	buffer[index] = '\0';
	return (buffer);
}

int		main(void)
{
	int		fd;
	size_t	sum;
    char	*puzzle;

	fd = open("puzzle", O_RDONLY);
	if (fd < 0)
		error("puzzle not found");
	while (1)
	{
		puzzle = get_line(fd);
		if (puzzle != NULL)
		{
			sum += get_calibration_value(puzzle);
			free(puzzle);
		}
		else
			break;
	}
	printf("sum of calibration values: %lu\n", sum);
	exit(0);
}
