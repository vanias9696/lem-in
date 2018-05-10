/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unique_ways.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismus <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 14:15:05 by ismus             #+#    #+#             */
/*   Updated: 2018/05/02 14:15:06 by ismus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	write_name(t_way *way, t_tr *t)
{
	int k;
	char *start;
	int i;

	k = 0;
	start = t->name;
	while (way->way[k])
		k++;
	if (k == 0)
	{
		way->way[0] = t->rooms[0];
		return (k);
	}
	else
		k--;
	while(t && ft_strcmp(t->name, way->way[k]) != 0)
		t = t->next;
	if (!t)
		return (-1);
	i = 0;
	while (t->rooms[i] && (ft_strcmp(t->rooms[i], start) == 0 ||
		mascmp(t->rooms[i], way->way) == 0))
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
	int i;

	i = 0;
	if (k == 0)
	{
		while(ft_strcmp(way->way[k], t->rooms[i]) != 0)
			i++;
		way->way[k] = t->rooms[i + 1];
		return (t->rooms[i + 1] == 0 ? 0 : 1);
	}
	while(ft_strcmp(way->way[k - 1], t->name) != 0)
		t = t->next;
	i = 0;
	while(ft_strcmp(way->way[k], t->rooms[i]) != 0)
		i++;
	way->way[k] = t->rooms[i + 1];
	return (t->rooms[i + 1] == 0 ? 0 : 1);
}

static int	test_way(t_way *way, t_tr *t, int i, int k)
{
	int m;

	m = -1;
	if (k >= i)
	{
		way->way[k] = 0;
		return (0);
	}
	if (write_name(way, t) < 0)
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

int			one_way(t_way *way, t_tr *t, int n_rm)
{
	int i;
	int k;

	i = -1;
	way->way = (char **)malloc(sizeof(char *) * (n_rm + 1));
	way->next = 0;
	while(++i <= n_rm)
		way->way[i] = 0;
	i = 1;
	while (++i < n_rm)
	{
		if (test_way(way, t, i, 0) == 1)
			break ;
		k = -1;
		while (way->way[++k])
			way->way[k] = 0;
	}
	if (i >= n_rm)
		return(pr_free("Way not found!", 0, 0));

	i = -1;
	while (way->way[++i])
		ft_printf("%s\n", way->way[i]);
	way->len = i;
	way->num = 1;
	return (2);
}

int			unique_ways(t_tr *t, t_way *way, t_lm *data)
{
	t_tr	*h;
	int		i;

	h = t->next;
	way->way = 0;
	i = -1;
	while(t->rooms[++i])
		if (ft_strcmp(h->name, t->rooms[i]) == 0)
			break ;
	if (t->rooms[i])
		return (1);
	i = 0;
	while(t->rooms[i] && h->rooms[i])
		i++;
	//if (i == 1)
		// return(one_way(way, t, data->n_rm));
	if (i > 0)
		return(many_way(&way, t, data->n_rm, i));
	else
		return(pr_free("Way not found!", 0, 0));
	return (0);
}
