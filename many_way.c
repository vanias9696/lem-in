/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   many_way.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismus <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 14:18:32 by ismus             #+#    #+#             */
/*   Updated: 2018/05/10 14:18:38 by ismus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	write_first_name(t_way *way, t_tr *t, char *start)
{
	int k;

	k = 0;
	while (t->rooms[k] && (ft_strcmp(t->rooms[k], start) == 0 ||
		mascmp(t->rooms[k], way->used_rooms) == 0))
		k++;
	way->way[0] = t->rooms[k];
	return (k);
}

static int	write_name(t_way *way, t_tr *t, int k, int i)
{
	char	*start;

	k = 0;
	start = t->name;
	while (way->way[k])
		k++;
	if (k == 0)
		return (write_first_name(way, t, start));
	k--;
	while (t && ft_strcmp(t->name, way->way[k]) != 0)
		t = t->next;
	if (!t)
		return (-1);
	i = 0;
	while (t->rooms[i] && (!ft_strcmp(t->rooms[i], start) ||
		!mascmp(t->rooms[i], way->way) ||
		!mascmp(t->rooms[i], way->used_rooms)))
		i++;
	if (t->rooms[i])
	{
		way->way[k + 1] = t->rooms[i];
		return (k + 1);
	}
	return (-1);
}

static int	next_name(t_way *way, t_tr *t, int k)
{
	int		i;
	char	*start;

	start = t->name;
	if (k != 0)
	{
		while (ft_strcmp(way->way[k - 1], t->name) != 0)
			t = t->next;
	}
	i = 0;
	while (ft_strcmp(way->way[k], t->rooms[i]) != 0)
		i++;
	i++;
	while (t->rooms[i] && (ft_strcmp(t->rooms[i], start) == 0 ||
		mascmp(t->rooms[i], way->way) == 0 ||
		mascmp(t->rooms[i], way->used_rooms) == 0))
		i++;
	way->way[k] = t->rooms[i];
	return (t->rooms[i] == 0 ? 0 : 1);
}

int			test_way(t_way *way, t_tr *t, int i, int k)
{
	int m;

	m = -1;
	if (k >= i)
	{
		way->way[k] = 0;
		return (0);
	}
	if (write_name(way, t, 0, 0) < 0)
		return (0);
	if (ft_strcmp(t->next->name, way->way[k]) == 0)
		return (1);
	while (test_way(way, t, i, k + 1) == 0)
	{
		if (next_name(way, t, k) == 0)
		{
			way->way[k] = 0;
			return (0);
		}
		if (ft_strcmp(t->next->name, way->way[k]) == 0)
			return (1);
	}
	return (1);
}
