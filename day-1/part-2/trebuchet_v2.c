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
 * Function compares the indexes found by checking the occurring digits, in
 * numerical and alphabets form. Function then joins the ultimate first and last
 * occurring digits.
 * @param i_index The first and last index of the occurring digits
 * @param s_index The index of the first character from the first occurring digits,
 * and the index of the last character from the last occurring digits, both in
 * alphabets format
 * @param ltoi The converted digits, from alphabets to numerical form.
 * @param puzzle The puzzle string
 * @return Function returns the joined digit
*/
int		compare_and_join(int i_index[2], int s_index[2], int ltoi[2], char *puzzle)
{
	int	first;
	int	last;

	if (s_index[0] != -1 && s_index[0] < i_index[0])
		first = ltoi[0] * 10;
	else
		first = (puzzle[i_index[0]] - '0') * 10;
	if (s_index[1] != -1 && s_index[1] > i_index[1])
		last = ltoi[1];
	else
		last = puzzle[i_index[1]] - '0';
	return (first + last);
}

/**
 * Function checks the index of the first and last occurrence of digits in
 * alphabets form from the string.
 * @param s_index The index of the first character from the first occurring digits,
 * and the index of the last character from the last occurring digits, both in
 * alphabets format
 * @param ltoi The converted digits, from alphabets to numerical form.
 * @param puzzle The puzzle string
 * @return Function does not return
*/
void	check_letters(int s_index[2], int ltoi[2], char *puzzle)
{
	const char	*letters[9] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
	const int	len = strlen(puzzle);
	int	start_found = 0;
	int	end_found = 0;

	for (int i = 0; i < len; i++) {
		for (int j = 0; j < 9; j++) {
			if (strncmp(puzzle + i, letters[j], strlen(letters[j])) == 0) {
				s_index[0] = i;
				ltoi[0] = j + 1;
				start_found = 1;
				break ;
			}
		}
		if (start_found)
			break ;
    }
	if (start_found == 0)
		s_index[0] = -1;

    for (int i = len - 1; i >= 0; i--) {
        for (int j = 0; j < 9; j++) {
            int letter_length = strlen(letters[j]);
            if (i - letter_length + 1 >= 0 &&
					strncmp(puzzle + i - letter_length + 1, letters[j],
								letter_length) == 0) {
				s_index[1] = i;
				ltoi[1] = j + 1;
                end_found = 1;
            }
        }
		if (end_found)
			break ;
    }
	if (end_found == 0)
		s_index[1] = -1;
}

/**
 * Function checks the index of the first and last occurrence of digits in
 * numerical form from the string.
 * @param i_index The first and last index of the occurring digits
 * @param puzzle The puzzle string
 * @return Function does not return
*/
void	check_numbers(int i_index[2], char *puzzle)
{
	const int	len = strlen(puzzle);
	int			start;
	int			end;

	start = -1;
	end = len;
	while (++start < len)
	{
		if (puzzle[start] >= 48 && puzzle[start] <= 57)
			break ;
	}
	while (--end > -1)
	{
		if (puzzle[end] >= 48 && puzzle[end] <= 57)
			break ;
	}
	i_index[0] = start;
	i_index[1] = end;
}

/**
 * Function checks for two occurrences in the puzzle string:
 * 1. Occurrences of digits (and its index)
 * 2. Occurrences of digits spelt in letters (converted digits and its index)
 * @param puzzle The puzzle string
 * @return Function returns the joined value of the first/last occurrence digits
*/
int		get_calibration_value(char *puzzle)
{
	int	i_index[2];
	int	s_index[2];
	int	ltoi[2];

	check_numbers(i_index, puzzle);
	check_letters(s_index, ltoi, puzzle);

	return (compare_and_join(i_index, s_index, ltoi, puzzle));
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
	sum = 0;
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
