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

#include "lem-in.h"

static int	data_a(t_lm *data, int i)
{
	char	*line;

	get_next_line(0, &line);
	while (line && line[i] <= '9' && line[i] >= '0')
		i++;
	if (!line)
	{
		ft_printf("\x1b[1;31mInsufficient data!\n");
		return (0);
	}
	if (line[i] != '\0')
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

static int	get_st_end(char *line, t_lm *data)
{
	if (ft_strcmp(line, "##start\0") != 0 && ft_strcmp(line, "##end\0") != 0)
	{
		free(line);
		ft_printf("\x1b[1;31mThe data was incorrectly entered!\n");
		return (0);
	}
	if ((ft_strcmp(line, "##start\0") == 0 && data->start) ||
		(ft_strcmp(line, "##end\0") == 0 && data->end))
	{
		ft_printf("\x1b[1;31mMore that one %s!\n", line + 2);
		free(line);
		return (0);
	}
	if (ft_strcmp(line, "##start\0") == 0)
		get_next_line(0, &(data->start));
	else
		get_next_line(0, &(data->end));
	free(line);
	if (data->start == 0 && data->end == 0)
	{
		ft_printf("\x1b[1;31mThe data was incorrectly entered!\n");
		return (0);
	}
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
		ft_printf("\x1b[1;31mThe data was incorrectly entered!\n");
		free(line);
		return (0);
	}
	if (data->rooms == 0)
		data->rooms = joinfree(line, "\0", 1);
	else
	{
		data->rooms = joinfree(data->rooms, "\n\0", 1);
		data->rooms = joinfree(data->rooms, line, 3);
	}
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
			ft_printf("\x1b[1;31mThe data was incorrectly entered!\n");
			free(line);
			return (0);
		}
		else if (data->coments == 0)
			data->coments = line;
		else
		{
			data->coments = join3free(data->coments, "\n\0", line, 5);
		}
		return (1);
	}
	else if (line[i] == ' ')
		return (add_rooms(data, ++i, line));
	ft_printf("\x1b[1;31mThe data was incorrectly entered!\n");
	free(line);
	return (0);
}

int			get_data(t_lm *data)
{
	char	*line;

	if (data_a(data, 0) == 0)
		return (0);
	while (get_next_line(0, &line))
	{
		if (!line)
			return (0);
		else if (ft_strncmp(line, "##", 2) == 0 && get_st_end(line, data) == 0)
			return (0);
		else if (ft_strncmp(line, "##", 2) != 0 &&
			ft_strncmp(line, "#", 1) == 0)
			free(line);
		else if (ft_strncmp(line, "##", 2) != 0 &&
			add_coments(line, 0, data) == 0)
			return (0);
	}
	if (data->start == 0 || data->end == 0 || data->coments == 0)
	{
		ft_printf("\x1b[1;31mData is not enough\n");
		return (0);
	}
	return (1);
}
