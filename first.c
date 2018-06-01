/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismus <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 15:10:53 by ismus             #+#    #+#             */
/*   Updated: 2018/04/26 15:10:54 by ismus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	free_ways(t_way *way)
{
	t_way	*h;
	int		i;

	while (way)
	{
		i = 0;
		if (way->way)
			free(way->way);
		while (way->used_rooms && way->used_rooms[i])
		{
			free(way->used_rooms[i]);
			i++;
		}
		if (way->used_rooms)
			free(way->used_rooms);
		if (way->an_w)
			free(way->an_w);
		h = way->next;
		free(way);
		way = h;
	}
}

static void	free_tree(t_tr *t)
{
	t_tr	*temp;
	int		i;

	while (t)
	{
		if (t->name)
			free(t->name);
		i = 0;
		while (t->rooms && t->rooms[i])
			free(t->rooms[i++]);
		if (t->rooms)
			free(t->rooms);
		temp = t;
		t = t->next;
		free(temp);
	}
}

static int	by_z(t_lm *data, t_tr *t)
{
	if (data)
	{
		data->rooms = 0;
		data->coments = 0;
		data->start = 0;
		data->end = 0;
		data->n_rm = 2;
	}
	if (t)
	{
		t->name = 0;
		t->rooms = 0;
		t->next = 0;
	}
	return (1);
}

static int	free_data(t_lm *data, t_way *way, t_tr *t, char **argv)
{
	if (data && data->rooms)
		free(data->rooms);
	if (data && data->coments)
		free(data->coments);
	if (data && data->start)
		free(data->start);
	if (data && data->end)
		free(data->end);
	if (data)
		free(data);
	if (way)
		free_ways(way);
	if (t)
		free_tree(t);
	ft_printf("\x1b[1;37m");
	if (argv && mascmp("-error\0", argv) == 0)
		correct_data();
	return (0);
}

int			main(int argc, char **argv)
{
	t_lm	*data;
	t_tr	*t;
	t_way	*way;
	int		i;

	if (get_arg(argc, argv) == 0)
	{
		ft_printf("\x1b[1;31mFlags were incorrectly entered.\n");
		return (ft_printf("Allowed flags are:\n-colour;\n-error.\n\x1b[1;37m"));
	}
	if (!(data = (t_lm *)malloc(sizeof(t_lm))))
		return (0);
	if (by_z(data, 0) == 0 || data_a(data, 0, 0) == 0 || !get_data(data, 0, 0)
		|| !(t = (t_tr *)malloc(sizeof(t_tr))))
		return (free_data(data, 0, 0, argv));
	if (by_z(0, t) == 0 || get_tree(t, data, 1) == 0 || last_check(t) == 0
		|| !(way = (t_way *)malloc(sizeof(t_way))))
		return (free_data(data, 0, t, argv));
	if (!(i = unique_ways(t, way, data)) && i == 0)
		return (free_data(data, way, t, argv));
	else if (i == 1)
		all_a(t->next->name, data->ants, argv);
	else
		take_turns(data->ants, &way, argv);
	return (free_data(data, way, t, 0));
}
