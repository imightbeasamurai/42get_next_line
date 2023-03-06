#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 10
#endif

int nlchr(char *str)
{
    int i;

    i = 0;
	if (!str)
		return (-1);
    while (str[i])
        if (str[i++] == '\n')
            return (i - 1);
    return (-1);
}

char    *get_my_rest(char *str, int nl)
{
	char	*rest;
    int		i;
    int		tmp;

	i = 0;
	tmp = nl;
	rest = NULL;
	while (str[++tmp])
		i++;
	if (i)
	{
		i = 0;
		rest = malloc(i + 1);
		while (str[++nl])
			rest[i++] = str[nl];
		rest[i] = 0;
	}
	return (rest);
}

char    *get_my_line(char *str, int nl)
{
    char    *line;
    int     i;

    i = -1;
    line = malloc(nl + 2);
    while (str[++i] != '\n')
        line[i] = str[i];
    if (str[i])
        line[i] = str[i];
    line[++i] = 0;
    return (line);
}

int	ft_strlen(char *str)
{
	int	i;
	
	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*join_my_lines(char	*buff, char *tmp)
{
	char	*join;
	int	buff_len;
	int	tmp_len;
	int	i = -1;
	int	j = 0;

	buff_len = ft_strlen(buff);
	tmp_len = ft_strlen(tmp);
	join = malloc(buff_len + tmp_len + 1);
	while (++i < buff_len)
		join[i] = buff[i];
	while (j < tmp_len)
		join[i++] = tmp[j++];
	join[i] = 0;
	if (buff_len)
		free(buff);
	return (join);
}

char	*get_next_line(int fd)
{
 	char    *line;
    char *buff;
	char	*tmp;
    static char *rest;
    int nl;
	
	buff = NULL;
	if (rest)
	{
		printf("/////[%s]\\\\\\\\\\\\", rest);
		buff = strdup(rest);
		free(rest);
		rest = NULL;
	}
    tmp = malloc(BUFFER_SIZE);
	nl = 1;
	while (nlchr(buff) == -1 && nl)
	{	
		nl = read(fd, tmp, BUFFER_SIZE);
		if (nl)
			buff = join_my_lines(buff, tmp);
	}
	free(tmp);
	if (!nl)
		return (buff);
    nl = nlchr(buff);
    if (nl != -1)
    {
        line = get_my_line(buff, nl);
		free(rest);
		rest = NULL;
        rest = get_my_rest(buff, nl);
    }
	return (line);
}

int main()
{
    int fd;
	char	*line;
    fd = open("text", O_RDONLY);
	line = get_next_line(fd);
	// line = join_my_lines("akki", "akka");
    printf("{%s}\n", line);
	line = get_next_line(fd);
    printf("{%s}\n", line);
	// line = get_next_line(fd);
    // printf("{%s}\n", line);
	// line = get_next_line(fd);
    // printf("{%s}\n", line);
	// line = get_next_line(fd);
    // printf("{%s}\n", line);
	// line = get_next_line(fd);
    // printf("{%s}\n", line);
	// line = get_next_line(fd);
    // printf("{%s}\n", line);
	// line = get_next_line(fd);
    // printf("{%s}\n", line);
}