/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismus <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 17:10:12 by ismus             #+#    #+#             */
/*   Updated: 2018/04/26 17:10:13 by ismus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	data_a(t_lm *data, int i)
{
	char	*line;

	get_next_line(0, &line);
	while (line && ft_strncmp("#", line, 1) == 0 && ft_strcmp(line, "##start\0")
		!= 0 && ft_strcmp(line, "##end\0") != 0)
	{
		ft_printf("%s\n", line);
		free(line);
		get_next_line(0, &line);
	}
	if (line)
		ft_printf("%s\n", line);
	while (line && line[i] <= '9' && line[i] >= '0')
		i++;
	if (!line || line[0] == '\0')
	{
		ft_printf("\x1b[1;31mInsufficient data!\n");
		return (0);
	}
	if (line[i] != '\0' || i > 10 || (i == 10 && ft_strcmp(line, "2147483647") > 0))
	{
		free(line);
		ft_printf("\x1b[1;31mNot the correct number of ants!\n");
		return (0);
	}

	data->ants = ft_atoi(line);
	free(line);
	if (data->ants == 0)
	{
		ft_printf("\x1b[1;31mNot enough ants!\n");
		return (0);
	}
	return (1);
}

static int	get_st_end(char *next, t_lm *data)
{
	char *line;

	line = ft_strdup(next);
	if ((ft_strcmp(line, "##start\0") == 0 && data->start) ||
		(ft_strcmp(line, "##end\0") == 0 && data->end))
	{
		ft_printf("\x1b[1;31mMore that one %s!\n", line + 2);
		free(line);
		return (0);
	}
	while (ft_strncmp(next, "#", 1) == 0)
	{
		free(next);
		if (get_next_line(0, &next) && next)
			ft_printf("%s\n", next);
		if (!next)
		{
			free(line);
			ft_printf("\x1b[1;31mError input!\n");
			return (0);
		}
		if (ft_strcmp(next, "##start\0") == 0 || ft_strcmp(next, "##end\0") == 0)
		{
			free(line);
			free(next);
			ft_printf("\x1b[1;31mError input!\n");
			return (0);
		}
	}
	if (ft_strcmp(line, "##start\0") == 0)
		data->start = next;
	else
		data->end = next;
	if ((ft_strcmp(line, "##start\0") == 0 && data->start == 0) ||
		(ft_strcmp(line, "##end\0") == 0 && data->end == 0))
		return (pr_free("The data was incorrectly entered!", line, 0));
	free(line);
	return (1);
}

static int	add_rooms(t_lm *data, int i, char *line)
{
	int k;

	while (line[i] <= '9' && line[i] >= '0')
		i++;
	k = i + 1;
	while (line[k] <= '9' && line[k] >= '0')
		k++;
	if (line[i] != ' ' || line[k])
		return (pr_free("The data was incorrectly entered!", line, 0));
	if (data->rooms == 0)
		data->rooms = joinfree(line, "\0", 1);
	else
	{
		data->rooms = joinfree(data->rooms, "\n\0", 1);
		data->rooms = joinfree(data->rooms, line, 3);
	}
	data->n_rm += 1;
	return (1);
}

static int	add_coments(char *line, int i, t_lm *data)
{
	while (line[i] != '\0' && line[i] != '-' && line[i] != ' ')
		i++;
	if (line[i] == '-')
	{
		while (line[++i] && line[i] != ' ' && line[i] != '-')
			i = i + 0;
		if (line[i])
			return (pr_free("The data was incorrectly entered!", line, 0));
		else if (data->coments == 0)
			data->coments = line;
		else
			data->coments = join3free(data->coments, "\n\0", line, 5);
		return (1);
	}
	else if (line[i] == ' ')
		return (add_rooms(data, ++i, line));
	ft_printf("\x1b[1;31mThe data was incorrectly entered!\n");
	free(line);
	return (0);
}

int			get_data(t_lm *data, char *line)
{
	int i;

	if (data_a(data, 0) == 0)
		return (0);
	while (get_next_line(0, &line))
	{
		if (line)
			ft_printf("%s\n", line);
		while (line && ft_strncmp(line, "#", 1) == 0 && ft_strcmp(line, "##start\0")
			!= 0 && ft_strcmp(line, "##end\0") != 0)
		{
			free(line);
			i = get_next_line(0, &line);
			if (i > 0 && line)
				ft_printf("%s\n", line);
			if (i == 0)
			{
				ft_printf("-----------------\n");
				return (1);
			}
		}
		if (!line)
			return (0);
		if (ft_strncmp(line, "##", 2) == 0)
		{
			if (get_st_end(line, data) == 0)
				return (0);
		}
		else if (add_coments(line, 0, data) == 0)
			return (0);
	}
	if (data->start == 0 || data->end == 0 || data->coments == 0)
	{
		ft_printf("\x1b[1;31mData is not enough\n");
		return (0);
	}
	ft_printf("-----------------\n");
	return (1);
}
