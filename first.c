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

static void	free_data(t_lm *data)
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
}

static void	free_ways(t_way *way)
{
	t_way	*h;
	int		i;

	while (way)
	{
		i = 0;
		if (way->way)
			free(way->way);
		while(way->used_rooms && way->used_rooms[i])
		{
			free(way->used_rooms[i]);
			i++;
		}
		if (way->used_rooms)
			free(way->used_rooms);
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
		if (t->rooms)
		{
			i = 0;
			while (t->rooms[i])
				free(t->rooms[i++]);
			free(t->rooms);
		}
		temp = t;
		t = t->next;
		free(temp);
	}
}

int			all_a(char *name, int n)
{
	int i;

	ft_printf("\nL%i-%s", 1, name);
	i = 1;
	while(++i <= n)
		ft_printf(" L%i-%s", i, name);
	ft_printf("\n");
	return (1);
}

int			check(void)
{
	t_lm	*data;
	t_tr	*t;
	t_way	*way;
	int		i;

	if (!(data = (t_lm *)malloc(sizeof(t_lm))))
		return (0);
	data->rooms = NULL;
	data->coments = NULL;
	data->start = NULL;
	data->end = NULL;
	data->n_rm = 2;
	if (get_data(data, 0) == 0 || !(t = (t_tr *)malloc(sizeof(t_tr))))
	{
		ft_printf("\x1b[1;37m");
		free_data(data);
		return (0);
	}
	if (get_tree(t, data, 1) == 0 || last_check(t) == 0 || !(way = (t_way *)malloc(sizeof(t_way))))
	{
		ft_printf("\x1b[1;37m");
		free_tree(t);
		free_data(data);
		return (0);
	}
	i = unique_ways(t, way, data);
	if (i == 0)
	{
		ft_printf("\x1b[1;37m");
		free_tree(t);
		free_data(data);
		free_ways(way);
		return (0);
	}
	if (i == 1)
		all_a(t->next->name, data->ants);
	ft_printf("\x1b[1;37mAll good\n");
	free_tree(t);
	free_data(data);
	free_ways(way);
	return (1);
}

int			main(void)
{
	check();
	system("leaks lem-in -quiet");
	return (1);
}
