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

static int	n_used_r(int n, t_way *way)
{
	int		i;
	int		q;
	int		k;

	i = 0;
	q = 0;
	while (++i < n)
	{
		k = -1;
		while (way->way[++k])
			q++;
		way = way->next;
		q--;
	}
	return (q);
}

static char	**used_r(int n, t_way *h, char **er)
{
	int		i;
	int		k;
	int		q;

	q = n_used_r(n, h);
	er = (char **)malloc(sizeof(char *) * (q + 1));
	er[q] = 0;
	q = -1;
	i = 0;
	while (++i < n)
	{
		k = 0;
		while (h->way[k + 1])
		{
			er[++q] = ft_strdup(h->way[k]);
			k++;
		}
		h = h->next;
	}
	return (er);
}

static int	selection_r(t_way *new, t_tr *t, int i, int n_rm)
{
	int k;

	while (++i < n_rm)
	{
		k = -1;
		while (new->way[++k])
			new->way[k] = 0;
		if (test_way(new, t, i, 0) == 1)
			break ;
	}
	new->len = i;
	return (i);
}

static int	many_way(t_way **way, t_tr *t, int n_rm, int n_way)
{
	t_way	*new;
	int		i;
	int		n;

	new = *way;
	n = 0;
	while (++n <= n_way)
	{
		if (!(new->way = (char **)malloc(sizeof(char *) * (n_rm + 1))))
			return (pr_free("Memory error!", 0, 0, 0));
		new->used_rooms = n == 1 ? 0 : used_r(n, *way, new->used_rooms);
		new->next = 0;
		new->num = n;
		i = selection_r(new, t, i, n_rm);
		if (i == n_rm && new->num == 1)
			return (pr_free("Way not found!", 0, 0, 0));
		if (i == n_rm)
			return (2);
		if (n < n_way && !(new->next = (t_way *)malloc(sizeof(t_way))))
			return (pr_free("Memory error!", 0, 0, 0));
		new = new->next;
	}
	return (2);
}

int			unique_ways(t_tr *t, t_way *way, t_lm *data)
{
	t_tr	*h;
	int		i;

	h = t->next;
	way->way = 0;
	way->used_rooms = 0;
	way->an_w = 0;
	i = -1;
	while (t->rooms[++i])
		if (ft_strcmp(h->name, t->rooms[i]) == 0)
			break ;
	if (t->rooms[i])
		return (1);
	i = 0;
	while (t->rooms[i] && h->rooms[i])
		i++;
	if (i > 0)
		return (many_way(&way, t, data->n_rm, i));
	else
		return (pr_free("Way not found!", 0, 0, 0));
	return (0);
}
