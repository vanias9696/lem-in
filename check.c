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
	while(line && line[i] <= '9' && line[i] >= '0')
		i++;
	if (!line)
	{
		ft_printf("\x1b[1;31minsufficient data!\n");
		return (0);
	}
	if (line[i] != '\0')
	{
		free(line);
		ft_printf("\x1b[1;31mnot the correct number of ants!\n");
		return (0);
	}
	data->ants = ft_atoi(line);
	free(line);
	if (data->ants == 0)
	{
		ft_printf("\x1b[1;31mnot enough ants!\n");
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

static int	get_else(t_lm *data, char *line, int i)
{
	while (get_next_line(0, line))
	{
		if (line && ft_strncmp(line, "##", 2) == 0 && get_st_end(line, data) == 0)//початок або кінець
			return (0);
		//тут зчитуваня кімнат і коментарів

	}
	return (1);
}

t_lm		*get_data(t_lm *data)
{
	char	*line;

	if (data_a(data, 0) == 0)//мурахи
		return (0);
	if (get_else(data, 0, 0) == 0)//все інше
		return (0);
}
