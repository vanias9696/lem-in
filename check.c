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

int			data_a(t_lm *data, int i, char *line)
{
	while (get_next_line(0, &line) > 0 && line && ft_strncmp("#", line, 1) == 0
		&& ft_strcmp(line, "##start\0")
		!= 0 && ft_strcmp(line, "##end\0") != 0)
	{
		ft_printf("%s\n", line);
		free(line);
	}
	if (line)
		ft_printf("%s\n", line);
	while (line && line[i] <= '9' && line[i] >= '0')
		i++;
	if (!line || line[0] == '\0')
		return (pr_free("Insufficient data!", line, 0, 0));
	if (line[i] != '\0' || i > 10 || (i == 10 &&
		ft_strcmp(line, "2147483647") > 0))
		return (pr_free("Incorrect amount of ants!", line, 0, 0));
	data->ants = ft_atoi(line);
	free(line);
	if (data->ants == 0)
		return (pr_free("Ants are not enough!", 0, 0, 0));
	return (1);
}

static int	get_st_end(char *next, t_lm *data)
{
	char *line;

	line = ft_strdup(next);
	if ((ft_strcmp(line, "##start\0") == 0 && data->start) ||
		(ft_strcmp(line, "##end\0") == 0 && data->end))
		return (pr_free("More than one 'start' or 'end'!", line, 0, 0));
	while (ft_strncmp(next, "#", 1) == 0)
	{
		free(next);
		if (get_next_line(0, &next) && next)
			ft_printf("%s\n", next);
		if (!next)
			return (pr_free("Error input!", line, 0, 0));
		if (ft_strcmp(next, "##start\0") == 0 ||
			ft_strcmp(next, "##end\0") == 0)
			return (pr_free("'Start' or 'end' was wrong entered!", line, next, 0));
	}
	!ft_strcmp(line, "##start\0") ? data->start = next :
		(data->end = next);
	if ((ft_strcmp(line, "##start\0") == 0 && data->start == 0) ||
		(ft_strcmp(line, "##end\0") == 0 && data->end == 0))
		return (pr_free("The data was incorrectly entered!", line, 0, 0));
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
	{
		free(line);
		ft_printf("\x1b[1;31mData about room was incorrectly entered!\n");
		return (0);
	}
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
		{
			free(line);
			ft_printf("\x1b[1;31mThe data about link was incorrectly entered!");
			return (0);
		}
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

int			get_data(t_lm *data, char *line, int i)
{
	while (get_next_line(0, &line))
	{
		if (line)
			ft_printf("%s\n", line);
		while (line && ft_strncmp(line, "#", 1) == 0 &&
			ft_strcmp(line, "##end\0") && ft_strcmp(line, "##start\0"))
		{
			free(line);
			if ((i = get_next_line(0, &line)) && i > 0 && line)
				ft_printf("%s\n", line);
			if (i == 0)
				return (ft_printf("----------------------\n"));
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
	return (ft_printf("----------------------\n"));
}
