#include "libft.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#define NUMBER_OF_CARDS 60
#define NUMBER_COL		3

size_t g_max_size = 0;

void	ft_del(void *data, size_t size)
{
	(void)size;
	ft_strdel((char **)&data);
}

void	ft_del2(void *data)
{
	ft_strdel((char **)&data);
}

t_list	*parse_file(int *count)
{
	int			fd;
	t_list		*list = NULL;
	t_list		*node;
	t_vector	*line;

	fd = open("./resources/list.txt", O_RDONLY);
	if (fd == FAILURE)
		return (NULL);
	line = vct_new(0);
	while (vct_readline(line, fd) > 0)
	{
		if (vct_apply(line, IS_SPACE) == TRUE)
			continue ;
		vct_apply(line, UPCASE);
		if (vct_len(line) > g_max_size)
			g_max_size = vct_len(line);
		node = ft_lstnew(vct_getstr(line), vct_len(line) + 1);
		ft_lstadd(&list, node);
		(*count)++;
	}
	g_max_size += 6;
	vct_del(&line);
	close(fd);
	return (list);
}

char	*get_elem(t_list **list, int nb)
{
	int	i = 0;
	char	*result = NULL;
	size_t	rest;

	for (t_list *tmp = *list; tmp != NULL; tmp = tmp->next)
	{
		if (i == nb)
		{
			result = ft_strnew(g_max_size);
			if (result == NULL)
				return (NULL);
			ft_memset(result, ' ', g_max_size);
			result[g_max_size - 1] = '\0';
			rest = (g_max_size - tmp->content_size) / 2
					+ (g_max_size - tmp->content_size) % 2,
			ft_memcpy(result + rest, tmp->content, tmp->content_size - 1);
			ft_lstdelnode(list, tmp->content, ft_del2);
			return (result);
		}
		i++;
	}
	return (NULL);
}

t_vector *get_result(t_list **list, int count)
{
	t_vector	*output = vct_new(0);
	int	i = 0;
	int	nb;
	char	*tmp = NULL;

	srand(time(NULL));
	while (i < NUMBER_OF_CARDS && *list != NULL)
	{
		nb = rand() % count;
		tmp = get_elem(list, nb);
		if (tmp == NULL)
			break ;
		if (i % NUMBER_COL == 0)
			vct_addstr(output, "\n\n\n\t\t");
		vct_addstr(output, tmp);
		count--;
		ft_strdel(&tmp);
		i++;
	}
	if (i != NUMBER_OF_CARDS)
	{
		vct_del(&output);
		return (NULL);
	}
	vct_add(output, '\n');
	return (output);
}

void	write_result(t_vector *vct)
{
	int	fd;

	fd = open("./cards.txt", O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd != FAILURE)
		vct_print_fd(vct, fd);
}

int	main(void)
{
	t_list 		*list = NULL;
	t_vector	*output;
	int			count = 0;

	if ((list = parse_file(&count)) == NULL || count < NUMBER_OF_CARDS)
		return (EXIT_FAILURE);
	output = get_result(&list, count);
	ft_lstdel(&list, ft_del);
	if (output == NULL)
		return (EXIT_FAILURE);
	write_result(output);
	vct_del(&output);
	return (EXIT_SUCCESS);
}
